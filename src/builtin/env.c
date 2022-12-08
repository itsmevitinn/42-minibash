/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:00:18 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/08 15:25:19 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(t_var_lst *env_lst, int fd)
{
	while (env_lst)
	{
		ft_putstr_fd(env_lst->name, fd);
		write(fd, "=", 1);
		ft_putstr_fd((char *)env_lst->content, fd);
		write(fd, "\n", 1);
		env_lst = env_lst->next;
	}
}
