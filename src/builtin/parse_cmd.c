/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:37:37 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/09 21:59:15 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	parse_name(char *cmd);
static int	validate_name(char *cmd);
static int	check_quote(char **cmd);

int	parse_cmd(char *cmd)
{
	if (!parse_name(cmd))
		return (0);
//	parse_content(cmd);
	return (1);
}

static int	parse_name(char *cmd)
{
	if (!validate_name(cmd))
		return (0);
	return (1);
}

static int	validate_name(char *cmd)
{
	while (*cmd && *cmd != '=')
	{
		if (*cmd == '\'' || *cmd == '\"')
		{
			cmd++;
			if (!check_quote(&cmd))
				return (0);
		}
		else
			cmd++;
	}
	return (1);
}

static int	check_quote(char **cmd)
{
	if (**cmd == '\'')
	{
		while (**cmd && **cmd != '\'' && **cmd != '=')
		{
			if (**cmd == '\"')
				return (0);
			(*cmd)++;
		}
	}
	else if (**cmd == '\"')
	{
		while (**cmd && **cmd != '\"' && **cmd != '=')
		{
			if (**cmd == '\'')
				return (0);
			(*cmd)++;
		}
	}
	if (**cmd == '\'' || **cmd == '\"')
		(*cmd)++;	
	return (1);
}
