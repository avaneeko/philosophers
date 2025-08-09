/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:39:11 by losypenk          #+#    #+#             */
/*   Updated: 2025/08/09 17:28:54 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char const **argv)
{
	t_prog	prog;
	if(program_init(argc, argv, &prog))
		return (__builtin_dump_struct(&prog, &printf), 0);
	else
		return (write(2, "Invalid command line arguments.\n", 32), 1);

	return (0);
}
