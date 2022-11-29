/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/28 23:44:09 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	pwd(void);
static void	echo(char *string);
void	isbuiltin(char *command)
{
	if (!ft_strncmp(command, "echo", 4))
		echo(command);
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
	int i;

	i = 0;
	pwd = getcwd(NULL, 0);
	while(pwd[i])
		write(1, &pwd[i++], 1);
	write(1, "\n", 1);
	free(pwd);
}

static void	echo(char *string)
{
	int i;

	i = 0;
	while(string[i])
		write(1, &string[i++], 1);
	write(1, "\n", 1);
	return ;
}
