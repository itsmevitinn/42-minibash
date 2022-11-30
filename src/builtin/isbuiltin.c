/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/30 01:22:58 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	pwd(int fd);
static void	echo(char *string, int fd, char param);
void	run_builtin(char **command)
{
	if (!ft_strncmp(command[0], "echo", 4))
		echo(command[1], 1, 'n');
	else if (!ft_strncmp(command[0], "cd", 2))
		cd(command[1]);
	else if (!ft_strncmp(command[0], "pwd", 3))
		pwd(1);
	else if (!ft_strncmp(command[0], "export", 6))
		pwd(1);
	else if (!ft_strncmp(command[0], "unset", 5))
		pwd(1);
	else if (!ft_strncmp(command[0], "env", 3))
		pwd(1);
	else if (!ft_strncmp(command[0], "exit", 3))
		pwd(1);
}

int	isbuiltin(char *command)
{
	if (!ft_strncmp(command, "echo", 4))
		return(1);
	else if (!ft_strncmp(command, "cd", 2))
		return(1);
	else if (!ft_strncmp(command, "pwd", 3))
		return(1);
	else if (!ft_strncmp(command, "export", 6))
		return(1);
	else if (!ft_strncmp(command, "unset", 5))
		return(1);
	else if (!ft_strncmp(command, "env", 3))
		return(1);
	else if (!ft_strncmp(command, "exit", 3))
		return(1);
	return (0);
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
	// if (!ft_strncmp(command[1], "-n", 2))
	// 	write(fd, "\n", 1);
	return ;
}
