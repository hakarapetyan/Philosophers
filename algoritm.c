#include "philo.h"

int stop_func(t_data *data, int nb)
{
	pthread_mutex_lock(&(data->mut_stop_time));
	if (nb)
	data->d_philo->stop_time = 1;
	if (data->d_philo->stop_time)
	{
		pthread_mutex_unlock(&(data->mut_stop_time));
		return (1);
	}
	pthread_mutex_unlock(&(data->mut_stop_time));
	return (0);
}

void *one_philo(t_data *data)
{
	pthread_mutex_lock((data->d_philo->l_fork));
	print(data,"has taken a fork\n");
	ft_usleep(data->time_to_die);
	print(data,"died\n");
	pthread_mutex_unlock((data->d_philo->l_fork));
	return (NULL);
}

void	philo_eat(t_data *data)
{
		pthread_mutex_lock((data->d_philo->l_fork));
		print(data,"has taken a fork\n");
		pthread_mutex_lock((data->d_philo->r_fork));
		print(data,"has taken a fork\n");
		ft_usleep(data->time_to_eat);
		print(data,"is eating\n");
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
	ft_usleep(data->time_to_sleep);
	print(data,"is thinking\n");
}
