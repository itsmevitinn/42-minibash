/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:02:16 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/01 18:01:24 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char **environ;

void	env(int	fd)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		ft_putstr_fd(environ[i], fd);
		write(fd, "\n", 1);
		i++;
	}
}
