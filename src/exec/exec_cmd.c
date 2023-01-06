/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/06 16:39:59 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	error_found(t_cmd_lst *cmd);
static void	find_cmd_type(t_cmd_lst *cmd, t_cmd_info *data,
				t_var_lst **env_lst);

void	exec_cmds(t_cmd_info *data, t_var_lst **env_lst)
{
	t_cmd_lst	*cmd;

	cmd = data->lst_cmd;
	while (cmd)
	{
		if (!error_found(cmd))
			find_cmd_type(cmd, data, env_lst);
		cmd = cmd->next;
	}
}

static void	find_cmd_type(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (is_builtin(cmd->args[0]))
		exec_builtin_cmd(cmd, data, env_lst);
	else
		exec_bin_cmd(cmd, data, *env_lst);
}

static int	error_found(t_cmd_lst *cmd)
{
	if (cmd->input == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->in_file, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (1);
	}
	else if (!*cmd->args)
		return (1);
	return (0);
}
