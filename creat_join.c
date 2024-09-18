#include "philo.h"

void	*philosophers(void *data)
{
	int	i;
	t_philo *d;

	i = 0;
	d = (t_philo *)data;
	if (d->id % 2 == 0)
		ft_usleep(d->data->time_to_eat);
	if (d->data->num_of_philo == 1)
		return (one_philo(d));
	if (d->data->eve_ate == 1)
	{
	while (d->stop_time != 1)
	{
		philo_eat(d);
		philo_sleep(d);
	}
	}
	return (NULL);
}

void create_thread(t_data *data)
{
	int	i;

	i = 0;
	data -> time_to_start = timestamp();
	if (data->num_of_philo == 1)
	{
		pthread_create(&data->d_philo[0].thr, NULL, &one_philo, &(data->d_philo[0]));
		return ;
	}
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->d_philo[i].thr, NULL, &philosophers, &(data->d_philo[i])))
			return ;
		
		i++;
	}
	pthread_mutex_lock(&(data->mut_eve_ate));
	data->eve_ate = 1;
	pthread_mutex_unlock(&(data->mut_eve_ate));
	
}

void join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->d_philo[i].thr, NULL);
		i++;
	}
	return ;
}