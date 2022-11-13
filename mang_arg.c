/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mang_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:38:43 by aaljaber          #+#    #+#             */
/*   Updated: 2022/04/23 19:30:48 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		n;
	long	result;

	i = 0;
	n = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		n = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * n);
}

int	is_valid(char **argv)
{
	int	i;
	int	k;

	k = -1;
	i = 0;
	while (argv[++i])
	{
		k = -1;
		while (argv[i][++k])
		{
			if (argv[i][k] < '0' || argv[i][k] > '9')
				return (0);
		}
	}
	return (1);
}

int	mang_mutex(t_main *philo)
{
	philo->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
		philo->num_philo);
	if (!philo->mutex)
	{
		printf (BRED"Error: MALLOC Failed\n");
		return (0);
	}
	philo->a_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
		philo->num_philo);
	if (!philo->a_mutex)
	{
		printf (BRED"Error: MALLOC Failed\n");
		return (0);
	}
	return (1);
}

int	mang_arrays(t_main *philo)
{
	if (!mang_mutex(philo))
		return (0);
	philo->forks = (int *)malloc(sizeof(int) * philo->num_philo);
	if (!philo->forks)
	{
		printf (BRED"Error: MALLOC Failed\n");
		return (0);
	}
	mang_fork((void *)philo, 0);
	philo->ate = (int *)malloc(sizeof(int) * philo->num_philo);
	if (!philo->ate)
	{
		printf (BRED"Error: MALLOC Failed\n");
		return (0);
	}
	mang_eat((void *)philo, 0);
	return (1);
}

int	mang_struct(t_main *philo, char **argv)
{
	if (is_valid(argv))
	{
		philo->num_philo = ft_atoi(argv[1]);
		philo->time_die = ft_atoi(argv[2]);
		philo->time_eat = ft_atoi(argv[3]);
		printf("%s\n", argv[3]);
		philo->f_died = 0;
		philo->time_sleep = ft_atoi(argv[4]);
		philo->t_initial = 0;
		philo->f_print = 0;
		if (argv[5])
			philo->num_eat = ft_atoi(argv[5]);
		if (philo->num_philo <= 0 || philo->time_die <= 0|| philo->time_eat <= 0 || philo->time_sleep <= 0)
			return (0);
		else if (!argv[5])
			philo->num_eat = 0;
		if (!mang_arrays(philo))
			return (0);
		return (1);
	}
	else
	{
		printf (BRED"Error: Invalid args\n");
		return (0);
	}
}
