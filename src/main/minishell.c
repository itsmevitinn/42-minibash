/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/30 15:52:44 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	g_running_process;

int main(void)
{
	char		*user_input;

	setup_signals();
	while(42)
	{
		user_input = display_prompt();
		add_history(user_input);
		if (user_input && ft_strlen(user_input))
			parse_cmd(user_input);
		else if (!user_input)
		{
			rl_clear_history();
			return (0);
		}
		free(user_input);
	}
	rl_clear_history();
}
