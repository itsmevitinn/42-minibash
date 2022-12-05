/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:00:18 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/05 12:05:47 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(int fd)
{
	t_list	*i;

	i = g_env;
	while (i)
	{
		ft_putstr_fd((char *)i->content, fd);
		write(fd, "\n", 1);
		i = i->next;
	}
}
