/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:23:15 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/10 14:07:55 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

static int	rtv1_modif_ray(t_ray *ray, double t, t_light *light)
{
	double	length;

	if (light != NULL)
	{
		ray->obj.pos.x = ray->cam.pos.x + t * ray->cam.dir.x;
		ray->obj.pos.y = ray->cam.pos.y + t * ray->cam.dir.y;
		ray->obj.pos.z = ray->cam.pos.z + t * ray->cam.dir.z;
		ray->obj.dir.x = light->pos.x - ray->obj.pos.x;
		ray->obj.dir.y = light->pos.y - ray->obj.pos.y;
		ray->obj.dir.z = light->pos.z - ray->obj.pos.z;
		length = sqrt(pow(ray->obj.dir.x, 2) + pow(ray->obj.dir.y, 2)
				+ pow(ray->obj.dir.z, 2));
		if (length == 0)
			return (ft_msg_int(2, "length = 0 rtv1_modif_ray.\n", 0));
		ray->obj.dir.x = ray->obj.dir.x / length;
		ray->obj.dir.y = ray->obj.dir.y / length;
		ray->obj.dir.z = ray->obj.dir.z / length;
	}
	return (1);
}

static void	rtv1_calc_final_color(t_ray *ray)
{
	if (ray->final_shade > 1)
		ray->final_shade = 1;
	ray->color.p.r = (uint8_t)round(ray->color.p.r
			* (ray->ambient + (1 - ray->ambient) * ray->final_shade))
			+ (255 - ray->color.p.r) * ray->coef_shine;
	ray->color.p.g = (uint8_t)round(ray->color.p.g
			* (ray->ambient + (1 - ray->ambient) * ray->final_shade))
			+ (255 - ray->color.p.g) * ray->coef_shine;
	ray->color.p.b = (uint8_t)round(ray->color.p.b
			* (ray->ambient + (1 - ray->ambient) * ray->final_shade))
			+ (255 - ray->color.p.b) * ray->coef_shine;
}

static void	rtv1_get_new_inter(t_rt *rt, t_obj *obj, t_light *nlight,
		t_ray *ray)
{
	t_obj	*save;
	t_obj	*tmp;
	double	t2;
	double	ret;

	save = NULL;
	t2 = -1;
	tmp = rt->objs;
	while (tmp != NULL)
	{
		if ((ret = rtv1_check_inter(tmp, ray->obj)) >= 0)
		{
			if (tmp != obj && (t2 < 0 || (t2 > 0 && ret < t2))
					&& ret < nlight->dist)
			{
				t2 = ret;
				save = tmp;
			}
		}
		tmp = tmp->next;
	}
	ray->dist = t2;
	rtv1_get_shade(nlight, obj, ray, save);
	ray->final_shade += ray->shade;
}

static int	rtv1_get_color2(t_rt *rt, t_obj *obj, t_ray *ray, double t)
{
	t_light *nlight;

	if (t < 0)
		return (0);
	ray->color.color = obj->color.color;
	if (rt->lights == NULL)
		return (1);
	nlight = rt->lights;
	while (nlight != NULL)
	{
		rtv1_modif_ray(ray, t, nlight);
		nlight->dist = sqrt(pow(nlight->pos.x - ray->obj.pos.x, 2)
				+ pow(nlight->pos.y - ray->obj.pos.y, 2)
				+ pow(nlight->pos.z - ray->obj.pos.z, 2));
		rtv1_get_new_inter(rt, obj, nlight, ray);
		if (ray->shade >= 0.95 && obj->is_shine == 1)
		{
			ray->coef_shine += (ray->shade - 0.95) * 27;
			if (ray->coef_shine > 1)
				ray->coef_shine = 1;
		}
		nlight = nlight->next;
	}
	rtv1_calc_final_color(ray);
	return (1);
}

int			rtv1_get_color(t_rt *rt, t_ray *ray)
{
	t_obj	*tmp;
	t_obj	*save;
	double	t;
	double	ret;

	t = -1;
	save = NULL;
	tmp = rt->objs;
	ray->final_shade = 0;
	ray->shade = 0;
	ray->coef_shine = 0;
	while (tmp != NULL)
	{
		if ((ret = rtv1_check_inter(tmp, ray->cam)) >= 0)
		{
			if (t < 0 || (t > 0 && ret < t))
			{
				t = ret;
				save = tmp;
			}
		}
		tmp = tmp->next;
	}
	return (rtv1_get_color2(rt, save, ray, t));
}
