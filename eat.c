/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 04:02:19 by rhee              #+#    #+#             */
/*   Updated: 2021/06/22 16:45:18 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->prev);
	display_msg(philo, 2);
	pthread_mutex_lock(&philo->forks_m);
	display_msg(philo, 2);
	
}

void	clean_forks(t_philo *philo)
{
	display_msg(philo, 1);
	pthread_mutex_unlock(philo->prev);
	pthread_mutex_unlock(&philo->forks_m);
	ft_usleep(philo->op->time_to_sleep);
}

void	eat(t_philo *philo)
{
	philo->is_eating = 1;
	philo->dead_time = ft_time() + philo->op->time_to_die;
	display_msg(philo, 0);
	ft_usleep(philo->op->time_to_eat);
	philo->eat_count++;
	if (philo->eat_count == philo->op->must_eat)
		philo->op->finish_n++;
	philo->is_eating = 0;
}