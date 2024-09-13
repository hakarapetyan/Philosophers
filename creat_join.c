#include "philo.h"

void	*philosophers(void *data)
{
	int	i;
	t_philo *d;

	i = 0;
	d = (t_philo *)data;
	if (d->id % 2 == 0)
		ft_usleep(d->data->time_to_eat);
	while (!stop_func(d, 0))
	{
		if (d->data->num_of_philo == 1)
			return (one_philo(d));
		philo_eat(d);
		philo_sleep(d);
	}
	printf("hihi\n");
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
	if (pthread_join(data->d_philo[i].thr, NULL) != 0)
	{
		printf("no\n");
		return ;
	}
	i++;
	i++;
	printf("philo nmb -> %d\n", data->num_of_philo);
	if (pthread_join(data->d_philo[i].thr, NULL) != 0)
	{
		printf("no\n");
		return ;
	}
	// while (i < data->num_of_philo)
	// {
	// 	printf("i=%d\n", i);
	// 	if (pthread_join(data->d_philo[i].thr, NULL) == 0)
	// 	{
	// 		printf("no\n");
	// 		return ;
	// 	}
	// 	i++;
	// }
	return ;
}