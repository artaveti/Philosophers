/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:13:55 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 12:43:26 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo.h"

void	ft_malloc_for_mutexes(t_arguments *arguments, int quant)
{
	arguments->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * quant);
	arguments->for_last_eat_time = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * quant);
	arguments->for_eat_limit = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * quant);
	return ;
}

void	ft_assign_arguments(char *argv[], t_arguments *arguments)
{
	int	quant;
	int	i;

	quant = ft_atoi_for_philosophers(argv[1]);
	arguments->philos_quant = quant;
	arguments->forks_quant = quant;
	arguments->time_to_die = ft_atoi_for_philosophers(argv[2]);
	arguments->time_to_eat = ft_atoi_for_philosophers(argv[3]);
	arguments->time_to_sleep = ft_atoi_for_philosophers(argv[4]);
	if (argv[5])
		arguments->eat_limit = ft_atoi_for_philosophers(argv[5]);
	else
		arguments->eat_limit = -1;
	arguments->eat_limit_arr = (int *)malloc(sizeof(int) * quant);
	i = 0;
	while (i < quant)
	{
		arguments->eat_limit_arr[i] = 0;
		i++;
	}
	arguments->stop_prog = 0;
	arguments->philosophers = (t_philosopher *)
		malloc(sizeof(t_philosopher) * quant);
	ft_malloc_for_mutexes(arguments, quant);
	return ;
}

void	ft_assign_philosophers_arguments(int i, t_arguments *arguments)
{
	arguments->philosophers[i].num = i;
	arguments->philosophers[i].time_to_eat = &arguments->time_to_eat;
	arguments->philosophers[i].time_to_sleep = &arguments->time_to_sleep;
	arguments->philosophers[i].eat_quant = 0;
	arguments->philosophers[i].right_fork = i;
	if (i == arguments->philos_quant - 1)
		arguments->philosophers[i].left_fork = 0;
	else
		arguments->philosophers[i].left_fork = i + 1;
	arguments->philosophers[i].start_of_prog = &arguments->start_of_prog;
	arguments->philosophers[i].last_eat_time = arguments->start_of_prog;
	arguments->philosophers[i].stop_prog = &arguments->stop_prog;
	arguments->philosophers[i].philos_quant = &arguments->philos_quant;
	arguments->philosophers[i].forks = arguments->forks;
	arguments->philosophers[i].for_printf = &arguments->for_printf;
	arguments->philosophers[i].for_die_status = &arguments->for_die_status;
	arguments->philosophers[i].for_last_eat_time = arguments->for_last_eat_time;
	arguments->philosophers[i].for_eat_limit = arguments->for_eat_limit;
	return ;
}
