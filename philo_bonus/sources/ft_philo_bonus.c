/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:36:50 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 15:00:48 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo_bonus.h"

void	ft_printf_for_philo_bonus(t_philosopher *philosopher, int idx, int num)
{
	long long		timestamp;
	long long int	start;
	long long int	time;
	int				philo_num;

	sem_wait(philosopher->sem_printf);
	ft_timestamp(&timestamp);
	start = philosopher->start_of_prog;
	time = timestamp - start;
	philo_num = idx + 1;
	if (num == 1)
		printf("%lld %d has taken a fork\n", time, philo_num);
	else if (num == 2)
		printf("%lld %d has taken a fork\n", time, philo_num);
	else if (num == 3)
		printf("%lld %d is eating\n", time, philo_num);
	else if (num == 4)
		printf("%lld %d is sleeping\n", time, philo_num);
	else if (num == 5)
		printf("%lld %d is thinking\n", time, philo_num);
	sem_post(philosopher->sem_printf);
	return ;
}

int	ft_check_process_to_stop(t_philosopher *philosopher,
		int idx, int num, int fork_quant)
{
	sem_wait(philosopher->sem_die_status);
	sem_wait(philosopher->sem_eat_limit);
	if (philosopher->stop_prog_philo_die != 1
		&& philosopher->stop_prog_eat_quant != 1)
	{
		ft_printf_for_philo_bonus(philosopher, idx, num);
		sem_post(philosopher->sem_die_status);
		sem_post(philosopher->sem_eat_limit);
	}
	else if (philosopher->stop_prog_philo_die == 1
		|| philosopher->stop_prog_eat_quant == 1)
	{
		sem_post(philosopher->sem_die_status);
		sem_post(philosopher->sem_eat_limit);
		if (fork_quant == 2)
			sem_post(philosopher->sem_forks);
		sem_post(philosopher->sem_forks);
		return (1);
	}
	return (0);
}

void	ft_check_is_fork_quant_one(t_philosopher *philosopher)
{
	if (philosopher->forks_quant == 1)
	{
		while (1)
		{	
			sem_wait(philosopher->sem_die_status);
			if (philosopher->stop_prog_philo_die == 1)
			{
				sem_post(philosopher->sem_forks);
				sem_post(philosopher->sem_die_status);
				break ;
			}
			sem_post(philosopher->sem_die_status);
		}
	}
	return ;
}

void	ft_assign_eat_bonus(t_philosopher *philosopher)
{
	sem_wait(philosopher->sem_die_status);
	ft_timestamp(&philosopher->last_eat_time);
	sem_post(philosopher->sem_die_status);
	ft_usleep(philosopher->time_to_eat);
	sem_wait(philosopher->sem_eat_limit);
	philosopher->eat_quant++;
	sem_post(philosopher->sem_eat_limit);
	return ;
}

void	ft_philo_bonus(t_philosopher *philosopher, int idx)
{
	if (idx % 2 == 0)
		usleep(2500);
	while (1)
	{
		sem_wait(philosopher->sem_forks);
		if (ft_check_process_to_stop(philosopher, idx, 1, 1) == 1)
			return ;
		ft_check_is_fork_quant_one(philosopher);
		sem_wait(philosopher->sem_forks);
		if (ft_check_process_to_stop(philosopher, idx, 2, 2) == 1)
			return ;
		if (ft_check_process_to_stop(philosopher, idx, 3, 2) == 1)
			return ;
		ft_assign_eat_bonus(philosopher);
		sem_post(philosopher->sem_forks);
		sem_post(philosopher->sem_forks);
		if (ft_check_process_to_stop(philosopher, idx, 4, 0) == 1)
			return ;
		ft_usleep(philosopher->time_to_sleep);
		if (ft_check_process_to_stop(philosopher, idx, 5, 0) == 1)
			return ;
	}
	return ;
}
