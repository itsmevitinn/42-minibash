/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:37:37 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/13 18:58:34 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*skip_quote(char *cmd);
static char	*handle_dollar_sign(char **cmd, char *i, t_var_lst *env_lst);

void	interpret_vars(char **cmd, t_var_lst *env_lst)
{
	char	*i;
	int		inside_double_quotes;

	inside_double_quotes = 0;
	i = *cmd;
	while (*i)
	{
		if (*i == '\"')
		{
			if (!inside_double_quotes)
				inside_double_quotes = 1;
			else
				inside_double_quotes = 0;
		}
		if (*i == '\'' && !inside_double_quotes)
			i = skip_quote(i);
		else if (*i == '$')
			i = handle_dollar_sign(cmd, i, env_lst);
		else
			i++;
	}
}

static char	*skip_quote(char *cmd)
{
	cmd++;
	while (*cmd != '\'' && *cmd)
		cmd++;
	if (*cmd == '\'')
		cmd++;
	return (cmd);
}

static char	*handle_dollar_sign(char **cmd, char *i, t_var_lst *env_lst)
{
	t_var_lst	*var;
	char		*exit_status;
	char		*var_name;

	if (i[1] == '?')
	{
		exit_status = ft_itoa(g_exit_status);
		i = insert_var(cmd, i, "?", exit_status);
		free(exit_status);
	}
	else
	{
		var_name = get_var_name(i);
		var = get_env(var_name, env_lst);
		if (!var || !var->content)
			remove_var(i, ft_strlen(var_name));
		else
			i = insert_var(cmd, i, var->name, var->content);
		free(var_name);
	}
	return (i);
}
