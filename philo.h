/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:51:32 by hakarape          #+#    #+#             */
/*   Updated: 2024/10/13 16:31:20 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thr;
	struct s_data	*data;
	unsigned long	last_eat_time;
	int				nb_ate;
	int				stop_time;
	pthread_mutex_t	mut_last_eat;
	pthread_mutex_t	mut_stop_time;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				must_eat_time;
	long int		time_to_start;
	t_philo			*d_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	mut_ate;
	pthread_mutex_t	mut_die;
	pthread_mutex_t	mut_stop;
	pthread_mutex_t mut_getter;
	pthread_mutex_t mutex_new; 
}					t_data;

long				ft_atoi(char *str);
int					ft_error(char *str);
void				ft_usleep(long int ms);
int					check_init_arg(t_data *data, int argc, char **argv);
long int			timestamp(void);
void				print(t_philo *data, char *str);
int					is_full(t_philo *philo);
void				init_mutex(t_data *data);
int					alloc_struct(t_data *data);
void				init_philo(t_data *data);
int					init(t_data *data);
int					stop_func(t_philo *d_philo, int nb);
void				*one_philo(void *phl);
void				philo_eat(t_philo *data);
void				philo_sleep(t_philo *data);
void				*philosophers(void *data);
void				create_thread(t_data *data);
void				join_thread(t_data *data);
void				clear(t_data *data);
//void				stop_simulation(t_data *data);
int					is_dead(t_data *data);
int					func_time(t_data *data);
int					is_sim_end(t_philo *d_philo);
void				end(t_data *data);
void				init_mutex_help(t_data *data);
void				init_arg(t_data *data, int argc, char **argv);
int	get_nb_philos(t_data *data);
int get_last_eat(t_philo *d_philo);
#endif