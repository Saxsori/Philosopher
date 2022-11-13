/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mang_ate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:41:40 by aaljaber          #+#    #+#             */
/*   Updated: 2022/04/19 20:41:42 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* the way to handle the greedy philo */
void	init_ate_arr(void *arg)
{
	t_main	*main;
	int		i;

	main = (t_main *)arg;
	i = -1;
	while (++i < main->num_philo)
		main->ate[i] = -1;
}

int	did_eat(void *arg)
{
	t_philo	*dumb;

	dumb = (t_philo *)arg;
	pthread_mutex_lock(&dumb->m_info->a_mutex[dumb->left]);
	if (dumb->m_info->ate[dumb->left] != dumb->id)
	{
		dumb->m_info->ate[dumb->left] = dumb->id;
		pthread_mutex_unlock(&dumb->m_info->a_mutex[dumb->left]);
	}
	else
		pthread_mutex_unlock(&dumb->m_info->a_mutex[dumb->left]);
	pthread_mutex_lock(&dumb->m_info->a_mutex[dumb->right]);
	if (dumb->m_info->ate[dumb->right] != dumb->id)
	{
		dumb->m_info->ate[dumb->right] = dumb->id;
		pthread_mutex_unlock(&dumb->m_info->a_mutex[dumb->right]);
	}
	else
		pthread_mutex_unlock(&dumb->m_info->a_mutex[dumb->right]);
	return (0);
}

int	can_eat(void *arg)
{
	t_philo	*dumb;

	dumb = (t_philo *)arg;
	dumb->r = 0;
	dumb->l = 0;
	pthread_mutex_lock(&dumb->m_info->a_mutex[dumb->left]);
	if (dumb->m_info->ate[dumb->left] != dumb->id)
	{
		pthread_mutex_unlock(&dumb->m_info->a_mutex[dumb->left]);
		dumb->l = 1;
	}
	else
		pthread_mutex_unlock(&dumb->m_info->a_mutex[dumb->left]);
	pthread_mutex_lock(&dumb->m_info->a_mutex[dumb->right]);
	if (dumb->m_info->ate[dumb->right] != dumb->id)
	{
		pthread_mutex_unlock(&dumb->m_info->a_mutex[dumb->right]);
		dumb->r = 1;
	}
	else
		pthread_mutex_unlock(&dumb->m_info->a_mutex[dumb->right]);
	if (dumb->r == 1 && dumb->l == 1)
		return (1);
	return (0);
}

void	clear_ate_arr(void	*arg)
{
	t_philo	*dumb;
	int		i;

	dumb = (t_philo *)arg;
	i = -1;
	pthread_mutex_lock(&dumb->m_info->l_mut);
	while (++i < dumb->m_info->num_philo)
	{
		pthread_mutex_lock(&dumb->m_info->a_mutex[i]);
		dumb->m_info->ate[i] = 0;
		pthread_mutex_unlock(&dumb->m_info->a_mutex[i]);
	}
	pthread_mutex_unlock(&dumb->m_info->l_mut);
}

int	mang_eat(void *arg, int op)
{
	if (op == 0)
	{
		init_ate_arr(arg);
		return (1);
	}
	else if (op == 1)
	{
		if (can_eat(arg))
			return (1);
		else
			return (0);
	}
	else if (op == 2)
	{
		did_eat(arg);
		return (1);
	}
	return (0);
}
