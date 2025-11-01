/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:39:22 by losypenk          #+#    #+#             */
/*   Updated: 2025/11/01 13:40:36 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_critical;
typedef pthread_t		t_thread;
typedef struct s_philo	t_philo;
typedef unsigned long	t_time;

typedef struct s_prog
{
	unsigned	n_philo;	// Number of philosophers
	unsigned	t_die;		// Time to die
	unsigned	t_eat;		// Time to eat
	unsigned	t_sleep;	// Time to sleep
	unsigned	n_to_eat;	// Number of times each must eat.
	t_time		start_time;	// Simulation start time.
	int			err;		// Last error. 0 if no error.
	t_philo		*philos;	// Philosopher data array.
	t_thread	*th;		// Philosopher thread array.
	t_critical	*forks;		// Critical section array.
	int			s_barrier;	// Simulation start barrier. 0 means closed.
	int			sim_stop;	// Simulation stop. 1 means stop.
	t_critical	print_acq;	// Critical to avoid mixed prints.
}	t_prog;

struct s_philo
{
	unsigned				id;			// Philosopher ID
	_Atomic unsigned		n_eaten;	// Number of times eaten
	_Atomic t_time			last_meal;	// Timestamp of last meal
	t_prog					*prog;		// Ptr to program data
	t_critical				*l_fork;	// Ptr to left fork
	t_critical				*r_fork;	// Ptr to right fork
};

//
//	Program initialize.
//	Parses the arguments and initializes all the data needed for the simulation.
//
int		program_init(int argc, char const **argv, t_prog *out);

//
//	Print the last error.
//
void	program_print_error(t_prog const *p);

// Thread entry point.
void	*proc(void *arg);

// Thread entry point for single case.
void	*proc_single(void *arg);

// Starts the simulation.
void	start_simulation(t_prog *p);

int		sleep_aware(int unsigned dur_us, int const volatile *sim_end);

////////////////////////////////////////////////////////////////////////////////
//	Logging function.														  //
////////////////////////////////////////////////////////////////////////////////

# define MSG_TAKEN_FORK "has taken a fork\n"
# define MSG_EATING "is eating\n"
# define MSG_SLEEPING "is sleeping\n"
# define MSG_THINKING "is thinking\n"
# define MSG_DIED "died\n"

// 10 for all possible id numbers.
// 20 for all possible timestamps.
// 2 for spaces.
// 17 for longest msg.
# define LOG_BUF_SIZE 49

// too bad I can't name this log()
void	log_state(t_philo *p, char const *msg);
void	log_state_no_critical(t_philo *p, char const *msg);

// Current timestamp in ms.
t_time	now_ms(unsigned long start_time);

////////////////////////////////////////////////////////////////////////////////
// Utils																	  //
////////////////////////////////////////////////////////////////////////////////

// String length
size_t	slen(char const *s);

// Print a string to STDOUT.
int		print(char const *s);

// Print a string to STDERR.
int		print_err(char const *s);

// Frees and nulls ptr from the null-terminated ptr array.
void	null_free(void *p[]);

void	mreverse(void *p, size_t size);

void	mcpy(void *dst, void const *src, size_t size);

#endif
