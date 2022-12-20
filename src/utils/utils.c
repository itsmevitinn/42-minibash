/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:23:45 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/20 11:38:35 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*skip_quote(char *cmd)
{
	char	quote;

	quote = *cmd++;
	while (*cmd != quote && *cmd)
		cmd++;
	if (*cmd == quote)
		cmd++;
	return (cmd);
}

void	remove_chunk(char *str, int len)
{
	char	*aux;

	while (len >=0 && *str)
	{
		aux = str;
		while (*aux)
		{
			*aux = aux[1];
			aux++;
		}
		len--;
	}
}

void	free_matrix(char **cmd_args)
{
	int i;

	i = 0;
	while(cmd_args[i])
		free(cmd_args[i++]);
	free(cmd_args);
}

void free_paths(char **paths, int i)
{
	// we iterate here because the current "i" was already freed by strjoin
	while (paths[i++])
		free(paths[i]);
	free(paths);
}

void print_matrix(char **cmd_args)
{
	int i;

	i = 0;
	while (cmd_args[i])
	{
		printf("[%i] %s ", i, cmd_args[i]);
		i++;
	}
	printf("\n");
}
