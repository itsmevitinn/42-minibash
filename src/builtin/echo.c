/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:26 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/30 23:37:50 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	echo(char **splitted_cmd, int fd)
{
	char *content;
	int i;

	content = splitted_cmd[1];
	i = 0;
	while(content[i])
		write(fd, &content[i++], 1);
	if (!ft_strncmp(splitted_cmd[1], "-n", 2))
		write(fd, "\n", 1);
	// free_matrix(splitted_cmd);
	return ;
}
