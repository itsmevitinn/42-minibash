/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:02:16 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/05 11:51:12 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char **environ;

void	initialize_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(environ[i])));
		i++;
	}
}
