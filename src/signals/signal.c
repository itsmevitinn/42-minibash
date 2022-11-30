/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:57:27 by gcorreia          #+#    #+#             */
/*   Updated: 2022/11/30 13:01:01 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_signal(int sig);

void	setup_signals(void)
{
	struct sigaction	sa_sig_int;
	struct sigaction	sa_sig_quit;

	sigemptyset(&(sa_sig_int.sa_mask));
	sigemptyset(&(sa_sig_quit.sa_mask));
	sa_sig_int.sa_handler = &handle_signal;
	sa_sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sig_int, NULL);
	sigaction(SIGQUIT, &sa_sig_quit, NULL);
}

static void	handle_signal(int sig)
{
	write(1, "\n", 1);
	if (g_running_process)
		g_running_process = 0;
	else //reinitialize readline manually bc user_input is not returned
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	(void)sig;
}
