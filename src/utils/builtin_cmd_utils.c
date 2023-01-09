/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:46:28 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/08 23:22:01 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all(t_cmd_info *data, t_var_lst **env_lst, int should_print)
{
	if (should_print)
		ft_putstr_fd("exit\n", 2);
	free(data->user_input);
	rl_clear_history();
	ft_varclear(env_lst);
	ft_cmdclear(&data->lst_cmd);
}

int	check_heredoc(t_cmd_lst *cmd)
{
	if (cmd->delimiter)
	{
		if (!execute_heredoc(cmd))
			return (0);
	}
	return (1);
}

int	execute_heredoc(t_cmd_lst *cmd)
{
	int	here_pipe[2];

	pipe(here_pipe);
	cmd->input = here_pipe[0];
	if (!get_heredoc_input(cmd, here_pipe))
		return (0);
	return (1);
}
