/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:23:51 by gcatarin          #+#    #+#             */
/*   Updated: 2023/11/05 20:17:43 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	dead_loop(t_philo *ph)
{
	pthread_mutex_lock(ph->dead_lock);
	if (ph->dead == 1)
		return (pthread_mutex_unlock(ph->dead_lock), 1);
	pthread_mutex_unlock(ph->dead_lock);
	return (0);
}

void	*ph_routine(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;
	if (ph->id % 2 == 0)
		usleep(1);
	while (!dead_loop(ph))
	{
		eating(ph);
		sleeping(ph);
		thinking(ph);
	}
	return (p);
}

char	*init_thread(t_data *d)
{
	pthread_t	master;
	int			i;
	
	if (pthread_create(&master, NULL, &monitor, d->ph) != 0)
		return ("Error creating thread master");
	i = 0;
	while (i < d->num_p)
	{
		if (pthread_create(&d->ph[i].thread, NULL, &ph_routine, &d->ph[i]) != 0)
			return ("Error creating thread philo");
		i++;
	}
	if (pthread_join(master, NULL) != 0)
		return ("Error joining master thread");
	i = 0;
	while (i < d->num_p)
	{
		if (pthread_join(d->ph[i].thread, NULL) != 0)
			return ("Error joining philo thread");
		i++;
	}
	return("good");
}
