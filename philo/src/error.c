/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:26:18 by jschaft           #+#    #+#             */
/*   Updated: 2024/03/29 16:03:43 by jschaft          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static int	is_not_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	test_maxint(t_data data)
{
	if (data.time_die > 2147483647 || data.time_eat > 2147483647
		|| data.time_sleep > 2147483647 || data.turn > 2147483647)
	{
		printf("Error! Too big number for the mischievous elfs!");
		printf(" Must stay inside int limit!\n");
		return (-1);
	}
	return (0);
}

static t_data	fill_nb_data(int ac, char **av, t_data data)
{
	data.nb_philo = ft_atol(av[1]);
	data.time_die = ft_atol(av[2]);
	data.time_eat = ft_atol(av[3]);
	data.time_sleep = ft_atol(av[4]);
	if (ac == 6)
	{
		data.turn = ft_atol(av[5]);
		if (data.turn == 0)
		{
			printf("Error! The mischievous elfs must prank at least once!\n");
			data.have_error = -1;
			return (data);
		}
	}
	if (data.time_die < 60 || data.time_eat < 60 || data.time_sleep < 60)
	{
		printf("Error! The  mischievous elfs are not that fast!");
		printf(" At least 60ms for each action\n");
		data.have_error = -1;
		return (data);
	}
	if (ac == 5)
		data.turn = -1;
	data.have_error = test_maxint(data);
	return (data);
}

t_data	perror_management(t_data data, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_not_number(av[i]) == 1)
		{
			printf("Error! Give numbers only as arguments\n");
			data.have_error = -1;
			return (data);
		}
		i++;
	}
	data = fill_nb_data(ac, av, data);
	if (data.have_error == -1)
		return (data);
	if (data.nb_philo > 200)
	{
		printf("Error! Too many mischievous elfs! Too much chaos! 200 max\n");
		data.have_error = -1;
		return (data);
	}
	return (data);
}
