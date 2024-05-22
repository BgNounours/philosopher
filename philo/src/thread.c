/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:26:18 by jschaft           #+#    #+#             */
/*   Updated: 2024/05/21 18:46:41 by jschaft          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	free_philo(t_philo **phi)
{
	int	i;

	i = -1;
	while (phi[++i])
		free(phi[i]);
	free(phi);
}

void	init_threads(t_philo **philo, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (i == n_philo - 1)
			philo[i]->r_fork = &philo[0]->l_fork;
		else
			philo[i]->r_fork = &philo[i + 1]->l_fork;
		philo[i]->started = get_time();
		pthread_create(&philo[i]->think_threads, NULL, turn, philo[i]);
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		pthread_join(philo[i]->think_threads, NULL);
		i++;
	}
}

void	threads_philo(t_data *data)
{
	t_philo	**philo;
	int		i;

	philo = malloc(sizeof(t_philo *) * (data->nb_philo + 1));
	i = 0;
	pthread_mutex_init(&data->m_dead, NULL);
	pthread_mutex_init(&data->m_write, NULL);
	pthread_mutex_init(&data->m_kill, NULL);
	while (i < data->nb_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->data = data;
		philo[i]->i = i;
		philo[i]->meal_left = data->turn;
		philo[i]->stop = 0;
		pthread_mutex_init(&philo[i]->l_fork, NULL);
		pthread_mutex_init(&philo[i]->m_eat, NULL);
		i++;
	}
	philo[i] = NULL;
	init_threads(philo, (int)data->nb_philo);
	free_philo(philo);
}
