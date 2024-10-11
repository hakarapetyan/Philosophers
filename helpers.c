/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:48:46 by hakarape          #+#    #+#             */
/*   Updated: 2024/10/08 17:33:12 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	func_time(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if ((int)(timestamp()
			- data->d_philo[i].last_eat_time) > data->time_to_die)
		{
			end(data);
			pthread_mutex_lock(&(data->print));
			printf("%ld %d died\n", timestamp() - data->time_to_start,
				data->d_philo[i].id);
			pthread_mutex_unlock(&(data->print));
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_full(t_philo *d_philo)
{
	int	nb_ate;

	pthread_mutex_lock(&(d_philo->data->mut_ate));
	nb_ate = d_philo->nb_ate;
	pthread_mutex_unlock(&(d_philo->data->mut_ate));
	return (nb_ate >= d_philo->data->must_eat_time
		&& d_philo->data->must_eat_time > 0);
}

int	is_dead(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->mut_die);
	if (func_time(data))
	{
		pthread_mutex_unlock(&(data->mut_die));
		return (0);
	}
	while (i < data->num_of_philo)
	{
		if (!is_full(&data->d_philo[i]))
		{
			pthread_mutex_unlock(&(data->mut_die));
			return (1);
		}
		i++;
	}
	end(data);
	pthread_mutex_unlock(&(data->mut_die));
	return (0);
}

int	is_sim_end(t_data *data)
{
	int	tmp;

	pthread_mutex_lock(&data->mut_stop_time);
	tmp = data->d_philo->stop_time;
	pthread_mutex_unlock(&data->mut_stop_time);
	return (tmp);
}

void	end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->mut_stop);
		data->d_philo[i].stop_time = 1;
		pthread_mutex_unlock(&data->mut_stop);
		i++;
	}
}
