/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/24 18:35:51 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static void clear_cmds(t_cmd_info *data);

void	exec_cmds(t_cmd_info *data, t_var_lst **env_lst)
{
	while(data->lst_cmd)
	{
		if (!exec_builtin_cmd(data->lst_cmd, data, env_lst))
			if (!exec_bin_cmd(data->lst_cmd, data, *env_lst))
			{
				g_exit_status = 1;
				break;
			}
		data->lst_cmd = data->lst_cmd->next;
	}
	clear_cmds(data);
}

static void clear_cmds(t_cmd_info *data)
{
	t_cmd_lst *temp;

	while(data->lst_cmd)
	{
		temp = data->lst_cmd->next;
		free(data->lst_cmd);
		data->lst_cmd = temp;
	}
}