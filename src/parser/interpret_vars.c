/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:37:37 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/09 22:38:47 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	alter_state(int *state);
static char	*handle_dollar_sign(char **cmd, char *i, t_var_lst *env_lst);
static char	*get_var_name(char *cmd);

void	interpret_vars(char **args, t_var_lst *env_lst)
{
	char	*line;
	int		inside_double_quotes;

	inside_double_quotes = 0;
	while (*args)
	{
		line = *args;
		while (*line)
		{
			if (*line == '\"')
				alter_state(&inside_double_quotes);
			if (*line == '\'' && !inside_double_quotes)
				line = skip_quote(line);
			else if (*line == '$' && !ft_isspace(line[1]) && line[1])
				line = handle_dollar_sign(args, line, env_lst);
			else
				line++;
		}
		args++;
	}
}

static void	alter_state(int *state)
{
	if (*state)
		*state = 0;
	else
		*state = 1;
}

static char	*handle_dollar_sign(char **arg, char *i, t_var_lst *env_lst)
{
	t_var_lst	*var;
	char		*exit_status;
	char		*var_name;

	if (i[1] == '?')
	{
		exit_status = ft_itoa(g_exit_status);
		i = sub_arg(arg, i, "?", exit_status);
		free(exit_status);
	}
	else
	{
		var_name = get_var_name(i);
		var = get_env(var_name, env_lst);
		if (!var || !var->content)
			remove_chunk(i, ft_strlen(var_name));
		else
			i = sub_arg(arg, i, var->name, var->content);
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
