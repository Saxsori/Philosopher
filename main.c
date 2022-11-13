/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrar <abrar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:45:38 by aaljaber          #+#    #+#             */
/*   Updated: 2022/04/23 15:46:30 by abrar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mang fork the main function to manage everything related to the fork
0 - to initialize 
1 - to check if it's available 
2 - to take the fork if it's available
3 - to put fork back */
int	mang_fork(void *arg, int op)
{
	if (op == 0)
		init_forks(arg);
	else if (op == 1)
	{
		if (!is_fork(arg))
			return (0);
	}
	else if (op == 2)
	{
		if (is_fork(arg))
			take_fork(arg);
	}
	else if (op == 3)
		put_fork((t_philo *)arg);
	return (1);
}

void	eating_extra_lines(t_philo *dumb)
{
	dumb->yes_think = 0;
	count_for_dumb(dumb, 'e');
}

/*
LOOPING --> start from 0,so if num_eat = 0 
in that case count will be always equal to 0 
so it's an infinite loop. 
If num_eat != 0 then i will decreament count by 1, cuz it will start
looping from 0 and I'm using this operator "<=" ... 
this is my way to handle inifine loop and finite loop at the same time 
- here were everything start only who's fork is available will enter
*/
void	*life_begin(void *arg)
{
	t_philo	*dumb;

	dumb = (t_philo *)arg;
	dumb->e = 0;
	while (dumb->e <= dumb->m_info->count && \
	check_death(dumb) && f_died_lock(dumb))
	{
		if (mang_fork((void *)dumb, 1) && check_death(dumb))
		{
			eating_extra_lines(dumb);
			if (mang_eat((void *)dumb, 1))
				mang_fork((void *)dumb, 2);
			if (dumb->f_right == 1 && dumb->f_left == 1 && \
			f_died_lock(dumb) && check_death(dumb))
				eating(dumb);
			if (dumb->yes_eat == 1 && f_died_lock(dumb) && check_death(dumb))
				sleeping(dumb);
			if (dumb->yes_sleep == 1 && f_died_lock(dumb) && check_death(dumb))
				thinking(dumb);
		}
		else if (!mang_fork((void *)dumb, 1) && \
		f_died_lock(dumb) && check_death(dumb))
			dying(dumb);
	}
	return (&dumb->m_info->f_died);
}

/* mang means manage -_- 
  philo is DUMB, don't you think so?;) */
/* here where should everything start,
array of mutex cuz each fork need a mutex, 
if i locked the whole array
a lot of DUMBS could die waiting for the unlock (waiting for their turn) so 
each fork will have his own lock 
so that the each philo would wait only for his fork
to be available */
/* the infinite loop -> to make gor some reasons it does work:) */
int	main(int argc, char **argv)
{
	t_main	main;

	if (argc == 6 || argc == 5)
	{
		if (!mang_struct(&main, argv))
			return (1);
		init_mutex(&main);
		if (dumb_exist(&main))
		{
			destroy_mutex(&main);
			free(main.mutex);
			free(main.a_mutex);
			return (1);
		}
		destroy_mutex(&main);
		free_arr(&main);
	}
	else
	{
		printf (BRED"Error: Missing args\n");
		return (1);
	}
	return (0);
}
