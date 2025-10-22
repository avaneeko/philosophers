/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:44:14 by losypenk          #+#    #+#             */
/*   Updated: 2025/10/22 13:08:22 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

//
//	Decimal string to unsigned.
//*	Returns 1 on successful conversion and 0 on overflow or conversion failure.
//
int	stou(char const *s, unsigned *out)
{
	unsigned	n;
	int			overflow;
	int			saw_digit;
	unsigned	dec;

	n = 0;
	overflow = 0;
	saw_digit = 0;
	if (*s == '+')
		s++;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		saw_digit = 1;
		dec = *s - '0';
		overflow |= n > UINT_MAX / 10;
		n *= 10;
		overflow |= n > UINT_MAX - dec;
		n += dec;
		s++;
	}
	if (!overflow && saw_digit)
		*out = n;
	return (!overflow && saw_digit);
}

static int	parse_arguments(int argc, char const **argv, t_prog *out)
{
	int	failure;

	if (argc != 5 && argc != 6)
		return (0);
	failure = 0;
	failure |= !stou(argv[1], &out->n_philo);
	failure |= !stou(argv[2], &out->t_die);
	failure |= !stou(argv[3], &out->t_eat);
	failure |= !stou(argv[4], &out->t_sleep);
	if (argc == 6)
		failure |= !stou(argv[5], &out->n_to_eat);
	else
		out->n_to_eat = ~0;
	return (failure == 0 && out->n_philo && out->t_die && out->t_eat
			&& out->t_sleep && out->n_to_eat);
}

int	program_init(int argc, char const **argv, t_prog *out)
{
	*out = (t_prog){0};
	if (!parse_arguments(argc, argv, out))
		return (0);
	return (1);
}
