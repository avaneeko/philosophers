/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:39:11 by losypenk          #+#    #+#             */
/*   Updated: 2025/10/22 11:53:16 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long START;
int	main(int argc, char const **argv)
{
	START = now_ms();
	t_prog	prog;
	if(!program_init(argc, argv, &prog))
	{
		program_print_error(&prog);
		return (1);
	}
	__builtin_dump_struct(&prog, &printf);
	start_simulation(&prog);;

	return (0);
}
