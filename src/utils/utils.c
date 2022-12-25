/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:23:45 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/25 17:22:43 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_matrix(char **cmd_args)
{
	int i;

	i = -1;
	while (cmd_args[++i])
		printf("[%i] %s ", i, cmd_args[i]);
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