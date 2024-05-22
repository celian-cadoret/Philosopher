/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccadoret <ccadoret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:07:54 by ccadoret          #+#    #+#             */
/*   Updated: 2024/02/29 11:03:32 by ccadoret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	char_to_int(char c)
{
	if (c >= '0' && c <= '9')
	{
		return (c - '0');
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -sign;
		}
		i++;
	}
	while ((str[i] <= '9') && (str[i] >= '0'))
	{
		result = (result * 10) + char_to_int(str[i]);
		i++;
	}
	return (result * sign);
}
/*
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	ft_atoi(argv[0])
	
}*/
