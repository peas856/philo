/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:59:47 by rhee              #+#    #+#             */
/*   Updated: 2021/06/22 16:27:58 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

// void        *monitor_count(void *state_v)
// {
// 	t_op    *data;
// 	int		i;
// 	int		total;

// 	data = (t_op *)state_v;
// 	total = 0;
// 	while (total < data->must_eat)
// 	{
// 		i = 0;
// 		while (i < data->n_philo)
// 			pthread_mutex_lock(&data->philo[i++].eat_m);
// 		total++;
// 	}
// 	pthread_mutex_unlock(&data->somebody_dead_m);
// 	return ((void*)0);
// }

void        *monitor_count(void *op_v)
{
	t_op    *op;
	int		total;

	op = (t_op *)op_v;
	total = 0;
	while (1)
	{
		if (op->finish_n == op->n_philo)
			break;
	}
	pthread_mutex_unlock(&op->killed);
	return ((void*)0);
}

void        *monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		if (!philo->is_eating && ft_time() > philo->dead_time)
		{
			display_msg(philo, 5);
			pthread_mutex_unlock(&philo->op->killed);
			return ((void*)0);
		}
		usleep(1000);
	}
}

void        *philosopher(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo*)philo_v;
	if (philo->op->n_philo == 1)
	{
		usleep(100);
		return ((void*)0);
	}
	philo->dead_time = ft_time() + philo->op->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, philo_v) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		clean_forks(philo);
		display_msg(philo, 3);
	}
	return ((void*)0);
}

int         ft_threads(t_op *data)
{
	int			i;
	pthread_t	tid;
	void		*philo;

	data->start = ft_time();
	if (data->must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void*)data) != 0)
			return (1);
		pthread_detach(tid);
	}
	i = 0;
	while (i < data->n_philo)
	{
		philo = (void*)(&data->philo[i]);
		if (pthread_create(&tid, NULL, &philosopher, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}