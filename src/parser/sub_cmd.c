/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:01:03 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/14 10:42:57 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	copy_rest(char	*dst, char *src);
static char	*insert_content(char *dst, char *content);
static char	*create_sub(char *cmd, char *name, char *content);
static char	*copy_until_dollar_sign(char *sub, char *cmd, int offset);

char	*sub_cmd(char **cmd, char *i, char *name, char *content)
{
	char	*sub;
	int	offset;

	sub = create_sub(*cmd, name, content);
	offset = i - *cmd;
	i = copy_until_dollar_sign(sub, *cmd, offset);
	i = insert_content(i, content);
	copy_rest(i, &(*cmd)[offset + ft_strlen(name) + 1]);
	free(*cmd);
	*cmd = sub;
	return (i);
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
