/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:57:27 by gcorreia          #+#    #+#             */
/*   Updated: 2022/11/26 13:01:55 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_signal(int sig);

void	setup_signals(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sigemptyset(&(sa_sigint.sa_mask));
	sigemptyset(&(sa_sigquit.sa_mask));
	sa_sigint.sa_handler = &handle_signal;
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

static void	handle_signal(int sig)
{
	printf("\tctrl-C intercepted, press ctrl-Z instead\n");
	//end_current_process();
	//display_prompt();
	(void)sig;
}
