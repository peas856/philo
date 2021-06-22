/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:21:51 by rhee              #+#    #+#             */
/*   Updated: 2021/06/22 16:42:58 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosophers.h"

long	ft_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int     ft_err(char *s)
{
	if (s)
		printf("%s\n", s);
	return (1);
}

int ft_clear(t_op *op)
{
	int	i;

	if (op->philo)
	{
		i = 0;
		while (i < op->n_philo)
		{  
			pthread_mutex_destroy(&op->philo[i++].forks_m);
		}
		free(op->philo);
	}
	pthread_mutex_destroy(&op->msg);
	pthread_mutex_destroy(&op->killed);
	return (1);
}

int					ft_atoi(const char *str)
{
	long long		i;
	long long		ret;
	int				sign;

	i = 0;
	sign = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	ret = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + str[i] - '0';
		if (ret > 2147483647 && sign == 1)
			return (-1);
		if (ret > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return (ret * sign);
}

void	ft_usleep(int length)
{
	long	time;

	time = ft_time();
	while (ft_time() < time + length)
		usleep(length);
}