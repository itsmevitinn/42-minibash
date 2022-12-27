/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:57:27 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/27 01:48:38 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_signal(int sig);

void	setup_signals(void)
{
	struct sigaction	sa_sig_int;
	struct sigaction	sa_sig_quit;

	memset(&sa_sig_int, 0, sizeof(sa_sig_int));
	memset(&sa_sig_quit, 0, sizeof(sa_sig_quit));
	sa_sig_int.sa_handler = &handle_signal;
	sa_sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sig_int, NULL);
	sigaction(SIGQUIT, &sa_sig_quit, NULL);
}

static void	handle_signal(int sig)
{
	write(1, "\n", 1);
	if (RL_ISSTATE(RL_STATE_READCMD))
	{
		g_exit_status = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	(void)sig;
}

void	restore_sigint(void)
{
	struct sigaction	sa_sig;

	memset(&sa_sig, 0, sizeof(sa_sig));
	sa_sig.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_sig, NULL);
}
