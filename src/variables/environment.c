/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:20:58 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/07 23:21:43 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern char **environ;

#include "../../include/minishell.h"

void	initialize_env(t_list *env_lst)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		ft_lstadd_back(&env_lst, ft_lstnew(ft_strdup(environ[i])));
		i++;
	}
}