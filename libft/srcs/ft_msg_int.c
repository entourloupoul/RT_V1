/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <pmasson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:56:44 by pmasson           #+#    #+#             */
/*   Updated: 2019/08/12 15:43:06 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_msg_int(int fd, char *msg, int ret)
{
	if (msg != NULL)
		write(fd, msg, ft_strlen(msg));
	return (ret);
}
