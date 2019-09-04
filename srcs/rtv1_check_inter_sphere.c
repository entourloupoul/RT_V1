/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check_inter_sphere.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:03:41 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 15:55:04 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

double	rtv1_check_inter_sphere(t_obj *obj, t_geo source)
{
	double	a;
	double	b;
	double	c;
	double	det;
	double	t;

	if ((a = source.dir.x * source.dir.x + source.dir.y * source.dir.y
				+ source.dir.z * source.dir.z) == 0)
		return (ft_msg_int(2, "Error calculating a in sphere.\n", -1));
	b = 2 * (source.dir.x * (source.pos.x - obj->u.sphere.center.x)
			+ source.dir.y * (source.pos.y - obj->u.sphere.center.y)
			+ source.dir.z * (source.pos.z - obj->u.sphere.center.z));
	c = pow(source.pos.x - obj->u.sphere.center.x, 2)
		+ pow(source.pos.y - obj->u.sphere.center.y, 2)
		+ pow(source.pos.z - obj->u.sphere.center.z, 2)
		- pow(obj->u.sphere.radius, 2);
	det = b * b - 4 * a * c;
	if (det < 0)
		return (-1);
	else
		t = rtv1_solve_2_deg(det, a, b);
	return (t);
}
