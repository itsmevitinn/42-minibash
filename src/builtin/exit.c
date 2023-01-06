/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:11:22 by Vitor             #+#    #+#             */
/*   Updated: 2023/01/06 18:47:56 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	numeric_argument(char *status);
static void	exec_exit(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);
static int	too_many_arguments(char **args, t_cmd_info *data);
static void	print_error(char *str);

void	ft_exit(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	if (data->qty > 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
			exec_exit(cmd, data, env_lst);
	}
	else
		exec_exit(cmd, data, env_lst);
}

static void	exec_exit(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	int	new_status;

	if (!too_many_arguments(cmd->args, data))
		return ;
	if (!cmd->args[1])
	{
		if (data->qty == 1)
			free_all(data, &env_lst, 1);
		exit(EXIT_SUCCESS);
	}
	else if (cmd->args[1] && numeric_argument(cmd->args[1]))
	{
		new_status = ft_atoi(cmd->args[1]);
		if (data->qty == 1)
			free_all(data, &data->env_lst, 1);
		exit(new_status);
	}
	else
	{
		print_error(cmd->args[1]);
		if (data->qty == 1)
			free_all(data, &data->env_lst, 0);
		exit(255);
	}
}

static int	too_many_arguments(char **args, t_cmd_info *data)
{
	int	args_size;

	args_size = count_args(args);
	if (args_size >= 3)
	{
		if (data->qty == 1)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		if (data->qty > 1)
			exit(1);
		g_exit_status = 1;
		return (0);
	}
	return (1);
}

static int	numeric_argument(char *status)
{
	while (*status)
	{
		if (*status >= '0' && *status <= '9')
			status++;
		else
			return (0);
	}
	return (1);
}

static void	print_error(char *str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}
