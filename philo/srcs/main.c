/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccadoret <ccadoret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:19:31 by ccadoret          #+#    #+#             */
/*   Updated: 2024/04/09 13:19:31 by ccadoret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	should_stop(t_philosopher *philo)
{
	int	stop;

	pthread_mutex_lock(philo->alive_mtx);
	stop = *(philo->philosopher_alive);
	if (philo->number_of_times_each_philosopher_must_eat == 0)
		stop = 1;
	pthread_mutex_unlock(philo->alive_mtx);
	if (!stop || philo->nb_philos == 1)
	{
		if ((get_current_time() - philo->last_meal) >= philo->time_to_die)
		{
			die(philo, 1);
			stop = 1;
		}
	}
	return (stop);
}

void	*life_round(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	philo->last_meal = philo->start;
	if (philo->id % 2 == 0 || philo->id == philo->nb_philos - 1)
		usleep(10);
	while (1)
	{
		if (!should_stop(philo) || philo->nb_philos == 1)
			if ((get_current_time() - philo->last_meal) >= philo->time_to_die)
				die(philo, 0);
		if (should_stop(philo))
			pthread_exit(NULL);
		if (!should_stop(philo))
			think(philo);
		if (!should_stop(philo))
			eat(philo);
		if (!should_stop(philo))
			sleep_p(philo);
	}
	return (NULL);
}

pthread_mutex_t	*init_mtx(pthread_mutex_t *pmtx, pthread_mutex_t *amtx, int nb)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * (nb + 1));
	i = -1;
	while (++i < nb)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(pmtx, NULL);
	pthread_mutex_init(amtx, NULL);
	return (forks);
}

t_philosopher	*init_table(int ac, char **av, t_data *o, int *common)
{
	t_philosopher	*table;
	int				i;

	table = malloc(sizeof(t_philosopher) * (o->nb_philos + 1));
	if (table == NULL)
		return (NULL);
	i = -1;
	while (++i < o->nb_philos)
	{
		table[i].id = i;
		table[i].forks = o->forks;
		table[i].nb_philos = o->nb_philos;
		table[i].time_to_die = ft_atoi(av[2]) + for_par(o->nb_philos);
		table[i].time_to_eat = ft_atoi(av[3]);
		table[i].time_to_sleep = ft_atoi(av[4]);
		table[i].start = get_current_time();
		table[i].philosopher_alive = common;
		table[i].print_mutex = &o->print_mtx;
		table[i].alive_mtx = &o->alive_mtx;
		table[i].number_of_times_each_philosopher_must_eat = ac_is_six(ac, av);
		pthread_create(&table[i].thread, NULL, life_round, &table[i]);
	}
	return (table);
}

int	main(int argc, char **argv)
{
	t_philosopher	*table;
	t_data			o;
	int				common;
	int				i;

	if (argc < 5 || argc > 6 || !control(argv + 1) || ft_atoi(argv[2]) < 60)
		return (printf(MSG), printf(MSG2), 1);
	common = 0;
	o.nb_philos = ft_atoi(argv[1]);
	o.forks = init_mtx(&o.print_mtx, &o.alive_mtx, o.nb_philos);
	table = init_table(argc, argv, &o, &common);
	i = -1;
	while (++i < o.nb_philos)
		pthread_join(table[i].thread, NULL);
	i = -1;
	while (++i < o.nb_philos)
		pthread_mutex_destroy(&o.forks[i]);
	pthread_mutex_destroy(&o.print_mtx);
	pthread_mutex_destroy(&o.alive_mtx);
	free(table);
	free(o.forks);
	return (0);
}
