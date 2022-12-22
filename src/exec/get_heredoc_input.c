/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:06:22 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/22 15:41:41 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	rl_catch_signals;

void	get_heredoc_input(t_cmd_lst *cmd)
{
	char	*line;
	char	*temp[] = {NULL};

	printf("delimiter = %s\n", cmd->delimiter);
	cmd->input = open("/tmp/temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	rl_catch_signals = 0;
	while (42)
	{
		line = readline(">");
		printf("read line = -%s-\n", line);
		if (!line || !ft_strncmp(line, cmd->delimiter, ft_strlen(line) + 1))
			break ;
		ft_putstr_fd(line, cmd->input);
		ft_putchar_fd('\n', cmd->input); 
	}
	rl_catch_signals = 1;
	close(cmd->input);
	cmd->input = open("/tmp/temp.txt", O_RDONLY, 0666);
	printf("cat with input from heredoc:\n");
	if (!fork())
	{
		dup2(cmd->input, 0);
		execve("/bin/cat", temp, NULL);
	}
	wait(NULL);
}
