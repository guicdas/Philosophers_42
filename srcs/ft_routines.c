/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:47:43 by gcatarin          #+#    #+#             */
/*   Updated: 2023/11/05 20:19:12 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(t_philo *ph)
{
	print_msg("is thinking", ph, ph->id);
}

void	sleeping(t_philo *ph)
{
	print_msg("is sleeping", ph, ph->id);
	usleep(ph->tsleep);
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(ph->rightfork);
	print_msg("has taken his right fork", ph, ph->id);
	if (ph->num_p == 1)
	{
		usleep(ph->tdie);
		pthread_mutex_unlock(ph->rightfork);
		return ;
	}
	pthread_mutex_lock(&ph->leftfork);
	print_msg("has taken his left fork", ph, ph->id);
	ph->eating = 1;
	print_msg("is eating", ph, ph->id);
	pthread_mutex_lock(ph->meal_lock);
	ph->last_meal = get_time_now(ph->tstart);
	ph->n_eaten++;
	pthread_mutex_unlock(ph->meal_lock);
	usleep(ph->teat);
	ph->eating = 0;
	pthread_mutex_unlock(&ph->leftfork);
	pthread_mutex_unlock(ph->rightfork);
}
