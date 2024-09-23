/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:44:26 by gcatarin          #+#    #+#             */
/*   Updated: 2023/11/05 20:54:22 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> //gettimeofday()
# include <pthread.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	size_t			tdie;
	size_t			teat;
	size_t			tsleep;
	size_t			tstart;
	size_t			last_meal;
	int				n_eat;
	int				n_eaten;
	int				dead;
	int				num_p;
	int				eating;
	pthread_mutex_t	leftfork;
	pthread_mutex_t	*rightfork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	struct t_data		*data;
}t_philo;

typedef struct s_data
{
	int				dead;
	int				num_p;
	t_philo			*ph;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}t_data;

/////////// UTILS ///////////// 
char	*is_ascii(char *s[]);
int		ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);

///////////// INIT ////////////
void	init_program(char **av, t_data *p);
void	init_ph(t_data *d, char **av);
void	init(t_philo *ph, char **av);

char	*init_thread(t_data *p);
void	print_msg(char *s, t_philo *ph, int id);
int		check_if_all_ate(t_philo *ph);
int		check_if_dead(t_philo *ph);
int		dead_loop(t_philo *ph);

/////////////   TIME   /////////////
size_t	get_time(void);
size_t	get_time_now(size_t start);

///////////// ROUTINES /////////////
void	*monitor(void *p);
void	*ph_routine(void *p);
void	eating(t_philo *ph);
void	sleeping(t_philo *ph);
void	thinking(t_philo *ph);

///////////// /////////////////
void	err(char *str, t_data *d);
