/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 22:16:40 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/30 01:30:13 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void start_pipes(t_cmd_info *data);
static void precedence_analyzer(t_cmd_info *data);
static void handle_cmd_pipes(t_cmd_lst *cmd, t_cmd_info *data);
static void handle_builtin_cmd(t_cmd_lst *cmd, int **pipes, int cmd_qty);
static void handle_bin_cmd(t_cmd_lst *cmd, int **pipes, int cmd_qty);

void fill_data(t_cmd_info *data)
{
	data->pipes = NULL;
	cmds_quantity(data);
	if (data->qty >= 2)
	{
		start_pipes(data);
		precedence_analyzer(data);
	}
}

static void precedence_analyzer(t_cmd_info *data)
{
	t_cmd_lst *temp_cmd;

	temp_cmd = data->lst_cmd;
	while (temp_cmd)
	{
		handle_cmd_pipes(temp_cmd, data);
		temp_cmd = temp_cmd->next;
	}
}

static void handle_cmd_pipes(t_cmd_lst *cmd, t_cmd_info *data)
{
	if (!*cmd->args)
		return ;
	if (is_builtin(cmd->args[0]))
		handle_builtin_cmd(cmd, data->pipes, data->qty);
	else
		handle_bin_cmd(cmd, data->pipes, data->qty);
	return ;
}

static void handle_builtin_cmd(t_cmd_lst *cmd, int **pipes, int cmd_qty)
{
	int last_id;

	last_id = cmd_qty - 1;
	// redirect not found: cmd->output == 1
	if (cmd->output == 1 && cmd->id != last_id)
		cmd->output = pipes[cmd->id][1];
}

static void handle_bin_cmd(t_cmd_lst *cmd, int **pipes, int cmd_qty)
{
	int last_id;

	last_id = cmd_qty - 1;
	// redirect output not found: cmd->output == 1
	if (cmd->output == 1 && cmd->id != last_id)
		cmd->output = pipes[cmd->id][1]; // so, go to pipe
	// redirect input not found: cmd->input == 0
	if (cmd->input == 0 && cmd->id != 0)
		cmd->input = pipes[cmd->id - 1][0];
}

static void start_pipes(t_cmd_info *data)
{
	int pipes_qty;
	int pipes_index;

	pipes_qty = data->qty - 1;
	pipes_index = 0;
	data->pipes = (int **)malloc(sizeof(int *) * pipes_qty);
	while (pipes_index < pipes_qty)
	{
		data->pipes[pipes_index] = (int *)malloc(sizeof(int) * 2);
		pipe(data->pipes[pipes_index++]);
	}
}
