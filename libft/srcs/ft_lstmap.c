/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:55:44 by pmasson           #+#    #+#             */
/*   Updated: 2018/11/12 17:21:26 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*ret;

	if (lst == NULL)
		return (NULL);
	if (f == NULL)
		return (lst);
	tmp = lst;
	if (!(new = ft_lstnew(f(tmp)->content, f(tmp)->content_size)))
		return (NULL);
	ret = new;
	tmp = tmp->next;
	while (tmp)
	{
		if (!(new->next = ft_lstnew(f(tmp)->content, f(tmp)->content_size)))
			return (NULL);
		new = new->next;
		tmp = tmp->next;
	}
	new->next = NULL;
	return (ret);
}
