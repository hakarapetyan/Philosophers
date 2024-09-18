#include "philo.h"

// int stop_func(t_philo *d_philo, int nb)
// {
// 	pthread_mutex_lock(&(d_philo->data->mut_stop_time));
// 	if (nb)
// 		d_philo->stop_time = 1;
// 	if (d_philo->stop_time)
// 	{
// 		pthread_mutex_unlock(&(d_philo->data->mut_stop_time));
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&(d_philo->data->mut_stop_time));
// 	return (0);
// }

void *one_philo(void *phl)
{
	t_philo *philo = (t_philo *) phl; 
	print(philo,"has taken a fork\n");
	printf("%d %d %s", philo->data->time_to_die, philo->id, "died\n");
	return (NULL) ;
}

void	philo_eat(t_philo *d_philo)
{
		pthread_mutex_lock((d_philo->l_fork));
		print(d_philo, "has taken a fork\n");
		pthread_mutex_lock((d_philo->r_fork));
		print(d_philo, "has taken a fork\n");
		print(d_philo, "is eating\n");
		ft_usleep(d_philo->data->time_to_eat);
		pthread_mutex_unlock((d_philo->l_fork));
		pthread_mutex_unlock((d_philo->r_fork));
		pthread_mutex_lock(&(d_philo->data->mut_ate));
		d_philo->nb_ate++;
		pthread_mutex_unlock(&(d_philo->data->mut_ate));
		pthread_mutex_lock(&(d_philo->data->mut_last_eat));
		d_philo->last_eat_time = timestamp();
		pthread_mutex_unlock(&(d_philo->data->mut_last_eat));
}

void philo_sleep(t_philo *d_philo)
{
	print(d_philo, "is sleeping\n");
	ft_usleep(d_philo->data->time_to_sleep);
	print(d_philo, "is thinking\n");
}
