/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 23:08:43 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/02 21:19:29 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	finish_bin_cmd(t_cmd_lst *cmd)
{
	int	status;

	waitpid(cmd->pid, &status, 0);
	if (!WIFEXITED(status))
	{
		g_exit_status = 1;
		return (0);
	}
	else
		g_exit_status = WEXITSTATUS(status);
	return (1);
}

void	command_not_found(t_cmd_lst *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
