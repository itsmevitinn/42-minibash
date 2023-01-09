/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:23:45 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/09 17:30:40 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_matrix(char **cmd_args)
{
	int	i;

	i = -1;
	while (cmd_args[++i])
		printf("[%i] %s ", i, cmd_args[i]);
	printf("\n");
}

void	close_all_pipes(t_cmd_info *data)
{
	int	i;

	i = -1;
	while (++i < (data->qty - 1))
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
	}
}

int	is_builtin(char *cmd_name)
{
	if ((!ft_strncmp(cmd_name, "echo", 5)) || (!ft_strncmp(cmd_name, "/bin/echo", 10)))
		return (1);
	else if ((!ft_strncmp(cmd_name, "cd", 3)) || (!ft_strncmp(cmd_name, "/usr/bin/cd", 12)))
		return (1);
	else if ((!ft_strncmp(cmd_name, "pwd", 4)) || (!ft_strncmp(cmd_name, "/bin/pwd", 9)))
		return (1);
	else if (!ft_strncmp(cmd_name, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd_name, "unset", 6))
		return (1);
	else if ((!ft_strncmp(cmd_name, "env", 4)) || (!ft_strncmp(cmd_name, "/usr/bin/env", 13)))
		return (1);
	else if (!ft_strncmp(cmd_name, "exit", 5))
		return (1);
	else
		return (0);
}

void	print_invalid_identifier(char *value, char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	count_args(char **args)
{
	int	counter;

	counter = 0;
	while (*args)
	{
		counter++;
		args++;
	}
	return (counter);
}
