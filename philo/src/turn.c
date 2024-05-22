/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:26:18 by jschaft           #+#    #+#             */
/*   Updated: 2024/05/21 18:46:54 by jschaft          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	ft_usleep_stop(unsigned int ms, t_philo *philo)
{
	unsigned int	start;

	start = get_time();
	pthread_mutex_lock(&philo->m_eat);
	while (get_time() - start < ms && !philo->stop)
	{
		pthread_mutex_unlock(&philo->m_eat);
		usleep(ms / 10);
		pthread_mutex_lock(&philo->m_eat);
	}
	pthread_mutex_unlock(&philo->m_eat);
}

static void	philo_eat(t_philo *philo)
{
	if (philo->i % 2)
	{
		pthread_mutex_lock(&philo->l_fork);
		put_message(MSG_FORK, philo);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		put_message(MSG_FORK, philo);
		pthread_mutex_lock(&philo->l_fork);
	}
	put_message(MSG_FORK, philo);
	put_message(MSG_EAT, philo);
	pthread_mutex_lock(&philo->m_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->m_eat);
	if (philo->meal_left > 0)
		philo->meal_left--;
	ft_usleep(philo->data->time_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
}

static void	*check_death(void *arg)
{
	t_philo	*philo;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	ft_usleep_stop(philo->data->time_die + 1, philo);
	pthread_mutex_lock(&philo->m_eat);
	if (get_time() - philo->last_eat >= philo->data->time_die && !philo->stop)
	{
		pthread_mutex_lock(&philo->data->m_dead);
		pthread_mutex_lock(&philo->data->m_kill);
		if (!philo->data->dead && !philo->stop)
		{
			pthread_mutex_unlock(&philo->data->m_kill);
			put_message(MSG_DIE, philo);
			pthread_mutex_lock(&philo->data->m_kill);
		}
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->m_kill);
		pthread_mutex_unlock(&philo->data->m_dead);
	}
	pthread_mutex_unlock(&philo->m_eat);
	return (NULL);
}

void	*turn(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_eat = philo->started;
	if (philo->i % 2)
		ft_usleep(philo->data->time_eat);
	while (!philo->data->dead)
	{
		pthread_create(&philo->dead_threads, NULL, check_death, philo);
		philo_eat(philo);
		if (!philo->meal_left)
		{
			pthread_mutex_lock(&philo->m_eat);
			philo->stop = 1;
			pthread_mutex_unlock(&philo->m_eat);
			pthread_join(philo->dead_threads, NULL);
			return (NULL);
		}
		put_message(MSG_SLEEP, philo);
		ft_usleep(philo->data->time_sleep);
		put_message(MSG_THINK, philo);
		pthread_detach(philo->dead_threads);
	}
	return (NULL);
	return (NULL);
}
