/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccadoret <ccadoret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:19:37 by ccadoret          #+#    #+#             */
/*   Updated: 2024/04/09 13:19:37 by ccadoret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	eat_2(t_philosopher *philo)
{
	if (!should_stop(philo) && philo->nb_philos > 1)
	{
		pthread_mutex_lock(&philo->forks[(philo->id + 1) % philo->nb_philos]);
		print_message(philo, "has taken a fork 🍴\n", 0);
		unlock_and_stop(philo, 3);
		pthread_mutex_lock(&philo->forks[philo->id]);
		print_message(philo, "has taken a fork 🍴\n", 0);
		unlock_and_stop(philo, 4);
		print_message(philo, "is eating   🍽️\n", 0);
		philo->last_meal = get_current_time();
		ft_usleep(philo->time_to_eat, philo, 4);
		pthread_mutex_unlock(&philo->forks[(philo->id + 1) % philo->nb_philos]);
		pthread_mutex_unlock(&philo->forks[philo->id]);
		if (philo->number_of_times_each_philosopher_must_eat)
			philo->number_of_times_each_philosopher_must_eat--;
	}
}

void	eat(t_philosopher *phl)
{
	if (!should_stop(phl) && phl->nb_philos > 1)
	{
		if (phl->id % 2 == 1)
			eat_2(phl);
		else
		{
			pthread_mutex_lock(&phl->forks[phl->id]);
			unlock_and_stop(phl, 1);
			print_message(phl, "has taken a fork 🍴\n", 0);
			unlock_and_stop(phl, 1);
			pthread_mutex_lock(&phl->forks[(phl->id + 1) % phl->nb_philos]);
			unlock_and_stop(phl, 2);
			print_message(phl, "has taken a fork 🍴\n", 0);
			unlock_and_stop(phl, 2);
			print_message(phl, "is eating   🍽️\n", 0);
			phl->last_meal = get_current_time();
			ft_usleep(phl->time_to_eat, phl, 2);
			pthread_mutex_unlock(&phl->forks[phl->id]);
			pthread_mutex_unlock(&phl->forks[(phl->id + 1) % phl->nb_philos]);
			if (phl->number_of_times_each_philosopher_must_eat)
				phl->number_of_times_each_philosopher_must_eat--;
		}
	}
}

void	think(t_philosopher *philosopher)
{
	print_message(philosopher, "is thinking 🤔\n", 0);
}

void	sleep_p(t_philosopher *philo)
{
	if (!should_stop(philo))
	{
		print_message(philo, "is sleeping 😴\n", 0);
		ft_usleep(philo->time_to_sleep, philo, 0);
	}
	if (should_stop(philo))
		pthread_exit(NULL);
}

void	die(t_philosopher *philosopher, int h)
{
	if (h == 0)
	{
		if (!should_stop_2(philosopher))
		{
			pthread_mutex_lock(philosopher->alive_mtx);
			*philosopher->philosopher_alive = 1;
			usleep(10);
			print_message(philosopher, "died in suffering 💀\n", 1);
			pthread_mutex_unlock(philosopher->alive_mtx);
		}
	}
	else
	{
		pthread_mutex_lock(philosopher->alive_mtx);
		*philosopher->philosopher_alive = 1;
		usleep(10);
		print_message(philosopher, "died in suffering 💀\n", 1);
		pthread_mutex_unlock(philosopher->alive_mtx);
	}
	pthread_exit(NULL);
}
