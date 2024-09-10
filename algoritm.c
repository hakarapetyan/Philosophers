#include "philo.h"

int stop_func(t_philo *d_philo, int nb)
{
	pthread_mutex_lock(&(d_philo->data->mut_stop_time));
		if (nb)
			d_philo->stop_time = 1;
		if (d_philo->stop_time)
		{
			printf("baba\n");
			if (!pthread_mutex_unlock(&(d_philo->data->mut_stop_time)))
			return (1);
		}
		pthread_mutex_unlock(&(d_philo->data->mut_stop_time));
			return (0);
	}

void *one_philo(t_philo *philo)
{
	if (!pthread_mutex_lock((philo->l_fork)))
	{
		print(philo,"has taken a fork\n");
		ft_usleep(philo->data->time_to_die);
		print(philo,"3died\n");
		pthread_mutex_unlock((philo->l_fork));
	}
	return (NULL) ;
}

void	philo_eat(t_philo *d_philo)
{
		// if (pthread_mutex_lock((d_philo->l_fork)) != 0)
		// 	print(d_philo, "1has taken a fork\n");
		// if (!pthread_mutex_lock((d_philo->r_fork)))
		// {
		// 	print(d_philo, "2has taken a fork\n");
		// 	ft_usleep(d_philo->data->time_to_eat);
		// 	print(d_philo,"is eating\n");
		// }
		// if (!pthread_mutex_unlock((d_philo->l_fork)))
		// 	printf("hihi\n");
		// if (!pthread_mutex_unlock((d_philo->r_fork)))
		// 	printf("bye\n");
		// if (!pthread_mutex_lock(&(d_philo->data->mut_ate)))
		// {
		// 	d_philo->nb_ate++;
		// 	printf("nbate%d\n", d_philo->nb_ate);
		// 	pthread_mutex_unlock(&(d_philo->data->mut_ate));
		// }
		// if (!pthread_mutex_lock(&(d_philo->data->mut_last_eat)))
		// {
		// 	printf("dog\n");
		// 	d_philo->last_eat_time = timestamp();
		// 	pthread_mutex_unlock(&(d_philo->data->mut_last_eat));
		// }
		pthread_mutex_lock((d_philo->l_fork));
		print(d_philo, "has taken a fork\n");
		pthread_mutex_lock((d_philo->r_fork));
		print(d_philo, "has taken a fork\n");
		ft_usleep(d_philo->data->time_to_eat);
		print(d_philo, "is eating\n");
		pthread_mutex_unlock((d_philo->l_fork));
		pthread_mutex_unlock((d_philo->r_fork));
		pthread_mutex_lock(&(d_philo->data->mut_ate));
		d_philo->nb_ate++;
		pthread_mutex_unlock(&(d_philo->data->mut_ate));
		pthread_mutex_lock(&(d_philo->data->mut_last_eat));
		d_philo->last_eat_time = timestamp();
		pthread_mutex_unlock(&(d_philo->data->mut_last_eat));
}

void philo_sleep(t_philo *d_philo)
{
	print(d_philo, "is sleeping\n");
	ft_usleep(d_philo->data->time_to_sleep);
	print(d_philo,"is thinking\n");
}
