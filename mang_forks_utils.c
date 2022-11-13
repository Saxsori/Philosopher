/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mang_forks_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:42:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/04/21 21:14:52 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->num_philo)
		main->forks[i] = 0;
}

/* check if it's available 
philo 1 take the fork 1 and the last fork */
int	is_fork(void *arg)
{
	t_philo	*dumb;

	dumb = (t_philo *)arg;
	if ((dumb->id + (dumb->m_info->num_philo - 1)) < 1 && dumb->id == 0)
		return (0);
	pthread_mutex_lock(&dumb->m_info->mutex[dumb->left]);
	if (dumb->m_info->forks[dumb->left] == 1)
	{
		pthread_mutex_unlock(&dumb->m_info->mutex[dumb->left]);
		return (0);
	}
	pthread_mutex_unlock(&dumb->m_info->mutex[dumb->left]);
	pthread_mutex_lock(&dumb->m_info->mutex[dumb->right]);
	if (dumb->m_info->forks[dumb->right] == 1)
	{
		pthread_mutex_unlock(&dumb->m_info->mutex[dumb->right]);
		return (0);
	}
	pthread_mutex_unlock(&dumb->m_info->mutex[dumb->right]);
	return (1);
}

void	left_fork(t_philo *dumb)
{
	pthread_mutex_lock(&dumb->m_info->mutex[dumb->left]);
	if (dumb->m_info->forks[dumb->left] == 0)
	{
		dumb->m_info->forks[dumb->left] = 1;
		pthread_mutex_unlock(&dumb->m_info->mutex[dumb->left]);
		dumb->f_left = 1;
	}
	if (!dumb->f_left)
		pthread_mutex_unlock(&dumb->m_info->mutex[dumb->left]);
}

void	right_fork(t_philo *dumb)
{
	pthread_mutex_lock(&dumb->m_info->mutex[dumb->right]);
	if (dumb->m_info->forks[dumb->right] == 0 && dumb->f_left)
	{
		dumb->m_info->forks[dumb->right] = 1;
		pthread_mutex_unlock(&dumb->m_info->mutex[dumb->right]);
		dumb->f_right = 1;
	}
	if (!dumb->f_right && !dumb->f_left)
		pthread_mutex_unlock(&dumb->m_info->mutex[dumb->right]);
	if (!dumb->f_right && dumb->f_left)
	{
		pthread_mutex_unlock(&dumb->m_info->mutex[dumb->right]);
		pthread_mutex_lock(&dumb->m_info->mutex[dumb->left]);
		dumb->m_info->forks[dumb->left] = 0;
		pthread_mutex_unlock(&dumb->m_info->mutex[dumb->left]);
		dumb->f_left = 0;
	}
}
