/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:27:16 by pmasson           #+#    #+#             */
/*   Updated: 2019/08/14 18:36:26 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <stdlib.h>

static int	rtv1_get_color_obj(t_obj *obj, char *line)
{
	char	*color;
	double		nb_color;

	if (!(color = ft_convert_base("0123456789ABCDEF", "0123456789", line + 8)))
		return (ft_msg_int(2, "Error, failed convert base.\n", -1));
	if (ft_strlen(line) > 14 || rtv1_atoi(color, &nb_color) != 1)
	{
		free(color);
		return (ft_msg_int(2, "Error, wrong color format.\n", -1));
	}
	free(color);
	if (nb_color < 0)
		return (ft_msg_int(2, "Error, color can't be negative.\n", -1));
	obj->color.color = (int32_t)nb_color;
	return (1);
}

static int	rtv1_fill_obj(t_obj *obj, char *line)
{
	if (ft_strncmp(line, "name=", 5) == 0)
	{
		if (obj->name != NULL)
			return (ft_msg_int(2, "Error, obj ca have only 1 name.\n", -1));
		if (!(obj->name = ft_strdup(line + 5)))
			return (ft_msg_int(2, "Error, name dup failed.\n", -1));
	}
	else if (ft_strncmp(line, "rot=", 4) == 0
			|| ft_strncmp(line, "pos=", 4) == 0
			|| ft_strncmp(line, "radius=", 7) == 0
			|| ft_strncmp(line, "angle=", 6) == 0)
		return (rtv1_get_coord_obj(obj, line));
	else if (ft_strcmp(line, "shining") == 0)
		obj->is_shine = 1;
	else if (ft_strncmp(line, "color=0x", 8) == 0)
		return (rtv1_get_color_obj(obj, line));
	else
		return (ft_msg_int(2, "Error, wrong term in objs.\n", -1));
	return (1);
}

static void	rtv1_get_obj2(t_rt *rt, t_obj *new, char *line)
{
	t_obj *tmp;

	if (ft_strcmp(line, "plane") == 0)
		new->type = PLANE;
	else if (ft_strcmp(line, "sphere") == 0)
		new->type = SPHERE;
	else if (ft_strcmp(line, "cylinder") == 0)
		new->type = CYLINDER;
	else if (ft_strcmp(line, "cone") == 0)
		new->type = CONE;
	if (rt->objs == NULL)
		rt->objs = new;
	else
	{
		tmp = rt->objs;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}


int		rtv1_get_obj(t_rt *rt, char *line)
{
	t_obj	*new;
	t_obj	*tmp;

	if (ft_strcmp(line, "plane") == 0 || ft_strcmp(line, "sphere") == 0
			|| ft_strcmp(line, "cylinder") == 0 || ft_strcmp(line, "cone") == 0) 
	{
		if (!(new = (t_obj *)malloc(sizeof(t_obj) * 1)))
			return (-1);
		ft_bzero(new, sizeof(t_obj));
		rtv1_get_obj2(rt, new, line);
		return (1);
	}
	tmp = rt->objs;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (rtv1_fill_obj(tmp, line));
}
