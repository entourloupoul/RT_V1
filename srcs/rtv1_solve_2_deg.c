/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_solve_2_deg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 13:01:13 by pmasson           #+#    #+#             */
/*   Updated: 2019/08/14 19:32:23 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double   rtv1_solve_2_deg(double det, double a, double b)
{
	double  t1;
	double  t2;

	if (a == 0)
		return (-1);
	if (det == 0)
		return (-b / (2 * a));
	else
	{
		t1 = (-b + sqrt(det)) / (2 * a);
		t2 = (-b - sqrt(det)) / (2 * a);
	}
	if (t1 >= 0 && (t1 <= t2 || t2 < 0))
		return (t1);
	if (t2 >= 0 && (t2 <= t1 || t1 < 0))
		return (t2);
	return (-1);
}
