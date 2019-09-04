/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_calc_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:49:15 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 16:23:23 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

static void	rtv1_calc_axis(t_obj *obj, t_fvec3d *axis)
{
	double	mat[3][3];

	axis->x = 0;
	axis->y = 0;
	axis->z = 1;
	if (obj->rot.x != 0)
	{
		create_rot_mat(mat, obj->rot.x * M_PI / 180, 'x');
		dot_product_column_vec(axis, mat, *axis);
	}
	if (obj->rot.y != 0)
	{
		create_rot_mat(mat, obj->rot.y * M_PI / 180, 'y');
		dot_product_column_vec(axis, mat, *axis);
	}
	if (obj->rot.x != 0)
	{
		create_rot_mat(mat, obj->rot.z * M_PI / 180, 'z');
		dot_product_column_vec(axis, mat, *axis);
	}
}

static void	rtv1_calc_constant(t_obj *obj, t_plane *plane)
{
	double	length;

	plane->constant = -obj->pos.x * plane->equation.x
		- obj->pos.y * plane->equation.y
		- obj->pos.z * plane->equation.z;
	length = sqrt(pow(plane->equation.x, 2)
			+ pow(plane->equation.y, 2)
			+ pow(plane->equation.z, 2));
	if (length != 0)
	{
		plane->norm.x = plane->equation.x / length;
		plane->norm.y = plane->equation.y / length;
		plane->norm.z = plane->equation.z / length;
	}
	else
	{
		plane->norm.x = plane->equation.x;
		plane->norm.y = plane->equation.y;
		plane->norm.z = plane->equation.z;
	}
}

static void	rtv1_calc_center(t_obj *obj, t_fvec3d *center)
{
	center->x = obj->pos.x;
	center->y = obj->pos.y;
	center->z = obj->pos.z;
	if (obj->type == SPHERE)
	{
		if (obj->u.sphere.radius <= 0)
			obj->u.sphere.radius = 10;
	}
	if (obj->type == CYLINDER)
	{
		obj->u.cylinder.plane.equation.x = obj->u.cylinder.axis.x;
		obj->u.cylinder.plane.equation.y = obj->u.cylinder.axis.y;
		obj->u.cylinder.plane.equation.z = obj->u.cylinder.axis.z;
		rtv1_calc_constant(obj, &(obj->u.cylinder.plane));
		if (obj->u.cylinder.radius <= 0)
			obj->u.cylinder.radius = 10;
	}
}

static void	rtv1_calc_cone_matrix_plane(t_obj *obj)
{
	create_rot_mat(obj->u.cone.mat_x, -obj->rot.x * M_PI / 180, 'x');
	create_rot_mat(obj->u.cone.mat_y, -obj->rot.y * M_PI / 180, 'y');
	create_rot_mat(obj->u.cone.mat_z, -obj->rot.z * M_PI / 180, 'z');
	obj->u.cone.plane.equation.x = obj->u.cone.axis.x;
	obj->u.cone.plane.equation.y = obj->u.cone.axis.y;
	obj->u.cone.plane.equation.z = obj->u.cone.axis.z;
	rtv1_calc_constant(obj, &(obj->u.cone.plane));
	if (obj->u.cone.angle <= 0)
		obj->u.cone.angle = 5;
}

void		rtv1_calc_obj(t_rt *rt)
{
	t_obj *tmp;

	tmp = rt->objs;
	while (tmp != NULL)
	{
		if (tmp->type == SPHERE)
			rtv1_calc_center(tmp, &(tmp->u.sphere.center));
		if (tmp->type == CYLINDER)
		{
			rtv1_calc_axis(tmp, &(tmp->u.cylinder.axis));
			rtv1_calc_center(tmp, &(tmp->u.cylinder.center));
		}
		if (tmp->type == CONE)
		{
			rtv1_calc_center(tmp, &(tmp->u.cone.center));
			rtv1_calc_axis(tmp, &(tmp->u.cone.axis));
			rtv1_calc_cone_matrix_plane(tmp);
		}
		if (tmp->type == PLANE)
		{
			rtv1_calc_axis(tmp, &(tmp->u.plane.equation));
			rtv1_calc_constant(tmp, &(tmp->u.plane));
		}
		tmp = tmp->next;
	}
}
