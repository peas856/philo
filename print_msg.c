/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trhee <trhee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:21:09 by rhee              #+#    #+#             */
/*   Updated: 2021/06/23 14:55:56 by trhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

void				ft_print(int option)
{
	if (option == 0)
		printf(" is eating\n");
	else if (option == 1)
		printf(" is sleeping\n");
	else if (option == 2)
		printf(" has taken a fork\n");
	else if (option == 3)
		printf(" is thinking\n");
	else
		printf(" died\n");
}

void				display_msg(t_philo *philo, int option)
{
	pthread_mutex_lock(&philo->op->msg);
	if (!(philo->op->is_dead))
	{
		printf("%ld ", ft_time() - philo->op->start);
		printf("%d ", philo->num + 1);
		if (option == 5)
			philo->op->is_dead = 1;
		ft_print(option);
	}
	pthread_mutex_unlock(&philo->op->msg);
}
