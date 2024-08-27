#include "philo.h"

long int timestamp()
{
	struct timeval	time;
	long int		cur;

	gettimeofday(&time, NULL);
	cur = time.tv_sec  * 1000 + time.tv_usec / 1000;
	return (cur);
}

void print(t_data *data, char *str)
{
	long int	time;

	time = timestamp() - data->time_to_start;
	pthread_mutex_lock(&(data->print));
	if (time > 0)
		printf("%ld %d %s",time, data ->d_philo->id, str);
	pthread_mutex_unlock(&(data->print));
}

void ft_usleep(long int ms)
{
	long int	time;

	time = timestamp();
	while ((timestamp() - time) < ms)
		usleep (ms / 10);
}

void clear(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(data->print));
	pthread_mutex_destroy(&((*data->forks)));
	pthread_mutex_destroy(&(data->mut_ate));
	pthread_mutex_destroy(&(data->mut_last_eat));
	pthread_mutex_destroy(&(data->mut_die));
	pthread_mutex_destroy(&(data->mut_stop_time));
	while (i < data ->num_of_philo)
	{
		pthread_mutex_destroy((data->d_philo[i].l_fork));
		pthread_mutex_destroy((data->d_philo[i].r_fork));
		i++;
	}
		free(data->d_philo);
		free(data->forks);
}