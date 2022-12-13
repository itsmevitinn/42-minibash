/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_vars_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:01:03 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/13 18:31:15 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_var_name(char *cmd)
{
	char	*aux;
	char	*name;
	int	len;

	len = 0;
	aux = cmd;
	while (*aux && ft_isalpha(*aux))
	{
		len++;
		aux++;
	}
	name = malloc(len);
	if (!name)
		return (NULL);
	aux = name;
	cmd++;
	while (*cmd && ft_isalpha(*cmd))
		*aux++ = *cmd++;
	*aux = '\0';
	return (name);	
}

void	remove_var(char *cmd, int len)
{
	char	*aux;

	while (len >= 0)
	{
		aux = cmd;
		while (*aux)
		{
			*aux = aux[1];
			aux++;
		}
		len--;
	}
}

char	*insert_var(char **cmd, char *i, char *name, char *content)
{
	char	*new_cmd;
	char	*reference_point;
	int	len;
	int	offset;

	len = ft_strlen(*cmd) + ft_strlen(content) - ft_strlen(name) + 3;
	new_cmd = malloc(len);
	if (!new_cmd)
		return (NULL);
	offset = i - *cmd;
	ft_memcpy(new_cmd, *cmd, offset);
	new_cmd[offset] = START;
	reference_point = insert_content(new_cmd + offset + 1, content);
	copy_rest(reference_point, *cmd + offset + ft_strlen(name) + 1);
	free(*cmd);
	*cmd = new_cmd;
	return (reference_point);
}

char	*insert_content(char *dst, char *content)
{
	while (*content)
		*dst++ = *content++;
	*dst++ = END;
	return (dst);
}

void	copy_rest(char	*dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}
