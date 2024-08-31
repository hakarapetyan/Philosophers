#include "philo.h"

void	*philosophers(void *data)
{
	int	i;
	t_philo *d;

	i = 0;
	d = (t_philo *)data;
	while (!stop_func(d, 0))
	{
		if (d->data->num_of_philo == 1)
			return (one_philo(data));
		philo_eat(d);
		philo_sleep(d);
	}
	return (NULL);
}

void create_thread(t_data *data)
{
	int	i;

	i = 0;
	data -> time_to_start = timestamp();
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->d_philo[i].thr, NULL, &philosophers, &(data->d_philo[i])))
			return ;
		i++;
	}
}

void join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(data->d_philo[i].thr, NULL))
			return ;
		i++;
	}
}