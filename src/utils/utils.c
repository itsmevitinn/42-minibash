/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:23:45 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/25 13:51:03 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_matrix(char **cmd_args)
{
	int i;

	i = 0;
	while(cmd_args[i])
		free(cmd_args[i++]);
	free(cmd_args);
}

void free_paths(char **paths, int i)
{
	// we iterate here because the current "i" was already freed by strjoin
	while (paths[i++])
		free(paths[i]);
	free(paths);
}

void print_matrix(char **cmd_args)
{
	int i;

	i = 0;
	while (cmd_args[i])
	{
		printf("[%i] %s ", i, cmd_args[i]);
		i++;
	}
	printf("\n");
}

void	close_all_pipes(t_cmd_info *data)
{
	int i;

	i = -1;
	while(++i < (data->qty - 1))
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
	}
}
