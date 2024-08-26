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
	pthread_mutex_init(&(data->print), NULL);
	pthread_mutex_init(&((*data->forks)), NULL);
	pthread_mutex_init(&(data->mut_ate), NULL);
	pthread_mutex_init(&(data->mut_last_eat), NULL);
	pthread_mutex_init(&(data->mut_die), NULL);
	pthread_mutex_init(&(data->mut_stop_time), NULL);
}