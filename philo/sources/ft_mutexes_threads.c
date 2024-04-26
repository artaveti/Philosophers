/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutexes_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:15:09 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 12:17:20 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo.h"

void	ft_mutexes_init(t_arguments *arguments)
{
	int	i;

	i = 0;
	while (i < arguments->forks_quant)
	{
		pthread_mutex_init(&arguments->forks[i], NULL);
		pthread_mutex_init(&arguments->for_last_eat_time[i], NULL);
		pthread_mutex_init(&arguments->for_eat_limit[i], NULL);
		i++;
	}
	pthread_mutex_init(&arguments->for_printf, NULL);
	pthread_mutex_init(&arguments->for_die_status, NULL);
	return ;
}

void	ft_threads_creat(t_arguments *arguments)
{
	int	i;

	i = 0;
	while (i < arguments->philos_quant)
	{
		pthread_create(&arguments->philosophers[i].philos_thread, NULL,
			&ft_philo, &arguments->philosophers[i]);
		i++;
	}
	return ;
}

void	ft_threads_join(t_arguments *arguments)
{
	int	i;

	i = 0;
	while (i < arguments->philos_quant)
	{
		pthread_join(arguments->philosophers[i].philos_thread, NULL);
		i++;
	}
	return ;
}

void	ft_mutexes_destroy(t_arguments *arguments)
{
	int	i;

	i = 0;
	while (i < arguments->forks_quant)
	{
		pthread_mutex_destroy(&arguments->forks[i]);
		pthread_mutex_destroy(&arguments->for_last_eat_time[i]);
		pthread_mutex_destroy(&arguments->for_eat_limit[i]);
		i++;
	}
	pthread_mutex_destroy(&arguments->for_printf);
	pthread_mutex_destroy(&arguments->for_die_status);
	return ;
}
