/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:24:49 by hakarape          #+#    #+#             */
/*   Updated: 2024/10/07 16:33:07 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (0);
}

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] || str[i - 1] == '-' || str[i - 1] == '+')
	{
		ft_error("IS NOT ONLY DIGIT\n");
		return (0);
	}
	return (result * sign);
}

void	init_arg(t_data *data, int argc, char **argv)
{
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_time = ft_atoi(argv[5]);
	else
		data->must_eat_time = -1;
}

int	check_init_arg(t_data *data, int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		ft_error("INVALID NUMBER OF ARGUMENTS\n");
		return (1);
	}
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0 || ft_atoi(argv[i]) > 2147483647)
		{
			ft_error("INVALID ARGUMENT");
			return (1);
		}
		i++;
	}
	if (ft_atoi(argv[1]) < 1)
		return (1);
	init_arg(data, argc, argv);
	return (0);
}
