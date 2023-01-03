/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:08:30 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/03 17:17:53 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_content(char *name, t_var_lst *env)
{
	int	name_len;

	name_len = ft_strlen(name);
	while (env && ft_strncmp(name, env->name, name_len + 1))
		env = env->next;
	if (env)
		return (env->content);
	return (NULL);
}

char	**list_to_matrix(t_var_lst *env_lst)
{
	t_var_lst	*temp;
	char		*all_contents;
	char		**matrix;

	temp = env_lst;
	all_contents = temp->name;
	all_contents = ft_strjoin(all_contents, "=", 0);
	all_contents = ft_strjoin(all_contents, temp->content, 'f');
	all_contents = ft_strjoin(all_contents, "\n", 'f');
	temp = temp->next;
	while (temp)
	{
		all_contents = ft_strjoin(all_contents, temp->name, 'f');
		all_contents = ft_strjoin(all_contents, "=", 'f');
		all_contents = ft_strjoin(all_contents, temp->content, 'f');
		all_contents = ft_strjoin(all_contents, "\n", 'f');
		temp = temp->next;
	}
	matrix = ft_split(all_contents, '\n');
	free(all_contents);
	return (matrix);
}
