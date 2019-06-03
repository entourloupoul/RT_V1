/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check_inter_sphere.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:03:41 by pmasson           #+#    #+#             */
/*   Updated: 2019/06/03 09:41:37 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <stdio.h>
static double	rtv1_inter_sphere_get_t(double det, double a, double b)
{
	double	t1;
	double	t2;

	if (det == 0)
		return (-b / (2 * a));
	else
	{
		t1 = (-b + sqrt(det)) / (2 * a);
		t2 = (-b - sqrt(det)) / (2 * a);
	}
	if (t1 >= 0 && t1 <= t2)
		return (t1);
	if (t2 >= 0 && t2 <= t1)
		return (t2);
	return (-1);
}

double	rtv1_check_inter_sphere(t_obj *obj, t_ray *ray)
{
	double	a;
	double	b;
	double	c;
	double	det;
	double	t;

	if ((a = ray->vec[0] * ray->vec[0] + ray->vec[1] * ray->vec[1]
				+ ray->vec[2] * ray->vec[2]) == 0)
		return (ft_msg_int(2, "Error calculating a in sphere.\n", -1));
	b = 2 * (ray->vec[0] * (ray->source[0] - (double)obj->data[0])
			+ ray->vec[1] * (ray->source[1] - (double)obj->data[1])
			+ ray->vec[2] * (ray->source[2] - (double)obj->data[2]));
	c = pow(ray->source[0] - obj->data[0] , 2)
		+ pow(ray->source[1] - obj->data[1] , 2)
		+ pow(ray->source[2] - obj->data[2] , 2) - pow(obj->data[3], 2);
	det = b * b - 4 * a * c;
	//printf("det:%f\n", det);
	if (det < 0)
		return (-1);
	else
		t = rtv1_inter_sphere_get_t(det, a, b);
	return (t);
}
