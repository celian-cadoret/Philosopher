/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccadoret <ccadoret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:24:42 by ccadoret          #+#    #+#             */
/*   Updated: 2024/04/10 13:24:42 by ccadoret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_message(t_philosopher *philo, char *msg, int n)
{
	if (n == 1 || !should_stop_2(philo))
	{
		pthread_mutex_lock(philo->print_mutex);
		printf("time: %ld philosopher %d %s",
			get_current_time() - philo->start, philo->id + 1, msg);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

void	ft_usleep(long time, t_philosopher *philo, int n)
{
	long	beginning;

	beginning = get_current_time();
	if (philo->id == -1 || n == -1)
		return ;
	while (get_current_time() < (beginning + time))
	{
		if (philo->nb_philos > 1)
			unlock_and_stop(philo, n);
		if (!should_stop(philo))
			if ((get_current_time() - philo->last_meal) >= philo->time_to_die)
				die(philo, 0);
		if (!should_stop(philo))
			usleep(10);
	}
}

void	wait_time(int time, t_philosopher *philo)
{
	if ((get_current_time() + time - philo->last_meal) > philo->time_to_die)
	{
		usleep(philo->time_to_die - (get_current_time() - philo->last_meal));
		die(philo, 0);
	}
	else
		usleep(time);
}

void	unlock_and_stop(t_philosopher *p, int nb)
{
	if (should_stop_2(p))
	{
		if (nb == 0)
			pthread_exit(NULL);
		if (nb == 1)
			pthread_mutex_unlock(&p->forks[p->id]);
		if (nb == 2)
		{
			pthread_mutex_unlock(&p->forks[p->id]);
			pthread_mutex_unlock(&p->forks[(p->id + 1) % p->nb_philos]);
		}
		if (nb == 3)
			pthread_mutex_unlock(&p->forks[(p->id + 1) % p->nb_philos]);
		if (nb == 4)
		{
			pthread_mutex_unlock(&p->forks[(p->id + 1) % p->nb_philos]);
			pthread_mutex_unlock(&p->forks[p->id]);
		}
		if (should_stop(p))
			pthread_exit(NULL);
	}
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
