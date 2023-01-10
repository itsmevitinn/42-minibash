/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:11:41 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/09 22:32:25 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	single_builtin(char *cmd_name, int cmd_qty);

void	handle_eof(t_var_lst **var_lst)
{
	ft_putstr_fd("exit\n", 2);
	rl_clear_history();
	ft_varclear(var_lst);
	exit(EXIT_SUCCESS);
}

void	get_exit_status(t_cmd_lst *lst_cmd, int cmd_qty)
{
	t_cmd_lst	*last_cmd;
	int			status;

	if (single_builtin(lst_cmd->args[0], cmd_qty))
		return ;
	while (lst_cmd)
	{
		waitpid(lst_cmd->pid, &status, 0);
		last_cmd = lst_cmd;
		lst_cmd = lst_cmd->next;
	}
	if (!last_cmd->not_found && last_cmd->args[0])
	{
		if (!WIFEXITED(status))
			g_exit_status = 130;
		else
			g_exit_status = WEXITSTATUS(status);
	}
}

static int	single_builtin(char *cmd_name, int cmd_qty)
{
	if (cmd_name)
	{
		if ((is_builtin("cd") || is_builtin("/usr/bin/cd")) && cmd_qty == 1)
			return (1);
		else if (is_builtin("export") && cmd_qty == 1)
			return (1);
		else if (is_builtin("unset") && cmd_qty == 1)
			return (1);
	}
	return (0);
}

void	run_commands(t_cmd_info *data)
{
	fill_data(data);
	exec_cmds(data, &data->env_lst);
	close_all_pipes(data);
}

void	free_resources(t_cmd_info *data)
{
	ft_cmdclear(&data->lst_cmd);
	free_pipes(data);
}
