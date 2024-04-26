/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_for_philo.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:58:48 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 13:24:17 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_FOR_PHILO_H
# define LIB_FOR_PHILO_H

# include <string.h> // memset();
# include <stdio.h> // printf();
# include <stdlib.h> // malloc(); free();
# include <unistd.h> // write(); usleep();
# include <sys/time.h> // gettimeofday();
# include <pthread.h> // pthread_create(); pthread_detach(); pthread_join();
						// pthread_mutex_init(); pthread_mutex_destroy();
						// pthread_mutex_lock(); pthread_mutex_unlock();
typedef struct s_philosopher
{
	int				num;
	int				*time_to_eat;
	int				*time_to_sleep;
	int				eat_quant;
	int				right_fork;
	int				left_fork;
	long long int	*start_of_prog;
	long long int	last_eat_time;
	int				*stop_prog;
	int				*philos_quant;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*for_printf;
	pthread_mutex_t	*for_die_status;
	pthread_mutex_t	*for_last_eat_time;
	pthread_mutex_t	*for_eat_limit;
	pthread_t		philos_thread;
}	t_philosopher;

typedef struct s_arguments
{
	long long int	start_of_prog;
	int				philos_quant;
	int				forks_quant;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_limit;
	int				*eat_limit_arr;
	int				stop_prog;
	pthread_mutex_t	*forks;
	pthread_mutex_t	for_printf;
	pthread_mutex_t	for_die_status;
	pthread_mutex_t	*for_last_eat_time;
	pthread_mutex_t	*for_eat_limit;
	t_philosopher	*philosophers;
}	t_arguments;

void			ft_timestamp(long long int *timestamp);
size_t			ft_strlen(const	char *s);
unsigned int	ft_atoi_for_philosophers(const char *str);
int				ft_check_arguments(int argc, char *argv[]);
void			ft_assign_arguments(char *argv[], t_arguments *arguments);
void			ft_assign_philosophers_arguments(int i, t_arguments *arguments);
void			ft_mutexes_init(t_arguments *arguments);
void			ft_threads_creat(t_arguments *arguments);
void			*ft_philo(void *argument);
void			ft_threads_checker(t_arguments *arguments);
void			ft_threads_join(t_arguments *arguments);
void			ft_mutexes_destroy(t_arguments *arguments);

#endif
