/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:21:17 by rhee              #+#    #+#             */
/*   Updated: 2021/06/17 14:12:31 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

int         ft_mutexes(t_op *op)
{
	int	i;

	pthread_mutex_init(&op->write_m, NULL);
	pthread_mutex_init(&op->somebody_dead_m, NULL);
	pthread_mutex_lock(&op->somebody_dead_m);
	if (!(op->forks_m =
		(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * op->n_philo)))
		return (ft_err("error : malloc err\n"));
	i = 0;
	while (i < op->n_philo)
		pthread_mutex_init(&op->forks_m[i++], NULL);
	return (0);
}

void        ft_philos(t_op *op)
{
	int	i;

	i = 0;
	while (i < op->n_philo)
	{
		op->philo[i].is_eating = 0;
		op->philo[i].num = i;
		op->philo[i].left_fork = i;
		op->philo[i].right_fork = (i + 1) % op->n_philo;
		op->philo[i].eat_count = 0;
		op->philo[i].op = op;
		pthread_mutex_init(&op->philo[i].mutex, NULL);
		pthread_mutex_init(&op->philo[i].eat_m, NULL);
		pthread_mutex_lock(&op->philo[i].eat_m);
		i++;
	}
}

int         ft_init(t_op *op, int ac, char **av)
{
	op->n_philo = ft_atoi(av[1]);
	op->time_to_die = ft_atoi(av[2]);
	op->time_to_eat = ft_atoi(av[3]);
	op->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		op->must_eat = ft_atoi(av[5]);
	else
		op->must_eat = 0;
	// if (state->amount < 2 || state->amount > 200 || state->time_to_die < 60
	// 	|| state->time_to_eat < 60 || state->time_to_sleep < 60
	// 	|| state->must_eat_count < 0)
	// 	return (1);
	// state->forks_m = NULL;
	// state->philos = NULL;
	if (!(op->philo = (t_philo *)malloc(sizeof(t_philo) * op->n_philo)))
		return (ft_err("error : malloc err\n"));
	ft_philos(op);
	return (ft_mutexes(op));
}

int         main(int ac, char **av)
{
	t_op	op;

	if (!(ac == 5 || ac == 6))
		return (ft_err("error: Invalid arguments\n"));
	ft_init(&op, ac, av);
	start_threads(&op); //return (clear_state(&state) && exit_error("error: fatal\n"));
	pthread_mutex_lock(&state.somebody_dead_m);
	pthread_mutex_unlock(&state.somebody_dead_m);
	clear_state(&op);
	return (0);
}