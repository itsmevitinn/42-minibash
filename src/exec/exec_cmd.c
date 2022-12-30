/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/30 01:17:59 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int find_cmd_type(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst);

void exec_cmds(t_cmd_info *data, t_var_lst **env_lst)
{
	t_cmd_lst *cmd;
	int pipes_qty;

	cmd = data->lst_cmd;
	pipes_qty = data->qty - 1;
	while (cmd)
	{
		if (!find_cmd_type(cmd, data, env_lst))
		{
			if (cmd->id < pipes_qty)
				close(data->pipes[cmd->id][1]);
			break;
		}
		if (cmd->id < pipes_qty)
			close(data->pipes[cmd->id][1]);
		cmd = cmd->next;
	}
}

static int find_cmd_type(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!*cmd->args)
		return (1);
	if (is_builtin(cmd->args[0]))
	{
		if (!exec_builtin_cmd(cmd, data, env_lst))
			return (0);
	}
	else
	{
		if (!exec_bin_cmd(cmd, data, *env_lst))
			return (0);
	}
	return (1);
}
