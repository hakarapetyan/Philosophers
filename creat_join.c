/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:48:05 by hakarape          #+#    #+#             */
/*   Updated: 2024/09/25 19:55:48 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!is_sim_end(philo->data))
	{
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	create_thread(t_data *data)
{
	int	i;

	i = 0;
	data->time_to_start = timestamp();
	if (data->num_of_philo == 1)
	{
		pthread_create(&data->d_philo[0].thr, NULL, &one_philo,
			&(data->d_philo[0]));
		return ;
	}
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->d_philo[i].thr, NULL, &philosophers,
				&(data->d_philo[i])))
			return ;
		i++;
	}
}

void	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->d_philo[i].thr, NULL);
		i++;
	}
	return ;
}
