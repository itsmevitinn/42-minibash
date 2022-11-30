/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:57:27 by gcorreia          #+#    #+#             */
/*   Updated: 2022/11/30 01:26:05 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_signal(int sig);

void	setup_signals(void)
{
	struct sigaction	sa_signal;

	sigemptyset(&(sa_signal.sa_mask));
	sa_signal.sa_handler = &handle_signal;
	sigaction(SIGINT, &sa_signal, NULL);
	sigaction(SIGQUIT, &sa_signal, NULL);
}

static void	handle_signal(int sig)
{
	write(1, "\n", 1);
	if (g_running_process)
		g_running_process = 0;
	else //reinitialize readline manually bc user_inouyt is not returned
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	(void)sig;
}
