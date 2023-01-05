/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 13:50:01 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/05 18:08:41 by gcorreia         ###   ########.fr       */
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

int	whitespace_checker(char *input)
{
	while (*input)
		if (!ft_isspace(*input++))
			return (0);
	return (1);
}

void	print_syntax_error(t_cmd_lst *cmd, char *str)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	if (*str)
	{
		ft_putchar_fd(*str, 2);
		if (*str == str[1])
			ft_putchar_fd(*str, 2);
	}
	else if (cmd->next)
		ft_putchar_fd('|', 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("\'\n", 2);
}
