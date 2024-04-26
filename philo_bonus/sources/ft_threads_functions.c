/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:59:17 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 15:00:26 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo_bonus.h"

void	ft_check_philo_die_status(t_philosopher *philosopher)
{
	sem_wait(philosopher->sem_die_status);
	ft_timestamp(&philosopher->current_time);
	if (philosopher->current_time - philosopher->last_eat_time
		> philosopher->time_to_die)
	{
		philosopher->stop_prog_philo_die = 1;
		sem_post(philosopher->sem_die_status);
		sem_wait(philosopher->sem_printf);
		printf("%lld %d died\n", philosopher->current_time
			- philosopher->start_of_prog, philosopher->idx + 1);
		exit (1);
	}
	sem_post(philosopher->sem_die_status);
	return ;
}

int	ft_check_philo_eat_limit(t_philosopher *philosopher)
{
	sem_wait(philosopher->sem_eat_limit);
	if (philosopher->eat_limit != -1
		&& philosopher->eat_quant >= philosopher->eat_limit)
	{
		philosopher->stop_prog_eat_quant = 1;
		sem_post(philosopher->sem_eat_limit);
		return (1);
	}
	sem_post(philosopher->sem_eat_limit);
	return (0);
}

void	*ft_thread_for_philo_process(void *argument)
{
	t_philosopher	*philosopher;

	philosopher = argument;
	while (1)
	{
		ft_check_philo_die_status(philosopher);
		if (ft_check_philo_eat_limit(philosopher) == 1)
			return (0);
	}
	return (0);
}
