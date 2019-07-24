/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check_inter_cylinder.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:58:36 by pmasson           #+#    #+#             */
/*   Updated: 2019/07/11 13:10:40 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

double	rtv1_check_inter_cylinder(t_obj *obj, t_ray *ray, int s)
{
	t_terms	terms[1];
	double	det;
	double	a;
	double	b;
	double	c;

	ft_bzero(terms, sizeof(t_terms));
	terms->i = -ray->vec[1 + s] * obj->data[6] + ray->vec[2 + s] * obj->data[5];
	terms->k = -ray->vec[2 + s] * obj->data[4] + ray->vec[0 + s] * obj->data[6];
	terms->m = -ray->vec[0 + s] * obj->data[5] + ray->vec[1 + s] * obj->data[4];
	terms->j = obj->data[1] * obj->data[6] - ray->source[1 + s] * obj->data[6]
		- obj->data[2] * obj->data[5] + ray->source[2 + s] * obj->data[5];
	terms->l = obj->data[2] * obj->data[4] - ray->source[2 + s] * obj->data[4]
		- obj->data[0] * obj->data[6] + ray->source[0 + s] * obj->data[6];
	terms->n = obj->data[0] * obj->data[5] - ray->source[0 + s] * obj->data[5]
		- obj->data[1] * obj->data[4] + ray->source[1 + s] * obj->data[4];
	if ((a = pow(terms->i, 2) + pow(terms->k, 2) + pow(terms->m, 2)) == 0)
		return (ft_msg_int(2, "Error calculating a in cylinder.", -1));
	b = 2 * (terms->i * terms->j + terms->k * terms->l + terms->m * terms->n);
	c = pow(terms->j, 2) + pow(terms->l, 2) + pow(terms->n, 2)
			- pow((double)obj->data[3], 2);
	det = pow(b, 2) - 4 * a * c;
	if (det < 0)
		return (-1);
	else
		return (rtv1_solve_2_deg(det, a, b));
}
