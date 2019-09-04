/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:17:08 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 14:43:32 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		dot_product_square(double r[3][3], double m1[3][3], double m2[3][3])
{
	r[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0];
	r[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1];
	r[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2];
	r[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0];
	r[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1];
	r[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2];
	r[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0];
	r[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1];
	r[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2];
}

void		dot_product_column(double r[3], double m1[3][3], double col[3])
{
	r[0] = m1[0][0] * col[0] + m1[0][1] * col[1] + m1[0][2] * col[2];
	r[1] = m1[1][0] * col[0] + m1[1][1] * col[1] + m1[1][2] * col[2];
	r[2] = m1[2][0] * col[0] + m1[2][1] * col[1] + m1[2][2] * col[2];
}

void		dot_product_column_vec(t_fvec3d *r, double m1[3][3], t_fvec3d col)
{
	r->x = m1[0][0] * col.x + m1[0][1] * col.y + m1[0][2] * col.z;
	r->y = m1[1][0] * col.x + m1[1][1] * col.y + m1[1][2] * col.z;
	r->z = m1[2][0] * col.x + m1[2][1] * col.y + m1[2][2] * col.z;
}

static void	init_mat(double mat[3][3])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			mat[i][j] = 0;
			j++;
		}
		i++;
	}
}

void		create_rot_mat(double mat[3][3], double angle, char axis)
{
	init_mat(mat);
	if (axis == 'x')
	{
		mat[0][0] = 1;
		mat[1][1] = cos(angle);
		mat[1][2] = -sin(angle);
		mat[2][1] = sin(angle);
		mat[2][2] = cos(angle);
	}
	if (axis == 'y')
	{
		mat[1][1] = 1;
		mat[0][0] = cos(angle);
		mat[2][0] = -sin(angle);
		mat[0][2] = sin(angle);
		mat[2][2] = cos(angle);
	}
	if (axis == 'z')
	{
		mat[2][2] = 1;
		mat[0][0] = cos(angle);
		mat[0][1] = -sin(angle);
		mat[1][0] = sin(angle);
		mat[1][1] = cos(angle);
	}
}
