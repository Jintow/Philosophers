/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:54:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/03 11:20:31 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "libft.h"
# include "ft_printf.h"
# include <pthread.h>
# include <sys/time.h>


# define TOO_FEW_ARG "Error : too few args : philo must be launch with \
the following args (last arg is optionnal):\n\t\
[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] \
[number_of_times_each_philosopher_must_eat]\n"

# define TOO_MANY_ARGS "Error : too many args : philo must be launch with \
the following args (last arg is optionnal):\n\t\
[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] \
[number_of_times_each_philosopher_must_eat]\n"

# define NO_VALID_ARGS "Error : args must be positives int values\n"
# define ERR_MALLOC "Error with malloc function\n"
# define ERR_INIT_MUTEX "Error while intializing mutexes\n"
# define ERR_THREADS "Error while creating threads\n"
# define ERR_LOCK "Error while locking a mutex\n"

typedef struct s_philo_id
{
	int				nb_philo;
	int				id;
	double			time_death;
	double			time_eat;
	double			time_sleep;
	int				nb_meal_max;
	int				nb_meal_taken;
	struct timeval	last_meal;
	struct timeval	time0_sim;
	pthread_mutex_t	fork1;
	pthread_mutex_t	fork2;
	struct s_philo	*p_for_all;
}t_philo_id;

typedef struct s_philo
{
	int				nb_philo;
	double			time_death;
	double			time_eat;
	double			time_sleep;
	int				nb_meal;
	t_philo_id		*tab_philo;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
}t_philo;

void	fail_exit(char *msg, char **tab_arg);
void	fail_exit2(char *msg, t_philo *philo);
void	init_struct_philo(t_philo *philo, char **tab_info);
char	**init_args(char **argv);
int		central_checking(char **tab_nb);

#endif
