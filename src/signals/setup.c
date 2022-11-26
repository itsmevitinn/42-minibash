/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:57:27 by gcorreia          #+#    #+#             */
/*   Updated: 2022/11/26 12:37:48 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_signal(int sig);

void	setup_signals(struct sigaction *sa)
{
	sigemptyset(&(sa->sa_mask));
	sa->sa_handler = &handle_signal;
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		//end_current_process();
		//display_prompt();
	}
}
