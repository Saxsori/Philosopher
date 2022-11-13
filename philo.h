/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:52:23 by aaljaber          #+#    #+#             */
/*   Updated: 2022/04/23 17:20:06 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
# include   <pthread.h>
# include   <sys/types.h>
# include	<sys/time.h>
# include	<string.h>
# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"

typedef struct s_main	t_main;
typedef struct s_philo
{
	int		id;
	int		right;
	int		left;
	int		f_left;
	int		f_right;
	int		t_start;
	int		t_stop;
	int		t_now;
	int		t_initial;
	int		t_crnt;
	int		yes_sleep;
	int		yes_eat;
	int		yes_think;
	int		l_nabr;
	int		r_nabr;
	int		l;
	int		r;
	int		sim;
	int		e;
	int		r_fork;
	int		l_fork;
	t_main	*m_info;
}	t_philo;
typedef struct s_main
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				e;
	int				l;
	int				s;
	int				count;
	int				t;
	int				d;
	int				d_yes;
	int				*forks;
	int				t_initial;
	int				f_died;
	int				f_print;
	t_philo			*phil;
	int				*ate;
	pthread_t		*philo;
	pthread_mutex_t	d_mut;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*a_mutex;
	pthread_mutex_t	p_mut;
	pthread_mutex_t	i_mut;
	pthread_mutex_t	c_mut;
	pthread_mutex_t	t_mut;
	pthread_mutex_t	ii_mut;
	pthread_mutex_t	l_mut;
}	t_main;

int		mang_struct(t_main *philo, char **argv);
int		is_valid(char **argv);
int		ft_atoi(const char *str);
int		mang_arrays(t_main *philo);

int		mang_fork(void *arg, int op);
void	init_forks(t_main *main);
int		is_fork(void *arg);
void	take_fork(void *arg);
void	put_fork(t_philo *dumb);

int		dumb_exist(t_main *main);
void	pre_dumb(t_philo *dumb, t_main *main);
void	init_dumb(t_philo *dumb, t_main	*main, int i);

void	*life_begin(void *arg);

void	count_for_dumb(t_philo *dumb, char what);
int		what_is_time_now(t_philo *dumb);
int		calc_tstamp(t_philo *dumb, char what);
int		check_death(t_philo *dumb);

int		mang_eat(void *arg, int op);
void	init_ate_arr(void *arg);
int		can_eat(void *arg);
int		did_eat(void *arg);
void	clear_ate_arr(void	*arg);

void	print_for_dumb(t_philo *dumb, char *str, char *code, char what);
int		f_died_lock(t_philo *dumb);
void	print_died(t_philo *dumb, char what);

void	init_mutex(t_main *main);
void	destroy_mutex(t_main *main);
void	free_arr(t_main *main);

void	eating(t_philo *dumb);
void	sleeping(t_philo *dumb);
void	thinking(t_philo *dumb);
void	dying(t_philo *dumb);

void	t_crnt(t_philo *dumb);
void	right_fork(t_philo *dumb);
void	left_fork(t_philo *dumb);
int		check_f_print(t_philo *dumb, int op);
void	check_death2(t_philo *dumb);

#endif