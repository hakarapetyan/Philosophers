/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:48:46 by hakarape          #+#    #+#             */
/*   Updated: 2024/10/13 16:54:03 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	func_time(t_data *data)
{
	int	i;
	int num = get_nb_philos(data);

	i = 0;
	while (i < num)
	{
		if ((int)(timestamp()
			- get_last_eat(&(data->d_philo[i]))) > data->time_to_die)
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

int	is_sim_end(t_philo *d_philo)
{
	int	tmp;

	pthread_mutex_lock(&d_philo->mut_stop_time);
	tmp = d_philo->stop_time;
	pthread_mutex_unlock(&d_philo->mut_stop_time);
	return (tmp);
}

void	end(t_data *data)
{
	int	i;
	int num = get_nb_philos(data);

	i = 0;
	while (i < num)
	{
		pthread_mutex_lock(&data->d_philo[i].mut_stop_time);
		data->d_philo[i].stop_time = 1;
		pthread_mutex_unlock(&data->d_philo[i].mut_stop_time);
		i++;
	}
}
