/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mang_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:46:50 by aaljaber          #+#    #+#             */
/*   Updated: 2022/04/23 16:53:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->num_philo)
		pthread_mutex_init(&main->mutex[i], NULL);
	i = -1;
	while (++i < main->num_philo)
		pthread_mutex_init(&main->a_mutex[i], NULL);
	pthread_mutex_init(&main->p_mut, NULL);
	pthread_mutex_init(&main->d_mut, NULL);
	pthread_mutex_init(&main->i_mut, NULL);
	pthread_mutex_init(&main->c_mut, NULL);
	pthread_mutex_init(&main->t_mut, NULL);
	pthread_mutex_init(&main->ii_mut, NULL);
	pthread_mutex_init(&main->l_mut, NULL);
}

void	destroy_mutex(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->num_philo)
		pthread_mutex_destroy(&main->mutex[i]);
	i = -1;
	while (++i < main->num_philo)
		pthread_mutex_destroy(&main->a_mutex[i]);
	pthread_mutex_destroy(&main->p_mut);
	pthread_mutex_destroy(&main->d_mut);
	pthread_mutex_destroy(&main->i_mut);
	pthread_mutex_destroy(&main->c_mut);
	pthread_mutex_destroy(&main->t_mut);
	pthread_mutex_destroy(&main->ii_mut);
	pthread_mutex_destroy(&main->l_mut);
}

void	free_arr(t_main *main)
{
	free(main->a_mutex);
	free(main->ate);
	free(main->mutex);
	free(main->forks);
}
