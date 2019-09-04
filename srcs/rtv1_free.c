/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:17:25 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 14:49:30 by pmasson          ###   ########.fr       */
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
			prev = tmp;
			tmp = tmp->next;
			free(prev);
			prev = NULL;
		}
	}
}

void	rtv1_free_scene(t_rt **rt)
{
	if (rt != NULL && *rt != NULL)
	{
		rtv1_free_light(&(*rt)->lights);
		rtv1_free_obj(&(*rt)->objs);
		free((*rt)->name);
		free(*rt);
		*rt = NULL;
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
