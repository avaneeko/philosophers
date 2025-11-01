/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:39:11 by losypenk          #+#    #+#             */
/*   Updated: 2025/11/01 13:41:07 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char const **argv)
{
	t_prog			prog;
	int unsigned	i;

	if (!program_init(argc, argv, &prog))
	{
		program_print_error(&prog);
		return (1);
	}
	start_simulation(&prog);
	i = ~0;
	while (++i < prog.n_philo)
		pthread_mutex_destroy(prog.forks + i);
	pthread_mutex_destroy(&prog.print_acq);
	null_free((void *[]){
		(void *)&prog.th,
		(void *)&prog.philos,
		(void *)&prog.forks,
		NULL
	});
	return (0);
}
