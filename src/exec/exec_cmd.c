/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/25 15:58:29 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_cmds(t_cmd_info *data, t_var_lst **env_lst)
{
	t_cmd_lst	*cmd;

	cmd = data->lst_cmd;
	while(cmd)
	{
		if (!exec_builtin_cmd(cmd, data, env_lst))
			if (!exec_bin_cmd(cmd, data, *env_lst))
			{
				g_exit_status = 1;
				break;
			}
		cmd = cmd->next;
	}
}

//static void clear_cmds(t_cmd_info *data)
//{
//	t_cmd_lst *temp;
//
//	while(data->lst_cmd)
//	{
//		temp = data->lst_cmd->next;
//		free(data->lst_cmd);
//		data->lst_cmd = temp;
//	}
//}
