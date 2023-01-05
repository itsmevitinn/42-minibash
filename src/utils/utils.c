/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:23:45 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/05 11:03:30 by vsergio          ###   ########.fr       */
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
	if (!ft_strncmp(cmd_name, "echo", 4))
		return (1);
	else if (!ft_strncmp(cmd_name, "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd_name, "pwd", 3))
		return (1);
	else if (!ft_strncmp(cmd_name, "export", 6))
		return (1);
	else if (!ft_strncmp(cmd_name, "unset", 5))
		return (1);
	else if (!ft_strncmp(cmd_name, "env", 3))
		return (1);
	else if (!ft_strncmp(cmd_name, "exit", 4))
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
