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

int	is_full(t_philo *d_philo)
{
	int	nb_ate = 0; 

	if (pthread_mutex_lock(&(d_philo->data->mut_ate)) == 0)
	{
		nb_ate = d_philo->nb_ate;
		pthread_mutex_unlock(&(d_philo->data->mut_ate)); 
	}
	if (nb_ate >= d_philo->data->must_eat_time)
		return (1);
	return (0);
}


int	 is_dead(t_data *data, t_philo *d_philo)
{
	int	i;

	i = 0;

	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&(data->mut_die));
		if (!is_full(&data->d_philo[i]))
		{
			pthread_mutex_unlock(&(data->mut_die));
			return (0);
		}
		// else
		// {
		// 	//stop_func(d_philo, 1);
		// 	i = 0;
		// 	while (i < data->num_of_philo)
		// 	{
		// 		pthread_mutex_lock(&(d_philo->data->mut_stop_time));
		// 		d_philo[i].stop_time = 1;
		// 		pthread_mutex_unlock(&(d_philo->data->mut_stop_time));
		// 		i++;
		// 	}
		// 	// printf("%ld %d %s", timestamp() - d_philo -> data ->time_to_start, d_philo->id, "2died\n");
		// 	pthread_mutex_unlock(&(data->mut_die));
		// 	return(1);
		// }
		else if ((int)(timestamp() - data->d_philo[i].last_eat_time) > data -> time_to_die)
		{
			// stop_func(d_philo, 1);
			while (i < data->num_of_philo)
			{
				pthread_mutex_lock(&(d_philo->data->mut_stop_time));
				d_philo[i].stop_time = 1;
				pthread_mutex_unlock(&(d_philo->data->mut_stop_time));
				i++;
			}
			printf("%ld %d %s", timestamp() - d_philo -> data ->time_to_start, d_philo->id, "1died\n");
			pthread_mutex_unlock(&(data->mut_die));
			return (1);
		}
		else
		{
			i = 0;
			while (i < data->num_of_philo)
			{
				pthread_mutex_lock(&(d_philo->data->mut_stop_time));
				d_philo[i].stop_time = 1;
				pthread_mutex_unlock(&(d_philo->data->mut_stop_time));
				i++;
			}
			// printf("%ld %d %s", timestamp() - d_philo -> data ->time_to_start, d_philo->id, "2died\n");
			pthread_mutex_unlock(&(data->mut_die));
			return(1);
		}	
		i++;
	}
	pthread_mutex_unlock(&(data->mut_die));
			return(1);
		//stop_func(d_philo, 1);
		//stop_func(d_philo, 1);
		// i = 0;
		// while (i < data->num_of_philo)
		// 	{
		// 		d_philo[i].stop_time = 1;
		// 		i++;
		// 	}
		// printf("%ld %d %s", timestamp() - d_philo -> data ->time_to_start, d_philo->id, "3died\n");
		// pthread_mutex_unlock(&(data->mut_die));
		// return (1);
}
