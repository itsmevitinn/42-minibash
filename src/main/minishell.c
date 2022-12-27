/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/26 22:21:27 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int whitespace_checker(char *input);

int g_exit_status;

int main(void)
{
	t_cmd_info data;
	t_var_lst *env_lst;
	char *user_input;

	initialize_env(&env_lst);
	setup_signals();
	while (42)
	{
		user_input = display_prompt();
		if (!user_input)
		{
			rl_clear_history();
			ft_varclear(&env_lst);
			return (0);
		}
		else if (!whitespace_checker(user_input))
		{
			add_history(user_input);
			data.lst_cmd = parse_input(user_input, env_lst);
			fill_data(&data);
			exec_cmds(&data, &env_lst);
			ft_cmdclear(&data.lst_cmd);
			free_pipes(&data);
		}
		free(user_input);
	}
}

static int whitespace_checker(char *input)
{
	int i;

	i = 0;
	while (input[i])
		if (!ft_isspace(input[i++]))
			return (0);
	return (1);
}
