/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:01:03 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/21 16:48:13 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	copy_rest(char	*dst, char *src);
static char	*insert_content(char *dst, char *content);
static char	*create_sub(char *cmd, char *name, char *content);
static char	*copy_until_dollar_sign(char *sub, char *cmd, int offset);

char	*sub_arg(char **arg, char *index, char *name, char *content)
{
	char	*sub;
	int	offset;

	sub = create_sub(*arg, name, content);
	offset = index - *arg;
	index = copy_until_dollar_sign(sub, *arg, offset);
	index = insert_content(index, content);
	copy_rest(index, &(*arg)[offset + ft_strlen(name) + 1]);
	free(*arg);
	*arg = sub;
	return (index);
}

static char	*create_sub(char *cmd, char *name, char *content)
{
	int	len;
	char	*sub;

	len = ft_strlen(cmd) + ft_strlen(content) - ft_strlen(name) + 3;
	sub = malloc(len);
	if (!sub)
		return (NULL);
	return (sub);
}

static char	*copy_until_dollar_sign(char *sub, char *cmd, int offset)
{
	int	i;

	i = 0;
	while (i < offset)
	{
		sub[i] = cmd[i];
		i++;
	}
	sub[i++] = START;
	return (sub + i);
}

static char	*insert_content(char *dst, char *content)
{
	while (*content)
		*dst++ = *content++;
	*dst++ = END;
	return (dst);
}

static void	copy_rest(char	*dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}
