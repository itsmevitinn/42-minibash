/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/28 12:15:29 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	pwd(void);
void	isbuiltin(char *command)
{
	if (!ft_strncmp(command, "echo", 4))
		pwd();
	else if (!ft_strncmp(command, "cd", 2))
		pwd();
	else if (!ft_strncmp(command, "pwd", 3))
		pwd();
	else if (!ft_strncmp(command, "export", 6))
		pwd();
	else if (!ft_strncmp(command, "unset", 5))
		pwd();
	else if (!ft_strncmp(command, "env", 3))
		pwd();
	else if (!ft_strncmp(command, "exit", 3))
		pwd();
}

static void	pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}
