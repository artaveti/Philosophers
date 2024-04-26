/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_semaphores.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:45:27 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 13:46:45 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo_bonus.h"

void	ft_open_semaphores(t_philosopher *philosopher)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_printf");
	sem_unlink("/sem_die_status");
	sem_unlink("/sem_eat_limit");
	philosopher->sem_forks = sem_open("/sem_forks", O_CREAT, 0644,
			philosopher->forks_quant);
	philosopher->sem_printf = sem_open("/sem_printf", O_CREAT, 0644, 1);
	philosopher->sem_die_status = sem_open("/sem_die_status", O_CREAT, 0644, 1);
	philosopher->sem_eat_limit = sem_open("/sem_eat_limit", O_CREAT, 0644, 1);
	return ;
}

void	ft_close_semaphores(t_philosopher *philosopher)
{
	sem_close(philosopher->sem_forks);
	sem_close(philosopher->sem_printf);
	sem_close(philosopher->sem_die_status);
	sem_close(philosopher->sem_eat_limit);
	return ;
}
