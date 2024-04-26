/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:33:33 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 13:33:49 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo_bonus.h"

void	ft_assign_arguments(char *argv[], t_arguments *arguments)
{
	int	quant;
	int	i;

	quant = ft_atoi_for_philosophers(argv[1]);
	arguments->philos_quant = quant;
	arguments->forks_quant = quant;
	arguments->process_ids = (pid_t *)malloc(sizeof(pid_t) * quant);
	i = 0;
	while (i < quant)
	{
		arguments->process_ids[i] = 0;
		i++;
	}
	return ;
}

void	ft_assign_philosopher_arguments(char *argv[],
			t_philosopher *philosopher, t_arguments *arguments)
{
	philosopher->forks_quant = ft_atoi_for_philosophers(argv[1]);
	philosopher->time_to_die = ft_atoi_for_philosophers(argv[2]);
	philosopher->time_to_eat = ft_atoi_for_philosophers(argv[3]);
	philosopher->time_to_sleep = ft_atoi_for_philosophers(argv[4]);
	if (argv[5])
		philosopher->eat_limit = ft_atoi_for_philosophers(argv[5]);
	else
		philosopher->eat_limit = -1;
	philosopher->eat_quant = 0;
	philosopher->start_of_prog = arguments->start_of_prog;
	philosopher->last_eat_time = arguments->start_of_prog;
	philosopher->stop_prog_philo_die = 0;
	philosopher->stop_prog_eat_quant = 0;
	philosopher->sem_eat_limit = philosopher->sem_eat_limit;
	return ;
}
