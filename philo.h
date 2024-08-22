#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo
{
	int 			id;
	struct s_data 	*data;
	unsigned long 	last_eat_time;
	int				nb_ate;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
}t_philo;

typedef struct s_data
{
	int num_of_philo;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	int must_eat_time;
	long int	time_to_start;
	t_philo *d_philo;
	pthread_mutex_t *forks;
	pthread_mutex_t	print;
	pthread_mutex_t	mut_ate;
	pthread_mutex_t	mut_last_eat;
	pthread_mutex_t	mut_die;
}t_data;

long		ft_atoi(char *str);
int			ft_error(char *str);
int			check_init_arg(t_data *data, int argc, char **argv);
long int 	timestamp();
void		print(t_data *data, char *str);
int			is_dead(t_data *data);
void		init_mutex(t_data *data);
int			alloc_struct(t_data *data);
void		init_philo(t_data *data);
void		init(t_data *data);
#endif