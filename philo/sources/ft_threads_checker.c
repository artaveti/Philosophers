/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:53 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 12:54:11 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo.h"

int	ft_check_last_eat_time(t_arguments *arguments,
		long long int *current_time, int idx)
{
	pthread_mutex_lock(&arguments->for_last_eat_time[idx]);
	ft_timestamp(current_time);
	if (*current_time - arguments->philosophers[idx].last_eat_time
		> arguments->time_to_die)
	{
		pthread_mutex_lock(&arguments->for_die_status);
		arguments->stop_prog = 1;
		pthread_mutex_unlock(&arguments->for_die_status);
		pthread_mutex_lock(&arguments->for_printf);
		printf("%lld %d died\n", *current_time - arguments->start_of_prog,
			arguments->philosophers[idx].num + 1);
		pthread_mutex_unlock(&arguments->for_printf);
		return (1);
	}
	pthread_mutex_unlock(&arguments->for_last_eat_time[idx]);
	return (0);
}

int	ft_check_eat_limit(t_arguments *arguments, int idx)
{
	int	sum;
	int	i;

	sum = 0;
	i = 0;
	pthread_mutex_lock(&arguments->for_eat_limit[idx]);
	if (arguments->philosophers[idx].eat_quant > arguments->eat_limit)
		arguments->eat_limit_arr[idx] = 1;
	while (i < arguments->philos_quant)
	{
		sum += arguments->eat_limit_arr[i];
		i++;
	}
	if (arguments->eat_limit == -1)
		sum = 0;
	if (sum == arguments->philos_quant)
	{
		pthread_mutex_lock(&arguments->for_die_status);
		arguments->stop_prog = 1;
		pthread_mutex_unlock(&arguments->for_die_status);
		pthread_mutex_unlock(&arguments->for_eat_limit[idx]);
		return (1);
	}
	pthread_mutex_unlock(&arguments->for_eat_limit[idx]);
	return (0);
}

void	ft_threads_checker(t_arguments *arguments)
{
	long long int	current_time;
	int				i;

	while (arguments->stop_prog != 1)
	{
		i = 0;
		while (i < arguments->philos_quant)
		{
			if (ft_check_last_eat_time(arguments, &current_time, i) == 1)
				break ;
			if (ft_check_eat_limit(arguments, i) == 1)
				break ;
			i++;
		}
	}
	return ;
}
