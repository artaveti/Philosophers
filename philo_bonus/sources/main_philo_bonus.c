/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:47:10 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 16:17:18 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_arguments		arguments;
	t_philosopher	philosopher;

	ft_timestamp(&arguments.start_of_prog);
	if (ft_check_arguments(argc, argv) != 0)
		exit(EXIT_SUCCESS);
	ft_assign_arguments(argv, &arguments);
	ft_assign_philosopher_arguments(argv, &philosopher, &arguments);
	ft_open_semaphores(&philosopher);
	ft_open_forks(&arguments, &philosopher);
	ft_kill_forks(&arguments);
	ft_close_semaphores(&philosopher);
	exit (EXIT_SUCCESS);
}
	//system("leaks philo");