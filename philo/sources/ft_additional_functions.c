/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:49:20 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 12:49:22 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo.h"

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

void	ft_timestamp(long long int *timestamp)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	*timestamp = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return ;
}
