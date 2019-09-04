/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check_inter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:20:03 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 16:17:00 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	rtv1_check_inter(t_obj *obj, t_geo source)
{
	double t;

	t = -1;
	if (obj->type == PLANE)
		t = rtv1_check_inter_plane(obj, source);
	if (obj->type == SPHERE)
		t = rtv1_check_inter_sphere(obj, source);
	if (obj->type == CYLINDER)
		t = rtv1_check_inter_cylinder(obj, source);
	if (obj->type == CONE)
		t = rtv1_check_inter_cone(obj, source);
	return (t);
}
