/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:48:05 by hakarape          #+#    #+#             */
/*   Updated: 2024/10/13 17:12:27 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*philosophers(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	if (philo->id % 2 == 0)
// 		ft_usleep(100);
// 	while (!is_sim_end(philo->data))
// 	{
// 		philo_eat(philo);
// 		philo_sleep(philo);
// 	}
// 	return (NULL);
// }
void *philosophers(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        ft_usleep(100);

    // Loop until the simulation ends
    while (1)
    {
        pthread_mutex_lock(&philo->data->mutex_new); // Lock before accessing shared data

        if (is_sim_end(philo))
        {
            pthread_mutex_unlock(&philo->data->mutex_new); // Unlock before breaking
            break;
        }

        pthread_mutex_unlock(&philo->data->mutex_new); // Unlock after checking

        // Perform eating and sleeping
        philo_eat(philo);
        philo_sleep(philo);
    }
    return (NULL);
}

int	get_nb_philos(t_data *data)
{
	int	nb;

	pthread_mutex_lock(&data->mut_getter);
	nb = data->num_of_philo;
	pthread_mutex_unlock(&data->mut_getter);
	return (nb);
}
int get_last_eat(t_philo *d_philo)
{
	int	eat;
	pthread_mutex_lock(&(d_philo->mut_last_eat));
	eat = d_philo->last_eat_time;
	pthread_mutex_unlock(&(d_philo->mut_last_eat));
	return (eat);
}
void	create_thread(t_data *data)
{
	int	i;
	int num = get_nb_philos(data);

	i = 0;
	data->time_to_start = timestamp();
	if (data->num_of_philo == 1)
	{
		pthread_create(&data->d_philo[0].thr, NULL, &one_philo,
			&(data->d_philo[0]));
		return ;
	}
	while (i < num)
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
	int num = get_nb_philos(data);

	i = 0;
	while (i < num)
	{
		pthread_join(data->d_philo[i].thr, NULL);
		i++;
	}
	return ;
}
