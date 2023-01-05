/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence_analyzer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:13:20 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/04 22:22:34 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	precedence_analyzer(t_cmd_info *data)
{
	t_cmd_lst	*temp_cmd;

	temp_cmd = data->lst_cmd;
	while (temp_cmd)
	{
		handle_cmd_pipes(temp_cmd, data);
		temp_cmd = temp_cmd->next;
	}
}

void	handle_cmd_pipes(t_cmd_lst *cmd, t_cmd_info *data)
{
	if (!*cmd->args)
		return ;
	if (is_builtin(cmd->args[0]))
		handle_builtin_cmd(cmd, data->pipes, data->qty);
	else
		handle_bin_cmd(cmd, data->pipes, data->qty);
	return ;
}

void	handle_builtin_cmd(t_cmd_lst *cmd, int **pipes, int cmd_qty)
{
	int	last_id;

	last_id = cmd_qty - 1;
	if (cmd->output == 1 && cmd->id != last_id)
		cmd->output = pipes[cmd->id][1];
}

void	handle_bin_cmd(t_cmd_lst *cmd, int **pipes, int cmd_qty)
{
	int	last_id;

	last_id = cmd_qty - 1;
	if (cmd->output == 1 && cmd->id != last_id)
		cmd->output = pipes[cmd->id][1];
	if (cmd->input == 0 && cmd->id != 0)
		cmd->input = pipes[cmd->id - 1][0];
}
