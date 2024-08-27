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
		//printf("str[i]=%c\n",str[i]);
		result = result * 10 + (str[i] -48);
		i++;
	}
	//printf("str=%s\n",str);
	if (str[i] || str[i - 1] == '-' || str[i - 1] == '+')
	{
		ft_error("IS NOT ONLY DIGIT\n");
		return(0);
	}
	return (result * sign);
}

int	is_full(t_data	*data, t_philo philo)
{
	if (philo.nb_ate >= data->must_eat_time)
	return (1);
	else
	return (0);
}

int	 is_dead(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(data->mut_die));
	printf("dead\n");
	while (i < data->num_of_philo)
	{
		printf("last eat=%lu\n  i=%d\n", data->d_philo[i].last_eat_time,  i);
		printf("time_to_eat=%d\n", data -> time_to_eat);
	if ((int)(timestamp() - data->d_philo[i].last_eat_time) > data -> time_to_eat)
	{
		stop_func(data, 1);
		print(data,"died\n");
		pthread_mutex_unlock(&(data->mut_die));
		return (1);
	}
	else if (!is_full(data, data->d_philo[i]))
	{
		stop_func(data, 1);
		print(data,"died\n");
		pthread_mutex_unlock(&(data->mut_die));
		return (1);
	}
	i++;
	}
	pthread_mutex_unlock(&(data->mut_die));
	return(0);
}
