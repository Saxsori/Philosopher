/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mang_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:09:49 by aaljaber          #+#    #+#             */
/*   Updated: 2022/04/23 19:46:20 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *dumb)
{
	if (f_died_lock(dumb))
		print_for_dumb(dumb, "is eating", BMAG, 'l');
	dumb->sim = what_is_time_now(dumb);
	while (42)
	{
		what_is_time_now(dumb);
		if (!check_death(dumb))
			break ;
		if (dumb->t_now - dumb->t_stop > 0)
			break ;
		usleep (1000);
	}
	dumb->yes_eat = 1;
	mang_fork((void *)dumb, 3);
	if (dumb->m_info->num_eat != 0)
		dumb->e++;
	dumb->f_left = 0;
	dumb->f_right = 0;
	// printf("%d\n",dumb->t_now - dumb->sim);
	check_death2(dumb);
}

void	sleeping(t_philo *dumb)
{
	if (f_died_lock(dumb))
		print_for_dumb(dumb, "is sleeping", BGRN, 'l');
	dumb->yes_eat = 0;
	count_for_dumb(dumb, 's');
	while (42)
	{
		what_is_time_now(dumb);
		if (!check_death(dumb))
			break ;
		if (dumb->t_now - dumb->t_stop > 0)
			break ;
		usleep(1000);
	}
	dumb->yes_sleep = 1;
	check_death(dumb);
}

void	thinking(t_philo *dumb)
{
	check_death(dumb);
	if (f_died_lock(dumb))
		print_for_dumb(dumb, "is thinking", BYEL, 'l');
	dumb->yes_sleep = 0;
	dumb->yes_think = 1;
}

void	dying(t_philo *dumb)
{
	count_for_dumb(dumb, 'd');
	while (42)
	{
		if (!check_death(dumb))
			break ;
		if (mang_fork((void *)dumb, 1))
		{
			calc_tstamp(dumb, 'n');
			break ;
		}
		what_is_time_now(dumb);
		pthread_mutex_lock(&dumb->m_info->d_mut);
		if (dumb->t_now - dumb->t_stop >= 0 && dumb->m_info->f_died != 1)
		{
			dumb->m_info->f_died = 1;
			pthread_mutex_unlock(&dumb->m_info->d_mut);
			print_for_dumb(dumb, "is died", BRED, 'd');
			break ;
		}
		pthread_mutex_unlock(&dumb->m_info->d_mut);
		usleep(1000);
	}
}

void	check_death2(t_philo *dumb)
{
	int	i;

	what_is_time_now(dumb);
	if ((dumb->t_now - dumb->sim) + dumb->m_info->time_sleep >= dumb->m_info->time_die)
	{
		i = dumb->m_info->time_die - (dumb->t_now - dumb->sim);
		if (i > 0)
			usleep(i * 1000);
		if (f_died_lock(dumb))
		{
			pthread_mutex_lock(&dumb->m_info->d_mut);
			dumb->m_info->f_died = 1;
			pthread_mutex_unlock(&dumb->m_info->d_mut);
			print_for_dumb(dumb, "is died", BRED, 'd');
		}
	}
}
