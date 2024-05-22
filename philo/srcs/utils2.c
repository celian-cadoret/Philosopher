/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccadoret <ccadoret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:21:54 by ccadoret          #+#    #+#             */
/*   Updated: 2024/04/24 10:21:54 by ccadoret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	should_stop_2(t_philosopher *philo)
{
	int	stop;

	pthread_mutex_lock(philo->alive_mtx);
	stop = *(philo->philosopher_alive);
	if (philo->number_of_times_each_philosopher_must_eat == 0)
		stop = 1;
	pthread_mutex_unlock(philo->alive_mtx);
	if (!stop)
	{
		if ((get_current_time() - philo->last_meal) >= philo->time_to_die)
		{
			stop = 2;
		}
	}
	return (stop);
}

int	for_par(int n)
{
	if (n == 1)
		return (0);
	return ((n % 2) * 10);
}

int	ac_is_six(int ac, char **av)
{
	if (ac == 6)
		return (ft_atoi(av[5]));
	return (-1);
}
