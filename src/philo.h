/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:39:22 by losypenk          #+#    #+#             */
/*   Updated: 2025/08/09 17:26:25 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

typedef struct s_prog
{
	unsigned n_philo;	// Number of philosophers
	unsigned t_die;		// Time to die
	unsigned t_eat;		// Time to eat
	unsigned t_sleep;	// Time to sleep
	unsigned n_to_eat;	// Number of times each must eat.
}	t_prog;

//
//	Program initialize.
//	Parses the arguments and initializes all the data needed for the simulation.
//
int	program_init(int argc, char const **argv, t_prog *out);
