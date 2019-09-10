/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_set_cam_vec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:18:49 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/10 14:11:32 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static int	rtv1_rot_cam(t_cam *cam)
{
	double		mat[3][3];

	if (cam->rot.x != 0)
	{
		create_rot_mat(mat, cam->rot.x * M_PI / 180, 'x');
		dot_product_column_vec(&(cam->u), mat, cam->u);
		dot_product_column_vec(&(cam->v), mat, cam->v);
		dot_product_column_vec(&(cam->w), mat, cam->w);
	}
	if (cam->rot.y != 0)
	{
		create_rot_mat(mat, cam->rot.y * M_PI / 180, 'y');
		dot_product_column_vec(&(cam->u), mat, cam->u);
		dot_product_column_vec(&(cam->v), mat, cam->v);
		dot_product_column_vec(&(cam->w), mat, cam->w);
	}
	if (cam->rot.z != 0)
	{
		create_rot_mat(mat, cam->rot.z * M_PI / 180, 'z');
		dot_product_column_vec(&(cam->u), mat, cam->u);
		dot_product_column_vec(&(cam->v), mat, cam->v);
		dot_product_column_vec(&(cam->w), mat, cam->w);
	}
	return (1);
}

int			rtv1_set_cam_vec(t_cam *cam)
{
	cam->u.x = 1;
	cam->u.y = 0;
	cam->u.z = 0;
	cam->v.x = 0;
	cam->v.y = 0;
	cam->v.z = 1;
	cam->w.x = 0;
	cam->w.y = -1;
	cam->w.z = 0;
	if (rtv1_rot_cam(cam) < 0)
		return (-1);
	return (1);
}
