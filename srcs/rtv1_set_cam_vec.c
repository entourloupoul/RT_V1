/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_set_cam_vec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:18:49 by pmasson           #+#    #+#             */
/*   Updated: 2019/08/14 18:36:29 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <math.h>

static int	rtv1_rot_cam(t_cam *cam)
{
	double		mat[3][3];

	if (cam->rot.x != 0)
	{
		puts("yo");
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

int		rtv1_set_cam_vec(t_cam *cam)
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
	printf("%f\n%f\n%f\n", cam->u.x, cam->u.y, cam->u.z);
	printf("%f\n%f\n%f\n", cam->v.x, cam->v.y, cam->v.z);
	printf("%f\n%f\n%f\n", cam->w.x, cam->w.y, cam->w.z);
	printf("pos\n%f\n%f\n%f\n", cam->pos.x, cam->pos.y, cam->pos.z);
	printf("rot\n%f\n%f\n%f\n", cam->rot.x, cam->rot.y, cam->rot.z);
	return (1);
}
