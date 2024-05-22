/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:15:04 by jschaft           #+#    #+#             */
/*   Updated: 2024/05/21 10:18:47 by jschaft          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	put_message_quick(char *msg, unsigned int time, int i)
{
	printf(msg, time, i + 1);
}

void	put_message(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_kill);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->m_kill);
		return ;
	}
	pthread_mutex_lock(&philo->data->m_write);
	if (!philo->data->dead)
		printf(msg, get_time() - philo->started, philo->i + 1);
	pthread_mutex_unlock(&philo->data->m_write);
	pthread_mutex_unlock(&philo->data->m_kill);
}
