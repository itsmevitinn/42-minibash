/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:23:45 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/23 14:57:52 by gcorreia         ###   ########.fr       */
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

	while (len >= 0 && *str)
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
