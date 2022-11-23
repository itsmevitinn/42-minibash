/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:02:32 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/28 22:32:52 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	found_newline(t_list_gnl	*stash)
{
	int			i;
	t_list_gnl	*current;

	current = ft_lstlast_gnl(stash);
	i = 0;
	if (stash == NULL)
		return (0);
	while (current->string[i])
	{
		if (current->string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list_gnl	*ft_lstlast_gnl(t_list_gnl *stash)
{
	t_list_gnl	*current;

	current = stash;
	while (current)
	{
		if (!current->next)
			return (current);
		current = current->next;
	}
	return (current);
}

void	generate_line(t_list_gnl	*stash, char	**list)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->string[i])
		{
			if (stash->string[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*list = malloc(sizeof(char) * (len + 1));
	if (*list == NULL)
		return ;
}

void	free_stash(t_list_gnl *stash)
{
	t_list_gnl	*temp;
	t_list_gnl	*current;

	current = stash;
	while (current)
	{
		free(current->string);
		temp = current->next;
		free(current);
		current = temp;
	}
}
