/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_for_args_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:37:22 by artaveti          #+#    #+#             */
/*   Updated: 2023/09/13 12:44:28 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_check_are_all_chars_digits(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != '\0')
	{
		if (argv[i][0] == '\0')
		{
			printf("Error: Argument contains only null character\n");
			return (2);
		}
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				printf("Error: Characters of argument are not only digits\n");
				return (3);
			}
			j++;
		}
		i++;
	}
	return (0);
}

unsigned int	ft_atoi_for_philosophers(const char	*str)
{
	unsigned int	num;

	num = 0;
	while (*str != '\0')
	{
		num = num * 10 + *str - 48;
		str++;
	}
	return (num);
}

int	ft_check_is_arg_int(char *argv[])
{
	int				i;
	int				j;
	unsigned int	num;

	i = 1;
	while (argv[i] != '\0')
	{
		j = 0;
		while (argv[i][j] == '0')
			j++;
		if (ft_strlen(&argv[i][j]) > 10)
		{
			printf("Error: Digit of argument is more than int\n");
			return (4);
		}
		num = ft_atoi_for_philosophers(argv[i]);
		if (num > 2147483647)
		{
			printf("Error: Digit of argument is more than int\n");
			return (5);
		}
		i++;
	}
	return (0);
}

int	ft_check_arguments(int argc, char *argv[])
{
	int	char_error;
	int	int_error;
	int	zero_error;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong arguments quantity\n");
		return (1);
	}
	char_error = ft_check_are_all_chars_digits(argv);
	if (char_error > 0)
		return (char_error);
	int_error = ft_check_is_arg_int(argv);
	if (int_error > 0)
		return (int_error);
	zero_error = ft_atoi_for_philosophers(argv[1]);
	if (zero_error == 0)
	{
		printf("Error: Digit of second argument must be more than 0\n");
		return (6);
	}
	return (0);
}
