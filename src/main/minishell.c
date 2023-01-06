/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/06 17:42:34 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	run_commands(t_cmd_info *data, t_var_lst *env_lst);
static void	get_exit_status(t_cmd_lst *lst_cmd, int cmd_qty);
static void	free_resources(t_cmd_info *data);
static int	single_builtin(char *cmd_name, int cmd_qty);

int			g_exit_status;

int	main(void)
{
	t_cmd_info	data;
	t_var_lst	*env_lst;

	initialize_env(&env_lst);
	setup_signals();
	while (42)
	{
		data.user_input = display_prompt();
		if (!data.user_input)
		{
			ft_putstr_fd("exit\n", 2);
			rl_clear_history();
			ft_varclear(&env_lst);
			return (0);
		}
		else if (!whitespace_checker(data.user_input))
		{
			add_history(data.user_input);
			if (parse_input(&data, env_lst))
			{
				run_commands(&data, env_lst);
				get_exit_status(data.lst_cmd, data.qty);
				free_resources(&data);
			}
		}
			free(data.user_input);
	}
}

static void	get_exit_status(t_cmd_lst *lst_cmd, int cmd_qty)
{
	int	status;

	while (lst_cmd)
	{
		if (single_builtin(lst_cmd->args[0], cmd_qty))
			return ;
		waitpid(lst_cmd->pid, &status, 0);
		lst_cmd = lst_cmd->next;
	}
	if (!WIFEXITED(status))
		g_exit_status = 1;
	else
		g_exit_status = WEXITSTATUS(status);
}

static int	single_builtin(char *cmd_name, int cmd_qty)
{
	if (!ft_strncmp(cmd_name, "cd", 2) && cmd_qty == 1)
		return (1);
	else if (!ft_strncmp(cmd_name, "export", 6) && cmd_qty == 1)
		return (1);
	else if (!ft_strncmp(cmd_name, "unset", 5) && cmd_qty == 1)
		return (1);
	return (0);
}

static void	run_commands(t_cmd_info *data, t_var_lst *env_lst)
{
	fill_data(data);
	exec_cmds(data, &env_lst);
	close_all_pipes(data);
}

static void	free_resources(t_cmd_info *data)
{
	ft_cmdclear(&data->lst_cmd);
	free_pipes(data);
}
