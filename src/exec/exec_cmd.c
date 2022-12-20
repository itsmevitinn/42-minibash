/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/20 19:08:00 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	print_pipes(t_cmd_info *data);
void	exec_cmds(t_cmd_info *data, t_var_lst **env_lst)
{
	int pid;
	int status;

	while(data->lst_cmd)
	{
		pid = fork();
		if (!pid)
		{
			printf("fd input from %s: %i\n", data->lst_cmd->args[0], data->lst_cmd->input);
			printf("fd output from %s: %i\n", data->lst_cmd->args[0], data->lst_cmd->output);
			if (data->lst_cmd->output != 1)
			{
				printf("%s duplicou o fd %i para o stdout\n", data->lst_cmd->args[0], data->lst_cmd->output);
				printf("closing fd from %s: %i\n",data->lst_cmd->args[0], data->pipes[0][0]);
				printf("closing fd from %s: %i\n",data->lst_cmd->args[0], data->pipes[0][1]);
				close(data->pipes[0][0]);
				dup2(data->lst_cmd->output, 1);
				close(data->pipes[0][1]);
			}
			if (data->lst_cmd->input != 0)
			{
				printf("%s duplicou o fd %i para o stdin\n", data->lst_cmd->args[0], data->lst_cmd->input);
				printf("closing fd from %s: %i\n",data->lst_cmd->args[0], data->pipes[0][1]);
				printf("closing fd from %s: %i\n",data->lst_cmd->args[0], data->pipes[0][0]);
				close(data->pipes[0][1]);
				dup2(data->lst_cmd->input, 0);
				close(data->pipes[0][0]);
			}
			if (!exec_builtin_cmd(data->lst_cmd, env_lst))
				exec_bin_cmd(data->lst_cmd);
		}
		ft_putstr_fd("waiting pid...\n", 2);
		waitpid(pid, &status, 0);
		printf("%s finished\n", data->lst_cmd->args[0]);
		g_exit_status = WEXITSTATUS(status);
		// free(cmd->args);
		data->lst_cmd = data->lst_cmd->next;
	}
}

static void	print_pipes(t_cmd_info *data)
{
	int i;

	i = 0;
	while(data->pipes[i])
	{
		printf("pipe leitura eh o fd: %i\n", data->pipes[i][0]);
		printf("pipe: escrita eh o fd: %i\n", data->pipes[i++][1]);
	}
}
