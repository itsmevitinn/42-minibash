/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:26 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/30 22:50:17 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	echo(char *string, int fd, char param)
{
	int i;

	i = 0;
	while(string[i])
		write(fd, &string[i++], 1);
	if (!param)
		write(fd, "\n", 1);
	// if (!ft_strncmp(command[1], "-n", 2))
	// 	write(fd, "\n", 1);
	return ;
}
