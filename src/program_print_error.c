/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_print_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:32:36 by losypenk          #+#    #+#             */
/*   Updated: 2025/11/01 13:32:37 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Converts error code to a string.
static	char const	*code2err(int err)
{
	if (err == 0)
		return ("No error.\n");
	else if (err == ENOMEM)
		return ("Out of memory.\n");
	else if (err == EINVAL)
		return ("Invalid argument.\n");
	else if (err == EBUSY || err == EAGAIN)
		return ("Resource temporarily unavailable.\n");
	return (NULL);
}

void	program_print_error(t_prog const *p)
{
	char const *const	str = code2err(p->err);

	if (str)
		(void)(print_err("Error: ") && print_err(str));
	else
		print_err("Unknown error has occurred.\n");
}
