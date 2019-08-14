/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_calc_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:49:15 by pmasson           #+#    #+#             */
/*   Updated: 2019/08/14 19:35:24 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	rtv1_calc_center(t_obj *obj, t_fvec3d *center)
{
	center->x = obj->pos.x;
	center->y = obj->pos.y;
	center->z = obj->pos.z;
}

static void rtv1_calc_axis(t_obj *obj, t_fvec3d *axis)
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

static void	rtv1_calc_constant(t_obj *obj)
{
	double	length;

	obj->u.plane.constant = -obj->pos.x * obj->u.plane.equation.x
			- obj->pos.y * obj->u.plane.equation.y
			- obj->pos.z * obj->u.plane.equation.z;
	length = sqrt(pow(obj->u.plane.equation.x, 2)
			+ pow(obj->u.plane.equation.y, 2)
			+ pow(obj->u.plane.equation.z, 2));
	if (length != 0)
	{
		obj->u.plane.norm.x = obj->u.plane.equation.x / length;
		obj->u.plane.norm.y = obj->u.plane.equation.y / length;
		obj->u.plane.norm.z = obj->u.plane.equation.z / length;
	}
	else
	{
		obj->u.plane.norm.x = obj->u.plane.equation.x;
		obj->u.plane.norm.y = obj->u.plane.equation.y;
		obj->u.plane.norm.z = obj->u.plane.equation.z;
	}
}

static void	rtv1_calc_cone_matrix(t_obj *obj)
{
		create_rot_mat(obj->u.cone.mat_x, obj->rot.x * M_PI / 180, 'x');
		create_rot_mat(obj->u.cone.mat_y, obj->rot.y * M_PI / 180, 'y');
		create_rot_mat(obj->u.cone.mat_z, obj->rot.z * M_PI / 180, 'z');
	
}

void	rtv1_calc_obj(t_rt *rt)
{
	t_obj *tmp;

	tmp = rt->objs;
	while (tmp != NULL)
	{
		if (tmp->type == SPHERE)
			rtv1_calc_center(tmp, &(tmp->u.sphere.center));
		if (tmp->type == CYLINDER)
		{
			rtv1_calc_center(tmp, &(tmp->u.cylinder.center));
			rtv1_calc_axis(tmp, &(tmp->u.cylinder.axis));
		}
		if (tmp->type == CONE)
		{
			rtv1_calc_center(tmp, &(tmp->u.cone.center));
			rtv1_calc_axis(tmp, &(tmp->u.cone.axis));
			rtv1_calc_cone_matrix(tmp);
		}
		if (tmp->type == PLANE)
		{
			rtv1_calc_axis(tmp, &(tmp->u.plane.equation));
			rtv1_calc_constant(tmp);
		}
		tmp = tmp->next;
	}
}

