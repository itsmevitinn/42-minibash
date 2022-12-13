/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:37:37 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/12 20:48:25 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*skip_quote(char *cmd);

void	interpret_vars(char **cmd, t_var_lst *env_lst)
{
	char	*i;

	i = *cmd;
	while (*i)
	{
		if (*i == '\'' || *i == '\"')
			i = skip_quote(i);
		else if (*i == '$')
		{
			i = sub_var_in_cmd(cmd, i, env_lst);
		}
		else
			i++;
	}
}

static char	*skip_quote(char *cmd)
{
	char	quote;

	quote = *cmd;
	cmd++;
	while (*cmd != quote && *cmd)
		cmd++;
	if (*cmd == quote)
		cmd++;
	return (cmd);
}
