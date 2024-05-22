/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccadoret <ccadoret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:19:42 by ccadoret          #+#    #+#             */
/*   Updated: 2024/04/09 13:19:42 by ccadoret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define MSG "number_of_philosophers time_to_die time_to_eat time_to_sleep"
# define MSG2 "+ [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*alive_mtx;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long			last_meal;
	long			start;
	int				*philosopher_alive;
}			t_philosopher;

typedef struct s_data
{
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	alive_mtx;
	int				nb_philos;
	int				common;
}			t_data;

int		ft_atoi(const char *str);
void	eat(t_philosopher *philosopher);
void	think(t_philosopher *philosopher);
void	sleep_p(t_philosopher *philo);
void	die(t_philosopher *philosopher, int h);
long	get_current_time(void);
int		should_stop(t_philosopher *philosopher);
void	print_message(t_philosopher *philosopher, char *msg, int n);
void	ft_usleep(long time, t_philosopher *philo, int n);
int		control(char **tab_str);
void	unlock_and_stop(t_philosopher *philosopher, int nb);
int		should_stop_2(t_philosopher *philo);
int		for_par(int n);
int		ac_is_six(int ac, char **av);

#endif