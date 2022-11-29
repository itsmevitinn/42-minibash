/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/29 14:51:31 by gcorreia         ###   ########.fr       */
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
		add_history("teste");
		if (user_input && ft_strlen(user_input))
			parse_cmd(user_input);
		free(user_input);
	}
}
