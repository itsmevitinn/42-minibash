/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 21:51:07 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/02 21:18:20 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmds_quantity(t_cmd_info *data)
{
	t_cmd_lst	*temp;
	int			qty;

	temp = data->lst_cmd;
	qty = 0;
	while (temp)
	{
		qty++;
		temp = temp->next;
	}
	data->qty = qty;
}
