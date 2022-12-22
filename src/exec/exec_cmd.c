/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/22 16:50:45 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_cmds(t_cmd_info *data, t_var_lst **env_lst)
{
	data->pids = calloc(sizeof(int), data->qty);
	data->id = 0;
	while(data->lst_cmd)
	{
		if (!exec_builtin_cmd(data->lst_cmd, env_lst))
			exec_bin_cmd(data->lst_cmd, data);
		data->lst_cmd = data->lst_cmd->next;
	}
}
