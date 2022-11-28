/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:57:27 by gcorreia          #+#    #+#             */
/*   Updated: 2022/11/28 11:19:39 by vsergio          ###   ########.fr       */
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
	if (sig == SIGINT)
		printf("\tctrl-C intercepted, press ctrl-Z instead\n");
	else if (sig == SIGQUIT)
		printf("\tctrl-\\ does nothing\n");
	//end_current_process();
	//display_prompt();
	(void)sig;
}
