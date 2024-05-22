/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:26:18 by jschaft           #+#    #+#             */
/*   Updated: 2024/05/21 11:08:52 by jschaft          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	put_intro(void)
{
	printf("  🌲 🌳 The Mischievous Elf's Forest 🌳 🌲\n");
	printf("_____________________________________________\n");
	printf("|__TIME___ID_______________ACTION___________|\n");
}

static void	put_one_philo(t_data data)
{
	put_message_quick(MSG_FORK, 0, 0);
	ft_usleep(data.time_die);
	put_message_quick(MSG_DIE, data.time_die, 0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("Error! Please give number of mischievous elfs, time to %s\n",
			"die, time to eat, time to sleep and if wanted number of turn.");
		return (0);
	}
	data = perror_management(data, ac, av);
	if (data.have_error == -1)
		return (0);
	if (data.nb_philo == 0)
	{
		printf("Error! Need elfs to cause chaos!\n");
		return (0);
	}
	data.dead = 0;
	put_intro();
	if (data.nb_philo == 1)
		put_one_philo(data);
	else
		threads_philo(&data);
	printf("|___________________________________________|\n");
}
