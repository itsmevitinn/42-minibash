/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:57:27 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/08 23:25:53 by vsergio          ###   ########.fr       */
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
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
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
