/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:48:55 by hakarape          #+#    #+#             */
/*   Updated: 2024/10/07 17:16:54 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->time_to_start = 0;
	while (i < data->num_of_philo)
	{
		data->d_philo[i].stop_time = 0;
		data->d_philo[i].id = i + 1;
		data->d_philo[i].last_eat_time = timestamp();
		data->d_philo[i].nb_ate = 0;
		data->d_philo[i].data = data;
		i++;
	}
}

void	init_mutex_help(t_data *data)
{
	pthread_mutex_init(&(data->print), NULL);
	pthread_mutex_init(&(data->mut_ate), NULL);
	pthread_mutex_init(&(data->mut_last_eat), NULL);
	pthread_mutex_init(&(data->mut_die), NULL);
	pthread_mutex_init(&(data->mut_stop_time), NULL);
	pthread_mutex_init(&(data->mut_stop), NULL);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		if (i == data->num_of_philo - 1)
		{
			data->d_philo[i].r_fork = &data->forks[i];
			data->d_philo[i].l_fork = &data->forks[0];
		}
		else
		{
			data->d_philo[i].r_fork = &data->forks[i];
			data->d_philo[i].l_fork = &data->forks[i + 1];
		}
		i++;
	}
}

int	alloc_struct(t_data *data)
{
	data->d_philo = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->d_philo)
		return (1);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_of_philo);
	if (!data->forks)
	{
		free(data->d_philo);
		return (1);
	}
	return (0);
}

int	init(t_data *data)
{
	if (!alloc_struct(data))
	{
		init_mutex_help(data);
		init_mutex(data);
		init_philo(data);
		return (0);
	}
	return (1);
}
