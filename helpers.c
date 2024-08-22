#include "philo.h"

int	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	return(0);
}
long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0 ;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] -48);
		i++;
	}
	if (str[i] || str[i - 1] == '-' || str[i - 1] == '+')
	{
		ft_error("IS NOT ONLY DIGIT\n");
		return(0);
	}
	return (result * sign);
}

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

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&(data->mut_die));
	if ((int)(timestamp() - data->d_philo->last_eat_time) > data -> time_to_eat)
		return (1);
	pthread_mutex_unlock(&(data->mut_die));
	return(0);
}