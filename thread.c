/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:59:47 by rhee              #+#    #+#             */
/*   Updated: 2021/06/18 03:20:47 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void        *monitor_count(void *state_v)
{
	t_op    *data;
	int		i;
	int		total;

	data = (t_op *)state_v;
	total = 0;
	while (total < data->must_eat)
	{
		i = 0;
		while (i < data->n_philo)
			pthread_mutex_lock(&data->philo[i++].eat_m);
		total++;
	}
	pthread_mutex_unlock(&data->somebody_dead_m);
	return ((void*)0);
}

void        *monitor(void *philo_v)
{
	t_philo		*philo;
    struct timeval t;

	philo = (t_philo*)philo_v;
	while (1)
	{
        gettimeofday(&t, NULL);
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && t.tv_sec > philo->limit)
		{
			display_message(philo, 4);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->op->somebody_dead_m);
			return ((void*)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}

void        *routine(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;
    struct timeval  t;

    gettimeofday(&t, NULL);
	philo = (t_philo*)philo_v;
	philo->last_eat = t.tv_sec;
	philo->limit = philo->last_eat + philo->op->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, philo_v) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		clean_forks(philo);
		display_message(philo, 3);
	}
	return ((void*)0);
}

int         start_threads(t_op *data)
{
	int			i;
	pthread_t	tid;
	void		*philo;
    struct timeval t;

    gettimeofday(&t, NULL);
	data->start = t.tv_sec;
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
		if (pthread_create(&tid, NULL, &routine, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}