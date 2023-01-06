/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:00 by Vitor             #+#    #+#             */
/*   Updated: 2023/01/06 16:42:52 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(t_cmd_lst *cmd)
{
	char	*pwd;

	cmd->pid = fork();
	if (!cmd->pid)
	{
		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, cmd->output);
		ft_putchar_fd('\n', cmd->output);
		free(pwd);
		exit(0);
	}
}
