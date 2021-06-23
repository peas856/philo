/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trhee <trhee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:21:17 by rhee              #+#    #+#             */
/*   Updated: 2021/06/23 15:00:44 by trhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void			ft_philo(t_op *op)
{
	int			i;

	i = 0;
	while (i < op->n_philo)
	{
		op->philo[i].is_eating = 0;
		op->philo[i].num = i;
		op->philo[i].eat_count = 0;
		op->philo[i].op = op;
		op->philo[i].prev = (i != 0) ? &op->philo[i - 1].forks_m : NULL;
		pthread_mutex_init(&op->philo[i].forks_m, NULL);
		i++;
	}
	op->philo[0].prev = &op->philo[op->n_philo - 1].forks_m;
	pthread_mutex_init(&op->msg, NULL);
	pthread_mutex_init(&op->killed, NULL);
	pthread_mutex_lock(&op->killed);
}

int				ft_parse(t_op *op, int ac, char **av)
{
	op->n_philo = ft_atoi(av[1]);
	op->time_to_die = ft_atoi(av[2]);
	op->time_to_eat = ft_atoi(av[3]);
	op->time_to_sleep = ft_atoi(av[4]);
	op->is_dead = 0;
	op->finish_n = 0;
	if (ac == 6)
		op->must_eat = ft_atoi(av[5]);
	else
		op->must_eat = -1;
	op->philo = NULL;
	if (!(op->philo = (t_philo *)malloc(sizeof(t_philo) * op->n_philo)))
		return (ft_err("error : malloc err\n"));
	return (0);
}

int				main(int ac, char **av)
{
	t_op		op;

	if (!(ac == 5 || ac == 6))
		return (ft_err("error: Invalid arguments\n"));
	if (ft_parse(&op, ac, av))
		return (ft_clear(&op));
	ft_philo(&op);
	ft_threads(&op);
	if (op.n_philo == 1)
	{
		ft_usleep(op.time_to_die);
		display_msg(&op.philo[0], 5);
		pthread_mutex_unlock(&op.killed);
	}
	pthread_mutex_lock(&op.killed);
	pthread_mutex_unlock(&op.killed);
	ft_clear(&op);
	return (0);
}
