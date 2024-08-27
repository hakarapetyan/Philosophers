#include "philo.h"

void	*philosophers(void *data)
{
	int	i;
	t_data *d;

	i = 0;
	d = (t_data *)data;
	printf("hi\n");
	while (!stop_func(data, 0))
	{
		printf("good\n");
		if (d->num_of_philo == 1)
			return (one_philo(data));
		// philo_eat(data);
		// philo_sleep(data);
	}
	return (NULL);
}

void create_thread(t_data *data)
{
	int	i;

	i = 0;
	printf("time =%ld", data->time_to_start);
	data -> time_to_start = timestamp();
	printf("time =%ld", data->time_to_start);
	while (i < data->num_of_philo)
	{
		printf("bye\n");
		if (pthread_create(&data->d_philo[i].thr, NULL, &philosophers, data))
			return ;
		printf("door\n");
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