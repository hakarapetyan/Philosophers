/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:47:57 by hakarape          #+#    #+#             */
/*   Updated: 2024/10/07 14:17:37 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	timestamp(void)
{
	struct timeval	time;
	long int		cur;

	gettimeofday(&time, NULL);
	cur = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (cur);
}

void	print(t_philo *d_philo, char *str)
{
	long int	time;

	time = timestamp() - d_philo->data->time_to_start;
	if (!pthread_mutex_lock(&(d_philo->data->print)))
	{
		if (time >= 0 && d_philo->stop_time != 1)
		{
			printf("%ld %d %s", time, d_philo->id, str);
		}
		pthread_mutex_unlock(&(d_philo->data->print));
	}
	return ;
}

void	ft_usleep(long int ms)
{
	long int	time;

	time = timestamp();
	while ((timestamp() - time) < ms)
		usleep(500);
}

void	clear(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(data->print));
	pthread_mutex_destroy(&((*data->forks)));
	pthread_mutex_destroy(&(data->mut_ate));
	pthread_mutex_destroy(&(data->mut_last_eat));
	pthread_mutex_destroy(&(data->mut_die));
	pthread_mutex_destroy(&(data->mut_stop_time));
	pthread_mutex_destroy(&(data->mut_stop));
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	free(data->d_philo);
	free(data->forks);
}
