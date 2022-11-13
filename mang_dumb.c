/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mang_dumb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:41:58 by aaljaber          #+#    #+#             */
/*   Updated: 2022/04/21 20:52:09 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_dumb(t_philo *dumb, t_main	*main, int i)
{
	dumb->id = i;
	dumb->m_info = main;
	dumb->f_left = 0;
	dumb->f_right = 0;
	dumb->yes_eat = 0;
	dumb->yes_sleep = 0;
	dumb->yes_think = 0;
	dumb->t_now = 0;
	dumb->t_crnt = 0;
	dumb->t_stop = 0;
	dumb->t_start = 0;
	dumb->m_info->count = dumb->m_info->num_eat;
	if (dumb->m_info->num_eat)
		dumb->m_info->count--;
	dumb->e = 0;
	dumb->t_crnt = 0;
	dumb->sim = 0;
	dumb->right = dumb->id;
	dumb->r = 0;
	if (dumb->id == 0)
		dumb->left = (dumb->id + dumb->m_info->num_philo) - 1;
	else
		dumb->left = dumb->id - 1;
	dumb->l = 0;
}

void	pre_dumb(t_philo *dumb, t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->num_philo)
		init_dumb(&dumb[i], main, i);
}

void	create_dumb(t_main *main, t_philo *dumb)
{
	struct timeval	now;
	int				i;

	i = -1;
	main->l = main->num_philo;
	gettimeofday(&now, NULL);
	main->t_initial = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	if (main->num_philo % 2 != 0)
		main->l--;
	while (++i < main->l)
	{
		++i;
		pthread_create(&main->philo[i], NULL, &life_begin, &dumb[i]);
	}
	usleep(1000);
	i = -2;
	if (main->num_philo % 2 == 0)
		main->l--;
	else if (main->num_philo % 2 != 0)
		main->l++;
	while (++i < main->l)
	{
		++i;
		pthread_create(&main->philo[i], NULL, &life_begin, &dumb[i]);
	}
}

/* Threads will return 1 in case of death or 0 in case of success 
   I didn't malloc it cuz it's static ^.^ */
/* I'm using a pointer from the main function 
so no static and no malloc needed 
|| CHECK IF U NEED MALLOC */
int	dumb_exist(t_main *main)
{
	t_philo		*dumb;
	int			*death;
	int			i;

	main->philo = (pthread_t *)malloc(sizeof(pthread_t) * main->num_philo);
	dumb = (t_philo *)malloc(sizeof(t_philo) * main->num_philo);
	pre_dumb(dumb, main);
	main->phil = dumb;
	create_dumb(main, dumb);
	i = -1;
	while (++i < main->num_philo)
		pthread_join(main->philo[i], (void *)&death);
	if (*death == 1 || death == NULL || *death == 0)
	{
		free(dumb);
		free(main->philo);
		return (0);
	}
	return (0);
}

int	f_died_lock(t_philo *dumb)
{
	pthread_mutex_lock(&dumb->m_info->d_mut);
	if (dumb->m_info->f_died)
	{
		pthread_mutex_unlock(&dumb->m_info->d_mut);
		return (0);
	}
	pthread_mutex_unlock(&dumb->m_info->d_mut);
	return (1);
}
