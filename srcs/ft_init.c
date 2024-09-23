/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:19:44 by gcatarin          #+#    #+#             */
/*   Updated: 2023/11/05 20:00:33 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init(t_philo *ph, char **av)
{
	ph->tdie = ft_atoi(av[2]);
	ph->teat = ft_atoi(av[3]);
	ph->tsleep = ft_atoi(av[4]);
	ph->eating = 0;
	ph->n_eaten = 0;
	if (av[5])
		ph->n_eat = ft_atoi(av[5]);
	else
		ph->n_eat = -1;
}

void	init_ph(t_data *prog, char **av)
{
	int	i;

	i = 0;
	while (i < prog->num_p)
	{
		prog->ph[i].id = i + 1;
		prog->ph[i].num_p = prog->num_p;
		init(&prog->ph[i], av);
		prog->ph[i].tstart = get_time();
		prog->ph[i].last_meal = get_time();
		prog->ph[i].write_lock = &prog->write_lock;
		prog->ph[i].dead_lock = &prog->dead_lock;
		prog->ph[i].meal_lock = &prog->meal_lock;
		prog->ph[i].dead = prog->dead;
		prog->ph[i].rightfork = NULL;
		pthread_mutex_init(&(prog->ph[i].leftfork), NULL);
		if (i == 0)
			prog->ph[i].rightfork = &prog->ph[0].leftfork;
		else
			prog->ph[i].rightfork = &prog->ph[i + 1].leftfork;
		i++;
	}
}

void	init_program(char **av, t_data *p)
{
	p->dead = 0;
	p->num_p = ft_atoi(av[1]);
	p->ph = malloc(sizeof(t_philo) * p->num_p);
	if (!p->ph)
		err("Error allocating ph pointer", p);
	pthread_mutex_init(&p->write_lock, NULL);
	pthread_mutex_init(&p->dead_lock, NULL);
	pthread_mutex_init(&p->meal_lock, NULL);
}
