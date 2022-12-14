/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:37:37 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/14 10:34:53 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	alter_state(int *state);
static char	*handle_dollar_sign(char **cmd, char *i, t_var_lst *env_lst);
static char	*get_var_name(char *cmd);

void	interpret_vars(char **cmd, t_var_lst *env_lst)
{
	char	*i;
	int		inside_double_quotes;

	inside_double_quotes = 0;
	i = *cmd;
	while (*i)
	{
		if (*i == '\"')
			alter_state(&inside_double_quotes);
		if (*i == '\'' && !inside_double_quotes)
			i = skip_quote(i);
		else if (*i == '$')
			i = handle_dollar_sign(cmd, i, env_lst);
		else
			i++;
	}
}

static void	alter_state(int *state)
{
	if (*state)
		*state = 0;
	else
		*state = 1;
}

static char	*handle_dollar_sign(char **cmd, char *i, t_var_lst *env_lst)
{
	t_var_lst	*var;
	char		*exit_status;
	char		*var_name;

	if (i[1] == '?')
	{
		exit_status = ft_itoa(g_exit_status);
		i = sub_cmd(cmd, i, "?", exit_status);
		free(exit_status);
	}
	else
	{
		var_name = get_var_name(i);
		var = get_env(var_name, env_lst);
		if (!var || !var->content)
			remove_chunk(i, ft_strlen(var_name));
		else
			i = sub_cmd(cmd, i, var->name, var->content);
		free(var_name);
	}
	return (i);
}

static char	*get_var_name(char *cmd)
{
	char	*aux;
	char	*name;

	aux = cmd;
	while (*aux && ft_isalpha(*aux))
		aux++;
	name = malloc(aux - cmd);
	if (!name)
		return (NULL);
	aux = name;
	cmd++;
	while (*cmd && ft_isalpha(*cmd))
		*aux++ = *cmd++;
	*aux = '\0';
	return (name);
}
