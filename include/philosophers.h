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
	long        time_to_die;
	long    	time_to_eat;
	long    	time_to_sleep;
	int	            must_eat;
    long    	start;
	struct s_philo	*philo;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	somebody_dead_m;
}					t_op;

typedef struct		s_philo
{
	int				num;
	int				is_eating;
	long     		limit;
	long     		last_eat;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	struct s_op 	*op;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_m;
}					t_philo;


int     ft_err(char *s);

int					ft_strlen(char const *str);

int					ft_atoi(char const *str);

void				ft_putnbr_fd(uint64_t n, int fd);

int					clear_state(t_op *state);

int					exit_error(char const *str);

int					init(t_op *state, int argc, char const **argv);

void				take_forks(t_philo *philo);

void				clean_forks(t_philo *philo);

void				eat(t_philo *philo);

void				display_message(t_philo *philo, int option);

int         start_threads(t_op *data);
void        *routine(void *philo_v);
void        *monitor(void *philo_v);
void        *monitor_count(void *state_v);

char        *print_message(int option);

#endif