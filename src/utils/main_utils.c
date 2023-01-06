/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:11:41 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/06 18:21:04 by gcorreia         ###   ########.fr       */
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
