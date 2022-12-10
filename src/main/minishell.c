/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/09 21:31:16 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	whitespace_checker(char *input);
int	exit_status;

int main(void)
{
	t_var_lst		*env_lst;
	char		*user_input;

	initialize_env(&env_lst);
//	setup_signals();
//	while(42)
//	{
//		printf("last exit status: %i\n", exit_status);
//		user_input = display_prompt();
//		if (!user_input)
//		{
//			//when ctrl + d is pressed
//			rl_clear_history();
//			ft_varclear(&env_lst);
//			return (0);
//		}
//		else if (!whitespace_checker(user_input))
//		{
//			add_history(user_input);
//			parse_input(user_input, env_lst);
//		}
//		free(user_input);
//	}
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
