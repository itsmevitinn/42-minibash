/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/23 16:08:30 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int g_exit_status;
static void fill_data(t_cmd_info *data);
static void start_pipes(t_cmd_info *data);
static void cmds_quantity(t_cmd_info *data);
static void precedence_analyzer(t_cmd_info *data);
static void use_pipes(t_cmd_info *data);
static void handle_not_builtin(t_cmd_lst *cmd, int **pipes, int cmd_qty);
static void handle_builtin(t_cmd_lst *cmd, int **pipes, int cmd_qty);
static void wait_childs(t_cmd_info *data);

int main(void)
{
	t_cmd_info data;
	t_var_lst *env_lst;
	char *user_input;

	initialize_env(&env_lst);
	setup_signals();
	while (42)
	{
		printf("last exit status: %i\n", g_exit_status);
		user_input = display_prompt();
		if (!user_input)
		{
			// when ctrl + d is pressed
			rl_clear_history();
			ft_varclear(&env_lst);
			return (0);
		}
		else if (!whitespace_checker(user_input))
		{
			add_history(user_input);
			data.lst_cmd = parse_input(user_input, env_lst);
		}
		fill_data(&data);
		exec_cmds(&data, &env_lst);
		if (data.qty >= 2)
			close_all_pipes(&data);
		wait_childs(&data);
		free(user_input);
	}
}

static void wait_childs(t_cmd_info *data)
{
	int status;
	int i;

	i = -1;
	while (data->pids[++i])
		waitpid(data->pids[i], &status, 0);
	g_exit_status = WEXITSTATUS(status);
}

static void fill_data(t_cmd_info *data)
{
	cmds_quantity(data);
	if (data->qty >= 2)
	{
		start_pipes(data);
		use_pipes(data);
	}
}

static void use_pipes(t_cmd_info *data)
{
	precedence_analyzer(data);
}

static void precedence_analyzer(t_cmd_info *data)
{
	t_cmd_lst *temp_cmd;

	temp_cmd = data->lst_cmd;
	while (temp_cmd)
	{
		if (is_builtin(temp_cmd->args[0]))
			handle_builtin(temp_cmd, data->pipes, data->qty);
		else
			handle_not_builtin(temp_cmd, data->pipes, data->qty);
		temp_cmd = temp_cmd->next;
	}
}

static void handle_not_builtin(t_cmd_lst *cmd, int **pipes, int cmd_qty)
{
	int last_id;

	last_id = cmd_qty - 1;
	// redirect output not found: cmd->output == 1
	if (cmd->output == 1 && cmd->id != last_id)
	{
		cmd->output = pipes[cmd->id][1]; // so, go to pipe
		printf("nao-builtin \"%s\" teve o output redirecionado para um pipe\n", cmd->args[0]);
	}
	// redirect input not found: cmd->input == 0
	if (cmd->input == 0 && cmd->id != 0)
	{
		cmd->input = pipes[cmd->id - 1][0];
		printf("nao-builtin \"%s\" teve input redirecionado de um pipe\n", cmd->args[0]);
	}
}

static void handle_builtin(t_cmd_lst *cmd, int **pipes, int cmd_qty)
{
	int last_id;

	last_id = cmd_qty - 1;
	// redirect not found: cmd->output == 1
	if (cmd->output == 1 && cmd->id != last_id)
	{
		// if not found, go to pipe
		cmd->output = pipes[cmd->id][1];
		printf("builtin \"%s\" teve o output redirecionado para um pipe\n", cmd->args[0]);
	}
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

static void cmds_quantity(t_cmd_info *data)
{
	t_cmd_lst *temp;
	int qty;

	temp = data->lst_cmd;
	qty = 0;
	while (temp)
	{
		qty++;
		temp = temp->next;
	}
	data->qty = qty;
}

int whitespace_checker(char *input)
{
	int i;

	i = 0;
	while (input[i])
		if (!ft_isspace(input[i++]))
			return (0);
	return (1);
}
