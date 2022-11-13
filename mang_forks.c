/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mang_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:42:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/04/21 21:14:35 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* in case of having only one philo then 
he will take only one fork and die after his time of death
and never print that he took the fork cuz he didn't take both 
never print if one take one fork only if they take both 
they will never eat if not 
dumb->right = 1 & dumb->left = 1 */
void	take_fork(void *arg)
{
	t_philo	*dumb;

	dumb = (t_philo *)arg;
	if (mang_fork((void *)dumb, 1))
	{
		if ((dumb->id + dumb->m_info->num_philo) - 1 > 0)
		{
			left_fork(dumb);
			right_fork(dumb);
			if (dumb->f_left && dumb->f_right)
			{
				mang_eat((void *)dumb, 2);
				print_for_dumb(dumb, "has taken a fork", BBLU, 'l');
				print_for_dumb(dumb, "has taken a fork", BBLU, 'l');
			}
		}
		else
		{
			dumb->m_info->forks[dumb->id] = 1;
			dumb->f_right = 1;
		}
	}
}

void	put_fork(t_philo *dumb)
{
	if (!mang_fork((void *)dumb, 1))
	{
		if ((dumb->id + dumb->m_info->num_philo) - 1 > 0)
		{
			pthread_mutex_lock(&dumb->m_info->mutex[dumb->left]);
			if (dumb->m_info->forks[dumb->left])
			{
				dumb->m_info->forks[dumb->left] = 0;
				pthread_mutex_unlock(&dumb->m_info->mutex[dumb->left]);
				dumb->f_left = 0;
			}
			if (dumb->f_left)
				pthread_mutex_unlock(&dumb->m_info->mutex[dumb->left]);
			pthread_mutex_lock(&dumb->m_info->mutex[dumb->right]);
			if (dumb->m_info->forks[dumb->right])
			{
				dumb->m_info->forks[dumb->right] = 0;
				pthread_mutex_unlock(&dumb->m_info->mutex[dumb->right]);
				dumb->f_right = 0;
			}
			if (dumb->f_right)
				pthread_mutex_unlock(&dumb->m_info->mutex[dumb->right]);
		}
	}
}
