/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:27:16 by pmasson           #+#    #+#             */
/*   Updated: 2019/06/03 14:47:32 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <stdlib.h>

static int	rtv1_get_color_obj(t_obj *obj, char *line)
{
	char *color;

	if (!(color = ft_convert_base(HEXA, DEC, line + 8)))
		return (ft_msg_int(2, "Error, failed convert base.\n", -1));
	if (ft_strlen(line) > 14 || rtv1_atoi(color, &obj->color) != 1)
	{
		free(color);
		return (ft_msg_int(2, "Error, wrong color format.\n", -1));
	}
	free(color);
	if (obj->color < 0)
		return (ft_msg_int(2, "Error, color can't be negative.\n", -1));
	return (1);
}

static int	rtv1_fill_obj(t_obj *obj, char *line)
{
	if (obj->opt == 0 && ft_strncmp(line, "name=", 5) != 0)
		return (ft_msg_int(2, "Error, param of obj should be name.\n", -1));
	if (obj->opt == 0 && !(obj->name = ft_strdup(line + 5)))
		return (ft_msg_int(2, "Error, dup name object", -1));
	if (obj->opt == 0)
	{
		obj->opt = 1;
		return (1);
	}
	else if ((line[0] == 'c' || line[0] == 'r' || line[0] == 'e'
				|| line[0] == 'a' || line[0] == 'l') && line[1] == '=')
		return (rtv1_get_coord_obj(obj, line));
	else if (ft_strcmp(line, "shining") == 0)
		obj->opt = obj->opt | 32;
	else if (ft_strncmp(line, "color=0x", 8) == 0)
		return (rtv1_get_color_obj(obj, line));
	else
		return (ft_msg_int(2, "Error, wrong term in objs.\n", -1));
	return (1);
}

static void	rtv1_get_obj2(t_scene *scene, t_obj *new)
{
	t_obj *tmp;

	if (scene->obj == NULL)
		scene->obj = new;
	else
	{
		tmp = scene->obj;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void	rtv1_new_obj(t_obj *new, char *line)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		new->data[i] = 0;
		i++;
	}
	new->opt = 0;
	new->name = NULL;
	new->color = 0x000000;
	if (ft_strcmp(line, "plane") == 0)
		new->type = 1;
	else if (ft_strcmp(line, "sphere") == 0)
		new->type = 2;
	else if (ft_strcmp(line, "cylinder") == 0)
		new->type = 3;
	else if (ft_strcmp(line, "cone") == 0)
		new->type = 4;
}

int		rtv1_get_obj(t_scene *scene, char *line)
{
	t_obj	*new;
	t_obj	*tmp;

	if (ft_strcmp(line, "plane") == 0 || ft_strcmp(line, "sphere") == 0
			|| ft_strcmp(line, "cylinder") == 0 || ft_strcmp(line, "cone") == 0) 
	{
		if (!(new = (t_obj *)malloc(sizeof(t_obj) * 1)))
			return (-1);
		if (!(new->data = (int *)malloc(sizeof(int) * 8)))
		{
			free(new);
			return (-1);
		}
		if (!(new->norm = (double *)malloc(sizeof(double) * 3)))
		{
			free(new->data);
			free(new);
			return (-1);
		}
		rtv1_new_obj(new, line);
		new->next = NULL;
		rtv1_get_obj2(scene, new);
		return (1);
	}
	tmp = scene->obj;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (rtv1_fill_obj(tmp, line));
}
