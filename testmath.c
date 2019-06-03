/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:00:51 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/16 18:09:53 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

int	main(void)
{
	int	a;
	int	b;
	double f;
	double g;
	double h;

	a = 7;
	b = 1;
	f = 0.394395;
	g = 0.918941;
	a = sqrt(pow(a,2) + pow(b, 2));
	h = sqrt(pow(f, 2) + pow(g, 2));
	printf("a:%f\nf:%f\n", (double)a, h);
	return (0);
}
