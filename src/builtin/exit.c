/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:11:22 by Vitor             #+#    #+#             */
/*   Updated: 2023/01/06 17:30:02 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	numeric_argument(char *status);
static void	exec_exit(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);
static int	too_many_arguments(char **args, t_cmd_info *data);
static int	count_args(char **args);

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
		{
			ft_putstr_fd("exit\n", 2);
			free(data->user_input);
			rl_clear_history();
			ft_varclear(&env_lst);
			ft_cmdclear(&data->lst_cmd);
		}
		exit(EXIT_SUCCESS);
	}
	else if (cmd->args[1] && numeric_argument(cmd->args[1]))
	{
		new_status = ft_atoi(cmd->args[1]);
		if (data->qty == 1)
		{
			ft_putstr_fd("exit\n", 2);
			free(data->user_input);
			rl_clear_history();
			ft_varclear(&env_lst);
			ft_cmdclear(&data->lst_cmd);
		}
		exit(new_status);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		if (data->qty == 1)
		{
			free(data->user_input);
			rl_clear_history();
			ft_varclear(&env_lst);
			ft_cmdclear(&data->lst_cmd);
		}
		exit(255);
	}
}

static int	count_args(char **args)
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
