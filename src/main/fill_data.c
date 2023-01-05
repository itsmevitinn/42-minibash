/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 22:16:40 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/04 22:22:18 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	open_pipes(t_cmd_info *data);

void	fill_data(t_cmd_info *data)
{
	data->pipes = NULL;
	data->qty = cmds_quantity(data);
	if (data->qty >= 2)
	{
		open_pipes(data);
		precedence_analyzer(data);
	}
}

static void	open_pipes(t_cmd_info *data)
{
	int	pipes_qty;
	int	pipes_index;

	pipes_qty = data->qty - 1;
	pipes_index = 0;
	data->pipes = (int **)malloc(sizeof(int *) * pipes_qty);
	while (pipes_index < pipes_qty)
	{
		data->pipes[pipes_index] = (int *)malloc(sizeof(int) * 2);
		pipe(data->pipes[pipes_index++]);
	}
}
