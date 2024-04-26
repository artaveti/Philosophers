/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_for_philo_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:06:30 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 15:01:38 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_FOR_PHILO_BONUS_H
# define LIB_FOR_PHILO_BONUS_H

# include <string.h> // memset();
# include <stdio.h> // printf();
# include <stdlib.h> // malloc(); free();
# include <unistd.h> // write(); usleep();
# include <sys/time.h> // gettimeofday();
# include <pthread.h> // pthread_create(); pthread_detach(); pthread_join(); p
						//thread_mutex_init(); pthread_mutex_destroy();
						// pthread_mutex_lock(); pthread_mutex_unlock();
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philosopher
{
	int				idx;
	int				forks_quant;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_limit;
	int				eat_quant;
	long long int	start_of_prog;
	long long int	last_eat_time;
	long long int	current_time;
	int				stop_prog_eat_quant;
	int				stop_prog_philo_die;
	sem_t			*sem_forks;
	sem_t			*sem_printf;
	sem_t			*sem_die_status;
	sem_t			*sem_eat_limit;
	pthread_t		thread_for_check;
}	t_philosopher;

typedef struct s_arguments
{
	long long int	start_of_prog;
	int				philos_quant;
	int				forks_quant;
	pid_t			*process_ids;
}	t_arguments;

void			ft_timestamp(long long int *timestamp);
size_t			ft_strlen(const	char *s);
void			ft_usleep(int milliseconds);
unsigned int	ft_atoi_for_philosophers(const char *str);
int				ft_check_arguments(int argc, char *argv[]);
void			ft_assign_arguments(char *argv[], t_arguments *arguments);
void			ft_assign_philosopher_arguments(char *argv[],
					t_philosopher *philosopher, t_arguments *arguments);
void			ft_open_semaphores(t_philosopher *philosopher);
void			*ft_thread_for_philo_process(void *argument);
void			ft_philo_bonus(t_philosopher *philosopher, int idx);
void			ft_open_forks(t_arguments *arguments,
					t_philosopher *philosopher);
void			ft_kill_forks(t_arguments *arguments);
void			ft_close_semaphores(t_philosopher *philosopher);

#endif
