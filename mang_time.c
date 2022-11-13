/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mang_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:26:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/26 15:16:42 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* this will set the start time and the stop time for philo to start his action
so we can calculate when it should stop
sim to save the the time of the beginnig their last meal */
void	count_for_dumb(t_philo *dumb, char what)
{
	dumb->t_start = what_is_time_now(dumb);
	if (what == 'e')
	{
		dumb->t_stop = dumb->t_start + dumb->m_info->time_eat;
		dumb->sim = dumb->t_start;
	}
	else if (what == 's')
		dumb->t_stop = dumb->t_start + dumb->m_info->time_sleep;
	else if (what == 'd')
		dumb->t_stop = dumb->t_start + dumb->m_info->time_die;
}

/* This will calculate the time now .. 
tv_sec is the number of seconds tv_usec it's fraction in milliseconds */
int	what_is_time_now(t_philo *dumb)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	dumb->t_now = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (dumb->t_now);
}

/* 
check if they don't have time left 
to wait till the fork be available again
(what_is_time_now(dumb) - dumb->sim) -> 
the time exceeded form the beginning of their last meal till now
dumb->m_info->time_die - (what_is_time_now(dumb) - dumb->sim) -> 
to see if there is time left to wait
 + dumb->m_info->time_sleep && dumb->yes_think == 1 -> 
 cuz they were dying b4 they think 
 */
int	check_death(t_philo *dumb)
{
	int	i;

	pthread_mutex_lock(&dumb->m_info->d_mut);
	if (dumb->m_info->time_die < (what_is_time_now(dumb) - dumb->sim) \
	&& dumb->yes_think == 1 && dumb->m_info->f_died != 1)
	{
		dumb->m_info->f_died = 1;
		pthread_mutex_unlock(&dumb->m_info->d_mut);
		i = (dumb->m_info->time_die - (what_is_time_now(dumb) - dumb->sim));
		if (i > 0)
			usleep(i * 1000);
		if ((what_is_time_now(dumb) - dumb->t_start) - i > \
		dumb->m_info->time_eat)
			print_for_dumb(dumb, "is died", BRED, 'd');
		else
			print_for_dumb(dumb, "is died", BRED, 'D');
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&dumb->m_info->d_mut);
		return (1);
	}
}

/* the time now - the time from where they did start the action */
int	calc_tstamp(t_philo *dumb, char what)
{
	if (what == 'n')
		dumb->t_crnt = what_is_time_now(dumb) - dumb->m_info->t_initial;
	else
		dumb->t_crnt += 0;
	return (dumb->t_crnt);
}

void	print_for_dumb(t_philo *dumb, char *str, char *code, char what)
{
	if (f_died_lock(dumb) && what == 'l')
	{
		pthread_mutex_lock(&dumb->m_info->p_mut);
		printf("%s%d %d %s\n", code, calc_tstamp(dumb, 'n'), dumb->id + 1, str);
		pthread_mutex_unlock(&dumb->m_info->p_mut);
	}
	else if (!f_died_lock(dumb) && what == 'd')
	{
		pthread_mutex_lock(&dumb->m_info->p_mut);
		printf("%s%d %d %s\n", code, calc_tstamp(dumb, 'n'), dumb->id + 1, str);
		pthread_mutex_unlock(&dumb->m_info->p_mut);
	}
	else if (!f_died_lock(dumb))
	{
		pthread_mutex_lock(&dumb->m_info->p_mut);
		printf("%s%d %d %s\n", code, calc_tstamp(dumb, 'n'), \
		dumb->id + 1, str);
		pthread_mutex_unlock(&dumb->m_info->p_mut);
	}
}
