/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:49:04 by hakarape          #+#    #+#             */
/*   Updated: 2024/10/07 17:12:52 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_init_arg(&data, argc, argv))
		return (1);
	if (!init(&data))
	{
		create_thread(&data);
		if (data.num_of_philo == 1)
		{
			pthread_join(data.d_philo[0].thr, NULL);
			clear(&data);
			return (0);
		}
		while (is_dead(&data))
			;
		join_thread(&data);
		clear(&data);
		return (0);
	}
	return (1);
}
