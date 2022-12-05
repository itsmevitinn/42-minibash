/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/05 11:50:17 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

t_list	*g_env;

int main(void)
{
	char		*user_input;

	setup_signals();
	initialize_env();
	while(42)
	{
		user_input = display_prompt();
		add_history(user_input);
		if (user_input && ft_strlen(user_input))
			parse_input(user_input);
		else if (!user_input)
		{
			rl_clear_history();
			ft_lstclear(&g_env, free);
			return (0);
		}
		free(user_input);
	}
}
