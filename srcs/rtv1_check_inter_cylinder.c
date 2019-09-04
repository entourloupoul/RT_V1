/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check_inter_cylinder.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:58:36 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 15:54:33 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

static void	rtv1_calc_terms_cyl(t_obj *obj, t_geo source, t_terms *term)
{
	term->j = (obj->u.cylinder.center.y - source.pos.y) * obj->u.cylinder.axis.z
		+ (source.pos.z - obj->u.cylinder.center.z) * obj->u.cylinder.axis.y;
	term->l = (obj->u.cylinder.center.z - source.pos.z) * obj->u.cylinder.axis.x
		+ (source.pos.x - obj->u.cylinder.center.x) * obj->u.cylinder.axis.z;
	term->n = (obj->u.cylinder.center.x - source.pos.x) * obj->u.cylinder.axis.y
		+ (source.pos.y - obj->u.cylinder.center.y) * obj->u.cylinder.axis.x;
}

double		rtv1_check_inter_cylinder(t_obj *obj, t_geo source)
{
	t_terms	term[1];
	double	det;
	double	a;
	double	b;
	double	c;

	ft_bzero(term, sizeof(t_terms));
	term->i = -source.dir.y * obj->u.cylinder.axis.z
		+ source.dir.z * obj->u.cylinder.axis.y;
	term->k = -source.dir.z * obj->u.cylinder.axis.x
		+ source.dir.x * obj->u.cylinder.axis.z;
	term->m = -source.dir.x * obj->u.cylinder.axis.y
		+ source.dir.y * obj->u.cylinder.axis.x;
	if ((a = pow(term->i, 2) + pow(term->k, 2) + pow(term->m, 2)) == 0)
		return (ft_msg_int(2, "Error calculating a in cylinder.", -1));
	rtv1_calc_terms_cyl(obj, source, term);
	b = 2 * (term->i * term->j + term->k * term->l + term->m * term->n);
	c = pow(term->j, 2) + pow(term->l, 2) + pow(term->n, 2)
			- pow(obj->u.cylinder.radius, 2);
	det = pow(b, 2) - 4 * a * c;
	if (det < 0)
		return (-1);
	else
		return (rtv1_solve_2_deg(det, a, b));
}
