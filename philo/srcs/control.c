/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccadoret <ccadoret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:59:39 by ccadoret          #+#    #+#             */
/*   Updated: 2024/04/19 11:59:39 by ccadoret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	verif_max(char *str)
{
	int		i;
	int		len;
	char	*max;

	i = 0;
	max = "2147483647";
	len = ft_strlen(str);
	if (len > 10)
		return (0);
	else
	{
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (0);
			if (len == 10)
				if (str[i] > max[i] || max[i] == '\0')
					return (0);
			i++;
		}
	}
	return (1);
}

int	control(char **tab_str)
{
	int	i;

	i = 0;
	while (tab_str[i])
	{
		if (!verif_max(tab_str[i]))
			return (0);
		i++;
	}
	return (1);
}
