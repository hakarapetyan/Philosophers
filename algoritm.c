#include "philo.h"

void one_philo(t_data *data)
{
	pthread_mutex_lock((data->d_philo->l_fork));
	usleep(data->time_to_die * 1000);
	print(data,"died\n");
	pthread_mutex_unlock((data->d_philo->l_fork));
}
void	eat(t_data *data)
{
		pthread_mutex_lock((data->d_philo->l_fork));
		print(data,"has taken a forl_k\n");
		pthread_mutex_lock((data->d_philo->r_fork));
		print(data,"has taken a fork\n");
		usleep(data->time_to_eat * 1000);
		print(data,"is eating");
		pthread_mutex_unlock((data->d_philo->l_fork));
		pthread_mutex_unlock((data->d_philo->r_fork));
		pthread_mutex_lock(&(data->mut_ate));
		data->d_philo->nb_ate++;
		pthread_mutex_unlock(&(data->mut_ate));
		pthread_mutex_lock(&(data->mut_last_eat));
		data->d_philo->last_eat_time = timestamp();
		pthread_mutex_unlock(&(data->mut_last_eat));
}

void philo_sleep(t_data *data)
{
	print(data, "is sleeping\n");
	usleep(data->time_to_sleep * 1000);
	print(data,"is thinking\n");
}

void *