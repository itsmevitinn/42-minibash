/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:08:30 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/25 14:09:27 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *get_content(char *name, t_var_lst *env)
{
	int name_len;

	name_len = ft_strlen(name);
	while (env && ft_strncmp(name, env->name, name_len + 1))
		env = env->next;
	if (env)
		return (env->content);
	return (NULL);
}
