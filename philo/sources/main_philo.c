/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:39:17 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 16:02:02 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo.h"

int	main(int argc, char *argv[])
{
	t_arguments	arguments;
	int			i;

	ft_timestamp(&arguments.start_of_prog);
	if (ft_check_arguments(argc, argv) != 0)
		return (1);
	ft_assign_arguments(argv, &arguments);
	i = 0;
	while (i < arguments.philos_quant)
	{
		ft_assign_philosophers_arguments(i, &arguments);
		i++;
	}
	ft_mutexes_init(&arguments);
	ft_threads_creat(&arguments);
	ft_threads_checker(&arguments);
	ft_threads_join(&arguments);
	ft_mutexes_destroy(&arguments);
	return (0);
}
//system("leaks philo");