/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:00 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/22 11:51:03 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	pwd(t_cmd_lst *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, cmd->output);
	ft_putchar_fd('\n', cmd->output);
	free(pwd);
	g_exit_status = 0;
}
