/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:24:24 by pmasson           #+#    #+#             */
/*   Updated: 2018/11/16 11:47:15 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd	*ft_create_elem(int fd)
{
	t_fd	*new;
	char	*content;

	if (!(new = (t_fd *)malloc(sizeof(t_fd))))
		return (NULL);
	if (!(content = (char *)malloc(sizeof(char))))
		return (NULL);
	content[0] = '\0';
	if (!(new->str = ft_strdup(content)))
		return (NULL);
	free(content);
	new->fd = fd;
	new->next = NULL;
	return (new);
}

int		ft_read(int fd, t_fd **lst)
{
	int		j;
	char	buff[BUFF_SIZE + 1];
	t_fd	*tmp;
	char	*ant;

	ft_bzero(buff, BUFF_SIZE + 1);
	tmp = *lst;
	while (tmp->fd != fd)
		tmp = tmp->next;
	while ((j = read(fd, buff, BUFF_SIZE)) > 0 && ft_strchr(buff, 10) == NULL)
	{
		ant = tmp->str;
		if (!(tmp->str = ft_strjoin(tmp->str, buff)))
			return (-1);
		free(ant);
		ft_strclr(buff);
	}
	ant = tmp->str;
	if (!(tmp->str = ft_strjoin(tmp->str, buff)))
		return (-1);
	free(ant);
	return (j);
}

void	*ft_get_line(t_fd **lst, char **line, int fd)
{
	int				i;
	unsigned long	len;
	t_fd			*tmp;

	tmp = *lst;
	while (tmp->fd != fd)
		tmp = tmp->next;
	i = 0;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '\n')
		{
			len = ft_strlen(tmp->str);
			if (!(*line = ft_strsub(tmp->str, 0, (size_t)i)))
				return (NULL);
			tmp->str = ft_strncpy(tmp->str, tmp->str + i + 1, len);
			return (*line);
		}
		i++;
	}
	if (!(*line = ft_strdup(tmp->str)))
		return (NULL);
	ft_strclr(tmp->str);
	return (*line);
}

int		get_next_line(const int fd, char **line)
{
	static t_fd		*lst = NULL;
	t_fd			*tmp;
	int				iread;

	tmp = lst;
	while (tmp != NULL && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		if ((tmp = ft_create_elem(fd)) == NULL)
			return (-1);
		tmp->next = lst;
		lst = tmp;
	}
	if ((iread = ft_read(fd, &lst)) < 0)
		return (-1);
	if (iread == 0 && tmp->str[0] == '\0')
		return (0);
	if (!(ft_get_line(&lst, line, fd)))
		return (-1);
	return (1);
}
