/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:06:22 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/08 23:25:50 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_warning(char *delimiter);

int	get_heredoc_input(t_cmd_lst *cmd, int *here_pipe)
{
	char	*line;

	while (42)
	{
		line = readline(">");
		if (g_exit_status == 130)
			return (0);
		if (!line)
		{
			print_warning(cmd->delimiter);
			break ;
		}
		else if (!ft_strncmp(line, cmd->delimiter, ft_strlen(line) + 1))
			break ;
		ft_putstr_fd(line, here_pipe[1]);
		ft_putchar_fd('\n', here_pipe[1]);
		free(line);
	}
	free(line);
	close(here_pipe[1]);
	return (1);
}

static void	print_warning(char *delimiter)
{
	ft_putstr_fd("bash: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
