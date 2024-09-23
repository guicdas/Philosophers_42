/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:45:19 by gcatarin          #+#    #+#             */
/*   Updated: 2023/11/05 20:08:28 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

char	*input_check(int ac, char **av)
{
	int		i;
	char	*s;

	i = 1;
	if (ac < 5 || ac > 6)
		return ("Wrong number of arguments");
	s = is_ascii(av);
	if (!ft_strcmp(s, "good"))
		return (s);
	while (i <= ac)
	{
		if (ft_atoi(av[i]) <= 0 && ft_atoi(av[i]) >= 2147483647)
			return ("argument wrong, all must be positive integers");
	}
	if (ac == 6)
	{
		if (ft_atoi(av[5]) < 0 && ft_atoi(av[i]) >= 2147483647)
			return ("5th argument wrong, must be an positive int or 0");
	}
	return ("good");
}

int	main(int argc, char **argv)
{
	char	*verify_input;
	char	*verify_threads;
	t_data	d;

	verify_input = input_check(argc, argv);
	init_program(argv, &d);
	if (ft_strcmp(verify_input, "good") == 0)
	{
		init_ph(&d, argv);
		verify_threads = init_thread(&d);
		if (ft_strcmp(verify_threads, "good") == 0)
			err("\nacabou", &d);
		else
			err(verify_threads, &d);
	}
	else
		err(verify_input, &d);
}
