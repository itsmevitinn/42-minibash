/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:00:18 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/06 16:42:25 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(t_cmd_lst *cmd, t_var_lst *env_lst)
{
	cmd->pid = fork();
	if (!cmd->pid)
	{
		while (env_lst)
		{
			if (env_lst->content)
			{
				ft_putstr_fd(env_lst->name, cmd->output);
				write(cmd->output, "=", 1);
				ft_putstr_fd((char *)env_lst->content, cmd->output);
				write(cmd->output, "\n", 1);
			}
			env_lst = env_lst->next;
		}
		exit(0);
	}
}
