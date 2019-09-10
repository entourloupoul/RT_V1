/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_create_final.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 16:30:17 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/10 14:06:46 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

static int	rtv1_calc_surf2(t_rt *rt, double x, double y, t_ray *ray)
{
	if (rtv1_get_color(rt, ray) <= 0)
		return (0);
	*((uint32_t *)(rt->sdl.surface->pixels + 4 * (int)x + 4 * (int)y
				* (int)rt->cam.px_screen_size.x)) = ray->color.color;
	return (1);
}

static void	rtv1_calc_ray_dir_y(t_ray *ray, t_rt *rt, double x, double y)
{
	ray->cam.dir.x = -rt->cam.w.x + rt->cam.screen_ratio.x
		* (x / rt->cam.px_screen_size.x - 0.5) * rt->cam.u.x
		+ rt->cam.screen_ratio.y * (0.5 - y / rt->cam.px_screen_size.y)
		* rt->cam.v.x;
	ray->cam.dir.y = -rt->cam.w.y + rt->cam.screen_ratio.x
		* (x / rt->cam.px_screen_size.x - 0.5) * rt->cam.u.y
		+ rt->cam.screen_ratio.y * (0.5 - y / rt->cam.px_screen_size.y)
		* rt->cam.v.y;
	ray->cam.dir.z = -rt->cam.w.z + rt->cam.screen_ratio.x
		* (x / rt->cam.px_screen_size.x - 0.5) * rt->cam.u.z
		+ rt->cam.screen_ratio.y * (0.5 - y / rt->cam.px_screen_size.y)
		* rt->cam.v.z;
}

static void	rtv1_calc_ray_dir_x(t_ray *ray, t_rt *rt)
{
	ray->cam.dir.x = ray->cam.dir.x + rt->cam.screen_ratio.x
		* (1 / rt->cam.px_screen_size.x) * rt->cam.u.x;
	ray->cam.dir.y = ray->cam.dir.y + rt->cam.screen_ratio.x
		* (1 / rt->cam.px_screen_size.x) * rt->cam.u.y;
	ray->cam.dir.z = ray->cam.dir.z + rt->cam.screen_ratio.x
		* (1 / rt->cam.px_screen_size.x) * rt->cam.u.z;
}

static int	rtv1_calc_surf(t_rt *rt)
{
	double	x;
	double	y;
	t_ray	ray[1];

	ft_bzero(ray, sizeof(t_ray));
	ray->cam.pos.x = rt->cam.pos.x;
	ray->cam.pos.y = rt->cam.pos.y;
	ray->cam.pos.z = rt->cam.pos.z;
	ray->shadows = rt->shadows;
	x = 0;
	y = 0;
	while (y < rt->cam.px_screen_size.y)
	{
		x = 0;
		rtv1_calc_ray_dir_y(ray, rt, x, y);
		while (x < rt->cam.px_screen_size.x)
		{
			rtv1_calc_surf2(rt, x, y, ray);
			rtv1_calc_ray_dir_x(ray, rt);
			ray->shade = 0;
			x = x + 1;
		}
		y = y + 1;
	}
	return (0);
}

int			rtv1_create_final(t_rt *rt)
{
	double	ratio;

	rt->cam.px_screen_size.x = rt->sdl.size.x;
	rt->cam.px_screen_size.y = rt->sdl.size.y;
	if (rt->cam.px_screen_size.x <= 10 || rt->cam.px_screen_size.y <= 10)
		return (ft_msg_int(2, "Error, width/length can't be 0 or less.\n", -1));
	ratio = rt->cam.px_screen_size.x / rt->cam.px_screen_size.y;
	rt->cam.screen_normal = 1;
	rt->cam.screen_ratio.x = 2 * tan(45 * M_PI / 180);
	rt->cam.screen_ratio.y = rt->cam.screen_ratio.x / ratio;
	if (rtv1_set_cam_vec(&(rt->cam)) < 0)
		return (-1);
	if (rtv1_calc_surf(rt) < 0)
		return (-1);
	return (1);
}
