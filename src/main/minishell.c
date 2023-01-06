/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/06 18:21:38 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			g_exit_status;

int	main(void)
{
	t_cmd_info	data;

	initialize_env(&data);
	setup_signals();
	while (42)
	{
		data.user_input = display_prompt();
		if (!data.user_input)
			handle_eof(&data.env_lst);
		else if (!whitespace_checker(data.user_input))
		{
			add_history(data.user_input);
			if (parse_input(&data))
			{
				run_commands(&data);
				get_exit_status(data.lst_cmd, data.qty);
				free_resources(&data);
			}
		}
		free(data.user_input);
	}
}
