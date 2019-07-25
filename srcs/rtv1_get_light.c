/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:04:17 by pmasson           #+#    #+#             */
/*   Updated: 2019/07/25 11:55:00 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdlib.h>

static void	rtv1_light_lst(t_rt *rt, t_light *new)
{
	t_light	*tmp;

	if (rt->lights == NULL)
		rt->lights = new;
	else
	{
		tmp = rt->lights;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int  rtv1_get_light(t_scene *scene, char **nb, int *count, char *line)
{
	t_light *new;
	int		ret;
	double	vec[3];

	ft_bzero(vec, sizeof(double) * 3);
	if (line[0] != 'p')
		return (-1);
	if (!(new = (t_light *)malloc(sizeof(t_light) * 1)))
		return (-1);
	ret = 1;
	while (ret == 1 && nb[*count] != NULL && *count < 3)
	{
		ret = rtv1_atoi(nb[*count], &vec[*count]);
		*count = *count + 1;
	}
	new->pos->x = vec[0];
	new->pos->y = vec[1];
	new->pos->z = vec[2];
	new->next = NULL;
	rtv1_light_lst(scene, new);
	return (ret);
}
