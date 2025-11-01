/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:33:01 by losypenk          #+#    #+#             */
/*   Updated: 2025/11/01 13:33:07 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mreverse(void *p, size_t size)
{
	size_t			i;
	unsigned char	t;

	i = ~0;
	while (++i < size / 2)
	{
		t = ((unsigned char *)p)[i];
		((unsigned char *)p)[i] = ((unsigned char *)p)[size - i - 1];
		((unsigned char *)p)[size - i - 1] = t;
	}
}

void	mcpy(void *dst, void const *src, size_t size)
{
	unsigned char		*d;
	unsigned char const	*s;
	size_t				i;

	d = dst;
	s = src;
	i = ~0;
	while (++i < size)
		d[i] = s[i];
}
