/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:00 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/23 15:20:31 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void pwd(t_cmd_lst *cmd, t_cmd_info *data)
{
	data->pids[cmd->id] = fork();
	if (!data->pids[cmd->id])
	{
		char *pwd;

		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, cmd->output);
		ft_putchar_fd('\n', cmd->output);
		free(pwd);
		exit(0);
	}
}