/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:48:37 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/20 11:53:47 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_error_prone_char(char c);
static void	print_error(char *str);
static char	*check_char(char *cmd, int *error);

int	check_syntax(char *cmd_line)
{
	int	error;

	error = 0;
	while (*cmd_line && !error)
	{
		if (*cmd_line == '\"' || *cmd_line == '\'')
			cmd_line = skip_quote(cmd_line);
		else if (is_error_prone_char(*cmd_line))
			cmd_line = check_char(cmd_line, &error);
		else
			cmd_line++;
	}
	if (error)
		return (0);
	else
		return (1);
}

static int	is_error_prone_char(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '\0')
		return (1);
	return (0);
}

static char	*check_char(char *cmd, int *error)
{
	if (*cmd == cmd[1])
		cmd++;
	cmd++;
	while (ft_isspace(*cmd))
		cmd++;
	if (is_error_prone_char(*cmd))
	{
		print_error(cmd);
		*error = 1;
	}
	return (cmd);
}

static void	print_error(char *str)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	if (*str)
	{
		ft_putchar_fd(*str, 2);
		if (*str == str[1] && *str != '|')
			ft_putchar_fd(*str, 2);
	}
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("\'\n", 2);
}
