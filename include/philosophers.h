#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

struct		s_philo;

typedef struct		s_op
{
	int	            n_philo;
	long        	time_to_die;
	long    		time_to_eat;
	long    		time_to_sleep;
	int	            must_eat;
    long    		start;
	struct s_philo	*philo;
	pthread_mutex_t	msg;
	pthread_mutex_t	killed;
	int				is_dead;
	int				finish_n;
}					t_op;

typedef struct		s_philo
{
	int				num;
	int				is_eating;
	long     		dead_time;
	int				eat_count;
	struct s_op 	*op;
	pthread_mutex_t	*prev;
	pthread_mutex_t	forks_m;
}					t_philo;

void				take_forks(t_philo *philo);
void				clean_forks(t_philo *philo);
void				eat(t_philo *philo);

long				ft_time(void);
int     			ft_err(char *s);
int					ft_atoi(char const *str);
int					ft_clear(t_op *op);

void        		ft_print(int option);
void				display_msg(t_philo *philo, int option);

int					ft_threads(t_op *data);
void				*philosopher(void *philo_v);
void				*monitor(void *philo_v);
void				*monitor_count(void *op_v);

#endif