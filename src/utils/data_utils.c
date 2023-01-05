/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 21:51:07 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/04 22:14:46 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmds_quantity(t_cmd_info *data)
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
	return (qty);
}
