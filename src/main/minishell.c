/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/05 11:55:59 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static int	whitespace_checker(char *input);
t_list	*g_env;

int main(void)
{
	char		*user_input;

	setup_signals();
	initialize_env();
	while(42)
	{
		user_input = display_prompt();
		if (!user_input)
		{
			//when ctrl + d is pressed
			rl_clear_history();
			ft_lstclear(&g_env, free);
			return (0);
		}
		else if (!whitespace_checker(user_input))
		{
			add_history(user_input);
			parse_input(user_input);
		}
		free(user_input);
	}
}

static int	whitespace_checker(char *input)
{
	int i;

	i = 0;
	while(input[i])
		if (!ft_isspace(input[i++]))
			return (0);
	return (1);
}
