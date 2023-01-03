/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:45:19 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/02 21:18:11 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_matrix(char **cmd_args)
{
	int	i;

	i = -1;
	while (cmd_args[++i])
		free(cmd_args[i]);
	free(cmd_args);
}

void	free_pipes(t_cmd_info *data)
{
	int	i;

	i = -1;
	while (++i < (data->qty - 1))
		free(data->pipes[i]);
	free(data->pipes);
}
