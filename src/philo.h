/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:39:22 by losypenk          #+#    #+#             */
/*   Updated: 2025/10/22 12:28:54 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

typedef struct s_prog
{
	unsigned	n_philo;	// Number of philosophers
	unsigned	t_die;		// Time to die
	unsigned	t_eat;		// Time to eat
	unsigned	t_sleep;	// Time to sleep
	unsigned	n_to_eat;	// Number of times each must eat.
	int			err;		// Last error. 0 if no error.
}	t_prog;

//
//	Program initialize.
//	Parses the arguments and initializes all the data needed for the simulation.
//
int		program_init(int argc, char const **argv, t_prog *out);

//
//	Print the last error.
//
void	program_print_error(t_prog const *p);

////////////////////////////////////////////////////////////////////////////////
// Utils																	  //
////////////////////////////////////////////////////////////////////////////////

// String length
size_t	slen(char const *s);

// Print a string to STDOUT.
int	print(char const *s);

// Print a string to STDERR.
int	print_err(char const *s);
