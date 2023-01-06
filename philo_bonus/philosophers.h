/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:54:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 23:02:16 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

# define TOO_FEW_ARG "Error : too few args : philo must be launch with \
the following args (last arg is optionnal):\n\t\
[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] \
[number_of_times_each_philosopher_must_eat]\n"

# define TOO_MANY_ARGS "Error : too many args : philo must be launch with \
the following args (last arg is optionnal):\n\t\
[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] \
[number_of_times_each_philosopher_must_eat]\n"

# define NO_VALID_ARGS "Error : args must be positives int values\n"

# define ERR_NB_PHILO "There must be at least one philo and no more than 200\n"

# define ERR_ARG_VALUE "Death, eat or time values must be over 60 ms\n"

# define ERR_MALLOC "Error with malloc function\n"
# define ERR_THREADS "Error while creating threads\n"
# define ERR_JOIN "Error while joining threads\n"
# define ERR_DESTR "Error while destroying mutex\n"
# define ERR_INIT_SEM "Error while intializing sempahore\n"
# define ERR_FORK "Error while forking child process\n"
# define ERR_DETACH "Error while detaching thread\n"
# define ERR_SEM_CLOSE "Error while closing semaphores\n"
# define ERR_SEM_UNLINK "Error while unlinking semaphores\n"

# define CHAR_INT_MAX "2147483647"
# define BASE_DEC "0123456789"

typedef struct s_philo_id
{
	int				nb_philo;
	int				id;
	pid_t			pid;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_meal_max;
	int				nb_meal_taken;
	struct timeval	last_meal;
	struct timeval	time0_sim;
	struct s_philo	*p_for_all;
}t_philo_id;

typedef struct s_philo
{
	int				nb_philo;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_meal_max;
	int				nb_meal_taken;
	t_philo_id		*tab_philo;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*death;
	sem_t			*meal;
	int				fork_status;
	int				print_status;
	int				death_status;
	int				meal_status;

}t_philo;

/*	------------ EXIT FUNCTIONS -------------  */

void	fail_exit(char *msg, char **tab_arg);
void	fail_exit2(char *msg, t_philo *philo);
void	destroy_and_exit_parent(t_philo *philo);

/*	------------ CHECKING FUNCTIONS -------------  */

int		ft_is_valid_format(char *str, char *comparing_base);
int		ft_strcmp(const char *s1, const char *s2);
int		central_checking(char **tab_nb);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nb, size_t size);
size_t	ft_strlen(const char *str);

/*	------------ SIMULATION FUNCTIONS -------------  */

void	init_struct_philo(t_philo *philo, char **tab_info);
void	activate_simulation(t_philo *philo);
void	living(t_philo_id *philo);
void	*check_is_dead(void *arg);
int		activity_time(int time_activity, int id);
int		eating(t_philo_id *philo);
int		get_time(struct timeval time1, struct timeval time2);

#endif
