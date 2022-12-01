/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:26 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/01 18:26:49 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	echo(char **splitted_cmd, int fd)
{
	int word_index;
	int trailing_newline;

	trailing_newline = 1;
	if (!ft_strncmp(splitted_cmd[1], "-n", 2) && ft_strlen(splitted_cmd[1]) == 2)
	{
		word_index = 2;
		trailing_newline = 0;
	}
	else
		word_index = 1;
	while(splitted_cmd[word_index])
	{
		ft_putstr_fd(splitted_cmd[word_index], fd);
		if (splitted_cmd[word_index + 1])
			write(fd, " ", 1);
		word_index++;
	}
	if (trailing_newline)
		write(fd, "\n", 1);
	// free_matrix(splitted_cmd);
	return ;
}
