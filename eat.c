#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->op->forks_m[philo->left_fork]);
	display_message(philo, 2);
	pthread_mutex_lock(&philo->op->forks_m[philo->right_fork]);
	display_message(philo, 2);
}

void	clean_forks(t_philo *philo)
{
	display_message(philo, 1);
	pthread_mutex_unlock(&philo->op->forks_m[philo->left_fork]);
	pthread_mutex_unlock(&philo->op->forks_m[philo->right_fork]);
	usleep(philo->op->time_to_sleep * 1000);
}

void	eat(t_philo *philo)
{
	struct timeval t;

	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	gettimeofday(&t, NULL);
	philo->last_eat = t.tv_sec;
	philo->limit = philo->last_eat + philo->op->time_to_die;
	display_message(philo, 0);
	usleep(philo->op->time_to_eat * 1000);
	philo->eat_count++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->eat_m);
}