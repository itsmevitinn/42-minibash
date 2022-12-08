/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:00:18 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/08 00:11:07 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(t_list *env_lst, int fd)
{
	while (env_lst)
	{
		ft_putstr_fd((char *)env_lst->content, fd);
		write(fd, "\n", 1);
		env_lst = env_lst->next;
	}
}
