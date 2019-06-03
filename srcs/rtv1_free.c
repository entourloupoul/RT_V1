/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:17:25 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/29 21:18:18 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdlib.h>

void	rtv1_free_obj(t_obj **obj)
{
	t_obj	*tmp;
	t_obj	*prev;

	if (obj != NULL && *obj != NULL)
	{
		tmp = *obj;
		while (tmp != NULL)
		{
			free(tmp->name);
			free(tmp->data);
			prev = tmp;
			tmp = tmp->next;
			free(prev);
			prev = NULL;
		}
	}
}

void	rtv1_free_light(t_light **light)
{
	t_light	*tmp;
	t_light	*prev;

	if (light != NULL && *light != NULL)
	{
		tmp = *light;
		while (tmp != NULL)
		{
			free(tmp->coord);
			prev = tmp;
			tmp = tmp->next;
			free(prev);
			prev = NULL;
		}
	}
}

void	rtv1_free_cam(t_cam **cam)
{
	//free u v w
	if (cam != NULL && *cam != NULL)
	{
		if ((*cam)->coord != NULL)
			free((*cam)->coord);
		free(*cam);
		*cam = NULL;
	}
}

void	rtv1_free_scene(t_scene **scene)
{
	if (scene != NULL && *scene != NULL)
	{
		rtv1_free_cam(&(*scene)->cam);
		rtv1_free_light(&(*scene)->light);
		rtv1_free_obj(&(*scene)->obj);
		free((*scene)->name);
		free(*scene);
		*scene = NULL;
	}
}

void	rtv1_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

