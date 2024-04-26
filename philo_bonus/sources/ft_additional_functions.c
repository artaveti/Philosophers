/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:28:02 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 14:45:45 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo_bonus.h"

void	ft_timestamp(long long int *timestamp)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	*timestamp = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return ;
}

size_t	ft_strlen(const	char *s)
{
	size_t	i;

	i = 0;
	if (!s[0])
		return (0);
	while (s[i])
		i++;
	return (i);
}

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

void	ft_open_forks(t_arguments *arguments, t_philosopher *philosopher)
{
	pid_t	process_num;
	int		i;

	i = 0;
	while (i < arguments->philos_quant)
	{
		process_num = fork();
		if (process_num == 0)
		{
			philosopher->idx = i;
			pthread_create(&philosopher->thread_for_check, NULL,
				&ft_thread_for_philo_process, philosopher);
			ft_philo_bonus(philosopher, i);
			pthread_join(philosopher->thread_for_check, NULL);
			exit(2);
		}
		arguments->process_ids[i] = process_num;
		i++;
	}
	return ;
}

void	ft_kill_forks(t_arguments *arguments)
{
	int	status;
	int	exit_status;
	int	i;

	while (wait(&status) != -1)
	{
		WIFEXITED(status);
		exit_status = WEXITSTATUS(status);
		if (exit_status == 1)
		{
			i = 0;
			while (i < arguments->philos_quant)
			{
				status = kill(arguments->process_ids[i], SIGKILL);
				i++;
			}
		}
	}
	return ;
}
