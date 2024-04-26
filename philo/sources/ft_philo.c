/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:23:04 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 12:53:35 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo.h"

void	ft_usleep(int milliseconds)
{
	struct timeval	start;
	struct timeval	finish;

	gettimeofday(&start, NULL);
	gettimeofday(&finish, NULL);
	while ((finish.tv_sec - start.tv_sec) * 1000
		+ (finish.tv_usec - start.tv_usec) / 1000 < milliseconds)
	{
		usleep(10);
		gettimeofday(&finish, NULL);
	}
	return ;
}

void	ft_printf_for_philo(t_philosopher *philosopher,
			long long int *timestamp, int num)
{
	long long int	start;
	int				philo_n;

	start = *philosopher->start_of_prog;
	philo_n = philosopher->num + 1;
	pthread_mutex_lock(philosopher->for_printf);
	ft_timestamp(timestamp);
	if (num == 1)
		printf("%lld %d has taken a fork\n", *timestamp - start, philo_n);
	else if (num == 2)
		printf("%lld %d has taken a fork\n", *timestamp - start, philo_n);
	else if (num == 3)
		printf("%lld %d is eating\n", *timestamp - start, philo_n);
	else if (num == 4)
		printf("%lld %d is sleeping\n", *timestamp - start, philo_n);
	else if (num == 5)
		printf("%lld %d is thinking\n", *timestamp - start, philo_n);
	pthread_mutex_unlock(philosopher->for_printf);
	return ;
}

int	ft_check_die_status(t_philosopher *philosopher, int num)
{
	long long int	timestamp;

	pthread_mutex_lock(philosopher->for_die_status);
	if (*philosopher->stop_prog != 1)
	{
		ft_printf_for_philo(philosopher, &timestamp, num);
		pthread_mutex_unlock(philosopher->for_die_status);
		if (*philosopher->philos_quant == 1)
		{
			pthread_mutex_unlock(&philosopher->forks[philosopher->right_fork]);
			return (1);
		}
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philosopher->for_die_status);
		if (num == 2 || num == 3)
			pthread_mutex_unlock(&philosopher->forks[philosopher->left_fork]);
		if (num == 1 || num == 2 || num == 3)
			pthread_mutex_unlock(&philosopher->forks[philosopher->right_fork]);
	}
	return (1);
}

void	ft_assign_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->for_last_eat_time[philosopher->num]);
	ft_timestamp(&philosopher->last_eat_time);
	pthread_mutex_unlock(&philosopher->for_last_eat_time[philosopher->num]);
	ft_usleep(*philosopher->time_to_eat);
	pthread_mutex_lock(&philosopher->for_eat_limit[philosopher->num]);
	philosopher->eat_quant++;
	pthread_mutex_unlock(&philosopher->for_eat_limit[philosopher->num]);
	return ;
}

void	*ft_philo(void *argument)
{
	t_philosopher	*philosopher;

	philosopher = argument;
	if (philosopher->num % 2 == 0)
		usleep(2500);
	while (1)
	{
		pthread_mutex_lock(&philosopher->forks[philosopher->right_fork]);
		if (ft_check_die_status(philosopher, 1) == 1)
			break ;
		pthread_mutex_lock(&philosopher->forks[philosopher->left_fork]);
		if (ft_check_die_status(philosopher, 2) == 1)
			break ;
		if (ft_check_die_status(philosopher, 3) == 1)
			break ;
		ft_assign_eat(philosopher);
		pthread_mutex_unlock(&philosopher->forks[philosopher->right_fork]);
		pthread_mutex_unlock(&philosopher->forks[philosopher->left_fork]);
		if (ft_check_die_status(philosopher, 4) == 1)
			break ;
		ft_usleep(*philosopher->time_to_sleep);
		if (ft_check_die_status(philosopher, 5) == 1)
			break ;
	}
	return (NULL);
}
