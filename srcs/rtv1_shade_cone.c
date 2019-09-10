/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_shade_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 09:56:38 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/10 14:11:37 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	rtv1_shade_cone_calc_proj(t_ray *ray, t_obj *obj, t_fvec3d *proj)
{
	double	length_center_inter;
	double	length_cent_proj;

	length_center_inter = sqrt(pow(ray->obj.pos.x - obj->u.cone.center.x, 2)
			+ pow(ray->obj.pos.y - obj->u.cone.center.y, 2)
			+ pow(ray->obj.pos.z - obj->u.cone.center.z, 2));
	length_cent_proj = length_center_inter
			/ cos(obj->u.cone.angle * M_PI / 180);
	proj->x = obj->u.cone.center.x + length_cent_proj * obj->u.cone.axis.x;
	proj->y = obj->u.cone.center.y + length_cent_proj * obj->u.cone.axis.y;
	proj->z = obj->u.cone.center.z + length_cent_proj * obj->u.cone.axis.z;
	if (rtv1_check_plane_side(*proj, obj->u.cone.plane, ray->obj.pos) == 1)
	{
		proj->x = obj->u.cone.center.x - length_cent_proj * obj->u.cone.axis.x;
		proj->y = obj->u.cone.center.y - length_cent_proj * obj->u.cone.axis.y;
		proj->z = obj->u.cone.center.z - length_cent_proj * obj->u.cone.axis.z;
	}
}

void		rtv1_shade_cone(t_obj *obj, t_ray *ray)
{
	t_fvec3d	norm;
	t_fvec3d	proj;
	double		length;
	double		shade;

	rtv1_shade_cone_calc_proj(ray, obj, &proj);
	norm.x = ray->obj.pos.x - proj.x;
	norm.y = ray->obj.pos.y - proj.y;
	norm.z = ray->obj.pos.z - proj.z;
	length = sqrt(norm.x * norm.x + norm.y * norm.y + norm.z * norm.z);
	if (length == 0)
		return ;
	norm.x = norm.x / length;
	norm.y = norm.y / length;
	norm.z = norm.z / length;
	shade = norm.x * ray->obj.dir.x + norm.y * ray->obj.dir.y
			+ norm.z * ray->obj.dir.z;
	if (shade <= 0)
		shade = 0;
	ray->shade = shade;
}
