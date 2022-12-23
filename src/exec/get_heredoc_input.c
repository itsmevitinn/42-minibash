/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:06:22 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/23 14:43:13 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_warning(char *delimiter);

void	get_heredoc_input(t_cmd_lst *cmd)
{
	char	*line;

	cmd->input = open("/tmp/.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (42)
	{
		line = readline(">");
		if (!line)
		{
			print_warning(cmd->delimiter);
			break ;
		}
		else if (!ft_strncmp(line, cmd->delimiter, ft_strlen(line) + 1))
			break ;
		ft_putstr_fd(line, cmd->input);
		ft_putchar_fd('\n', cmd->input);
		free(line);
	}
	free(line);
	close(cmd->input);
	cmd->input = open("/tmp/.txt", O_RDONLY, 0666);
}

static void	print_warning(char *delimiter)
{
	ft_putstr_fd("bash: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
