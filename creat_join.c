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
	{
		printf("one\n");
		return (one_philo(d));
	}
	while (d->stop_time != 1)
	{
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
	if (data->num_of_philo == 1)
		pthread_detach(data->d_philo[0].thr);
}

void join_thread(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_philo == 1)
	{
		pthread_detach(data->d_philo[0].thr);
		return ;
	}
	while (i < data->num_of_philo)
	{
		printf("gogog\n");
		pthread_join(data->d_philo[i].thr, NULL);
		i++;
	}
	return ;
}