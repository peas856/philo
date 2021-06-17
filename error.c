/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:21:51 by rhee              #+#    #+#             */
/*   Updated: 2021/06/18 02:49:07 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

int     ft_err(char *s)
{
	if (s)
		printf("%s\n", s);
	return (0);
}

int clear_state(t_op *state)
{
	int	i;

	if (state->forks_m)
	{
		i = 0;
		while (i < state->n_philo)
			pthread_mutex_destroy(&state->forks_m[i++]);
		free(state->forks_m);
	}
	if (state->philo)
	{
		i = 0;
		while (i < state->n_philo)
		{
			pthread_mutex_destroy(&state->philo[i].mutex);
			pthread_mutex_destroy(&state->philo[i++].eat_m);
		}
		free(state->philo);
	}
	pthread_mutex_destroy(&state->write_m);
	pthread_mutex_destroy(&state->somebody_dead_m);
	return (1);
}

