/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:21:09 by rhee              #+#    #+#             */
/*   Updated: 2021/06/17 14:24:06 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"
// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died
char        *print_message(int option)
{
	if (option == 0)
		return (" is eating\n");
	else if (option == 1)
		return (" is sleeping\n");
	else if (option == 2)
		return (" has taken a fork\n");
	else if (option == 3)
		return (" is thinking\n");
	else if (option == 4)
		return (" died\n");
}

void        display_message(t_op *op, t_philo *philo, int option)
{
	static int	dead = 0;

	pthread_mutex_lock(&op->write_m);
	if (!dead)
	{
		printf("%u ", get_time() - op->start, 1);
		if (option != 4)
			printf("%d ", philo->num + 1);
		else
			dead = 1;
		print_message(option);
	}
	pthread_mutex_unlock(&op->write_m);
}