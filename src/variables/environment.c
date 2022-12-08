/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:20:58 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/08 14:01:33 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern char **environ;

#include "../../include/minishell.h"

void	initialize_env(t_list **env_lst)
{
	int	i;

	i = 0;
	*env_lst = NULL;
	while (environ[i])
	{
		ft_lstadd_back(env_lst, ft_lstnew(ft_strdup(environ[i])));
		i++;
	}
}
