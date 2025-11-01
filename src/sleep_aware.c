/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_aware.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:29:00 by losypenk          #+#    #+#             */
/*   Updated: 2025/11/01 13:30:48 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//$ This file defines a sleep_aware function, that induces microsleeps
// to still yield the thread, but wake up in small periods of time to check
// whether the simulation has stopped to stop it's own thread.

// Sleep, perdiodically waking up to check whether the simulation has to end.
// Returns non-zero if the simulation has to end, zero otherwise.

static unsigned long	now_us(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((unsigned long)tv.tv_sec * 1000000ul + (unsigned long)tv.tv_usec);
}

int	sleep_aware(int unsigned dur_us, int const volatile *sim_end)
{
	unsigned long const	end = now_us() + dur_us;
	unsigned long		now;
	unsigned long		rem;

	while (!*sim_end)
	{
		now = now_us();
		if (now >= end)
			break ;
		rem = end - now;
		if (rem > 20000ul)
			usleep(rem / 4);
		else if (rem > 2000ul)
			usleep(1000);
		else
			usleep(200);
	}
	return (*sim_end);
}
