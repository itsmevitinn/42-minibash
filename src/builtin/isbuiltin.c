/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/29 09:49:03 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	pwd(int fd);
static void	echo(char *string, int fd, char param);
void	isbuiltin(char *command)
{
	if (!ft_strncmp(command, "echo", 4))
		echo(command, 1, 'n');
	else if (!ft_strncmp(command, "cd", 2))
		pwd(1);
	else if (!ft_strncmp(command, "pwd", 3))
		pwd(1);
	else if (!ft_strncmp(command, "export", 6))
		pwd(1);
	else if (!ft_strncmp(command, "unset", 5))
		pwd(1);
	else if (!ft_strncmp(command, "env", 3))
		pwd(1);
	else if (!ft_strncmp(command, "exit", 3))
		pwd(1);
}

static void	pwd(int fd)
{
	char *pwd;
	int i;

	i = 0;
	pwd = getcwd(NULL, 0);
	while(pwd[i])
		write(fd, &pwd[i++], 1);
	write(fd, "\n", 1);
	free(pwd);
}

static void	echo(char *string, int fd, char param)
{
	int i;

	i = 0;
	while(string[i])
		write(fd, &string[i++], 1);
	if (!param)
		write(fd, "\n", 1);
	return ;
}
