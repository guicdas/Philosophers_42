/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_master.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:53:32 by gcatarin          #+#    #+#             */
/*   Updated: 2023/11/05 20:55:31 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_msg(char *s, t_philo *ph, int id)
{
	size_t	time;

	pthread_mutex_lock(ph->write_lock);
	time = get_time_now(ph->tstart);
	if (!dead_loop(ph))
		printf("%zu %d %s\n", time, id, s);
	pthread_mutex_unlock(ph->write_lock);
}

int	philosopher_dead(t_philo *ph, size_t tdie)
{
	pthread_mutex_lock(ph->meal_lock);
	if (get_time_now(ph->last_meal) >= tdie && ph->eating == 0)
		return (pthread_mutex_unlock(ph->meal_lock), 1);
	pthread_mutex_unlock(ph->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph[0].num_p)
	{
		if (philosopher_dead(&ph[i], ph[i].tdie))
		{
			print_msg("died", &ph[i], ph[i].id);
			pthread_mutex_lock(ph[0].dead_lock);
			ph->dead = 1;
			pthread_mutex_unlock(ph[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *ph)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (ph[0].n_eat == -1)
		return (0);
	while (i < ph[0].num_p)
	{print_msg("AQUIIIIIIIIIIIIIIIII", &ph[2], ph[2].n_eaten);
;		pthread_mutex_lock(ph[i].meal_lock);
		if (ph[i].n_eaten >= ph[i].n_eat)
			finished_eating++;
		pthread_mutex_unlock(ph[i].meal_lock);
		i++;
	}
	if (finished_eating == ph[0].num_p)
	{
		pthread_mutex_lock(ph[0].dead_lock);
		ph->dead = 1;
		pthread_mutex_unlock(ph[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;
	while (1)
		if (check_if_dead(ph) == 1 || check_if_all_ate(ph) == 1)
			break ;
	return (p);
}
