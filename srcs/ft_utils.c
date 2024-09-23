/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:47:03 by gcatarin          #+#    #+#             */
/*   Updated: 2023/11/05 19:42:47 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	err(char *str, t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->num_p)
	{
		pthread_mutex_destroy(&d->ph[i].leftfork);
		pthread_mutex_destroy(d->ph[i].rightfork);
	}
	free(d->ph);
	pthread_mutex_destroy(&d->write_lock);
	pthread_mutex_destroy(&d->dead_lock);
	pthread_mutex_destroy(&d->meal_lock);
	printf("%s!\n", str);
}

int	ft_atoi(char *str)
{
	long int	num;

	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str >= '0' && *str <= '9')
		num = num * 10 + (*str++ - 48);
	return (num);
}

char	*is_ascii(char *s[])
{
	int	i;
	int	j;

	i = 1;
	while (s[i])
	{
		if (ft_strcmp(s[i], "") == 0)
			return ("Empty argument");
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] < '0' || s[i][j] > '9')
				return ("Invalid character");
			j++;
		}
		i++;
	}
	return ("good");
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s1[n])
		n++;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (n == i)
		return (0);
	return (s1[i] - s2[i]);
}
