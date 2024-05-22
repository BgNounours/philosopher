/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:26:18 by jschaft           #+#    #+#             */
/*   Updated: 2024/05/21 18:47:12 by jschaft          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define MSG_FORK "|% 6u % 4u             has taken a spoon🥄|\n"
# define MSG_EAT "|% 6u % 4u     is eating the shroom soup🍄|\n"
# define MSG_SLEEP "|% 6u % 4u   is planning the next prank 😈|\n"
# define MSG_THINK "|% 6u % 4u          is being mischievous🧝|\n"
# define MSG_DIE "|% 6u % 4u                          died💀|\n"

typedef struct s_data
{
	long				nb_philo;
	long				time_eat;
	long				time_sleep;
	long				time_die;
	long				turn;
	pthread_mutex_t		m_dead;
	pthread_mutex_t		m_kill;
	int					dead;
	pthread_mutex_t		m_write;
	int					have_error;
}				t_data;

typedef struct s_philo
{
	int				stop;
	int				i;
	int				last_eat;
	int				meal_left;
	unsigned int	started;
	pthread_t		think_threads;
	pthread_t		dead_threads;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
}				t_philo;

long			ft_atol(const char *nptr);
unsigned int	get_time(void);
void			ft_usleep(unsigned int ms);

t_data			perror_management(t_data data, int ac, char **av);
void			threads_philo(t_data *data);
void			*turn(void *arg);

void			put_message_quick(char *msg, unsigned int time, int i);
void			put_message(char *msg, t_philo *philo);

#endif