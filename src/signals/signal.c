/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:57:27 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/22 15:45:57 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static void	handle_signal(int sig);

extern char	*rl_prompt;
extern char	*rl_line_buffer;
extern int	rl_done;
extern int	rl_eof_found;

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
	if(!ft_strncmp(rl_prompt, ">", 2))
	{
		rl_done = 1;
		rl_eof_found = 1;
	}
	if (RL_ISSTATE(RL_STATE_READCMD))
	{
		g_exit_status = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		g_exit_status = 130;
	(void)sig;
}
