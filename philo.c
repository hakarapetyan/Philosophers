#include "philo.h"

int check_init_arg(t_data *data, int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		ft_error("INVALID NUMBER OF ARGUMENTS\n");
		return(1);
	}
	while (i < argc)
	{
	if (ft_atoi(argv[i]) <= 0)
	{
		printf("bye\n");
		printf("argv =%ld\n", ft_atoi(argv[i]));
		ft_error("INVALID ARGUMENT");
		return(1);
	}
		i++;
	}
	if (ft_atoi(argv[1]) < 1)
		return(1);
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	data ->must_eat_time = ft_atoi(argv[5]);
	else
	data -> must_eat_time = 0;

return(0);
}

int	main(int argc, char **argv)
{
	t_data data;
	if(check_init_arg(&data,argc,argv))
		return (0);
	init(&data);

	return (0);
}