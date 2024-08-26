#include "philo.h"
void init_philo(t_data *data)
{
	int	i;

	i = 0;

	data->time_to_start = timestamp();
	while (i < data->num_of_philo)
	{
		data->d_philo[i].id = i + 1;
		data->d_philo[i].last_eat_time = 0;
		data->d_philo[i].nb_ate = 0;
		data->d_philo[i].data = data;
		data->d_philo[i].stop_time = 0;
	}
}

void init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(data->print), NULL);
	pthread_mutex_init(&((*data->forks)), NULL);
	pthread_mutex_init(&(data->mut_ate), NULL);
	pthread_mutex_init(&(data->mut_last_eat), NULL);
	pthread_mutex_init(&(data->mut_die), NULL);
	pthread_mutex_init(&(data->mut_stop_time), NULL);
	while (i < data->num_of_philo)
	{
		if (i == data->num_of_philo - 1 )
		{
			data->d_philo[i].r_fork = &data->forks[i];
			data->d_philo[i].l_fork = &data->forks[0];
		}
		data->d_philo[i].r_fork = &data->forks[i];
		data->d_philo[i].l_fork = &data->forks[i + 1];
		i++;
	}

}
int alloc_struct(t_data *data)
{
	data->d_philo = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if(!data->d_philo)
	return(0);

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if(!data->forks)
	{
		free(data->d_philo);
		return(0);
	}
	return (0);
}

void init(t_data *data)
{
	alloc_struct(data);
	init_mutex(data);
	init_philo(data);
}