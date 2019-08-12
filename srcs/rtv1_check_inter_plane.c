/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check_inter_plane.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:26:19 by pmasson           #+#    #+#             */
/*   Updated: 2019/08/12 15:30:14 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	rtv1_check_inter_plane(t_obj *obj, t_geo source)
{
	double	t;
	double	den;
	double	num;

	den = obj->u.plane.equation.x * source.dir.x + obj->u.plane.equation.y
		* source.dir.y + obj->u.plane.equation.z * source.dir.z;
	if (den == 0)
		return (-1);
	num = -obj->u.plane.constant
		- obj->u.plane.equation.x * source.pos.x
		- obj->u.plane.equation.y * source.pos.y
		- obj->u.plane.equation.z * source.pos.z;
	t = num / den;
	return (t);
}
