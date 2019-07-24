/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check_inter_sphere.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:03:41 by pmasson           #+#    #+#             */
/*   Updated: 2019/07/11 13:02:49 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

double	rtv1_check_inter_sphere(t_obj *obj, t_ray *ray, int s)
{
	double	a;
	double	b;
	double	c;
	double	det;
	double	t;

	if ((a = ray->vec[0 + s] * ray->vec[0 + s] + ray->vec[1 + s] * ray->vec[1 + s]
				+ ray->vec[2 + s] * ray->vec[2 + s]) == 0)
		return (ft_msg_int(2, "Error calculating a in sphere.\n", -1));
	b = 2 * (ray->vec[0 + s] * (ray->source[0 + s] - (double)obj->data[0])
			+ ray->vec[1 + s] * (ray->source[1 + s] - (double)obj->data[1])
			+ ray->vec[2 + s] * (ray->source[2 + s] - (double)obj->data[2]));
	c = pow(ray->source[0 + s] - obj->data[0] , 2)
		+ pow(ray->source[1 + s] - obj->data[1] , 2)
		+ pow(ray->source[2 + s] - obj->data[2] , 2) - pow(obj->data[3], 2);
	det = b * b - 4 * a * c;
	if (det < 0)
		return (-1);
	else
		t = rtv1_solve_2_deg(det, a, b);
	return (t);
}
