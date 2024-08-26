#include "philo.h"

void	*philosophers(void *data)
{
	int	i;
	t_data *d;

	i = 0;
	d = (t_data *)data;
	while (!is_dead(data))
	{
		if (d->num_of_philo == 1)
			return (one_philo(data));
		philo_eat(data);
		philo_sleep(data);
	}
	return (NULL);
}

void creat_thread(t_data *data)
{
	int	i;

	i = 0;
	data -> time_to_start = timestamp();
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->d_philo[i].thr, NULL, &philosophers, &data))
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