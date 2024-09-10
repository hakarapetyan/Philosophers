#include "philo.h"

void	*philosophers(void *data)
{
	int	i;
	t_philo *d;

	i = 0;
	d = (t_philo *)data;
	if (d->id % 2 == 0)
		ft_usleep(500);
	while (!stop_func(d, 0))
	{
		printf("stop_time22 = %d\n", d->stop_time);
		if (d->data->num_of_philo == 1)
			return (one_philo(d));
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
		printf("i=%d\n", i);
		if (pthread_join(data->d_philo[i].thr, NULL))
			return ;
		i++;
		printf("juni\n");
	}
}