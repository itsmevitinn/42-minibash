/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:12:19 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/14 13:33:44 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	remove_quotes(char *cmd);
static void	remove_ctrl_chars(char *cmd);
static char	*clean_quote(char *cmd);
static char	*skip_variable(char *cmd);

void	cleanup(char *cmd)
{
	remove_quotes(cmd);
	remove_ctrl_chars(cmd);
}

static void	remove_quotes(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == START)
			cmd = skip_variable(cmd);
		else if (*cmd == '\'' || *cmd == '\"')
			cmd = clean_quote(cmd);
		else
			cmd++;
	}
}

static char	*skip_variable(char *cmd)
{
	while (*cmd && *cmd != END)
		cmd++;
	if (*cmd == END)
		cmd++;
	return (cmd);
}

static char	*clean_quote(char *cmd)
{
	char	quote;

	quote = *cmd;
	remove_chunk(cmd, 0);
	while (*cmd && *cmd != quote)
		cmd++;
	if (*cmd == quote)
		remove_chunk(cmd, 0);
	return (cmd);
}

static void	remove_ctrl_chars(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == START || *cmd == END)
			remove_chunk(cmd, 0);
		else
			cmd++;
	}
}
