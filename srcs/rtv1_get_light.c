/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:04:17 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/09 14:47:01 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdlib.h>

static void	rtv1_light_lst(t_scene *scene, t_light *new)
{
	t_light	*tmp;

	if (scene->light == NULL)
	{
		new->nb = 0;
		scene->light = new;
	}
	else
	{
		tmp = scene->light;
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->nb = tmp->nb + 1;
		tmp->next = new;
	}
}

int  rtv1_get_light(t_scene *scene, char **nb, int *i, char *line)
{
	t_light *new;
	int		ret;

	if (line[0] != 't')
		return (-1);
	if (!(new = (t_light *)malloc(sizeof(t_light) * 1)))
		return (-1);
	if (!(new->coord = (int *)malloc(sizeof(int) * 4)))
	{
		free(new);
		return (-1);
	}
	ret = 1;
	while (ret == 1 && nb[*i] != NULL && *i < 3)
	{
		ret = rtv1_atoi(nb[*i], &new->coord[*i]);
		*i = *i + 1;
	}
	new->next = NULL;
	rtv1_light_lst(scene, new);
	return (ret);
}
