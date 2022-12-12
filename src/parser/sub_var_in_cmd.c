/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_var_in_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:01:03 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/12 20:53:39 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*insert_var(char **cmd, char *i, char *name, char *content);
static void	remove_var(char *cmd);
static void	copy_rest(char	*dst, char *src);
static char	*insert_content(char *dst, char *content);
static char	*get_var_name(char *cmd);

char	*sub_var_in_cmd(char **cmd, char *i, t_var_lst *env_lst)
{
	t_var_lst	*var;
	char		*exit_status;
	char		*var_name;
	
	if (i[1] == '?')
	{
		exit_status = ft_itoa(g_exit_status);
		i = insert_var(cmd, i, "?", exit_status);
		free(exit_status);
	}
	else
	{
		var_name = get_var_name(i);
		var = get_env(var_name, env_lst);
		free(var_name);
		if (!var || !var->content)
			remove_var(i);
		else
			i = insert_var(cmd, i, var->name, var->content);
	}
	return (i);
}

static char	*get_var_name(char *cmd)
{
	char	*aux;
	char	*name;
	int	len;

	len = 0;
	aux = cmd;
	while (*aux && !ft_isspace(*aux))
	{
		len++;
		aux++;
	}
	name = malloc(len);
	if (!name)
		return (NULL);
	aux = name;
	cmd++;
	while (*cmd && !ft_isspace(*cmd))
		*aux++ = *cmd++;
	*aux = '\0';
	return (name);	
}

static void	remove_var(char *cmd)
{
	char	*aux;

	while (*cmd && !ft_isspace(*cmd))
	{
		aux = cmd;
		while (*aux)
		{
			*aux = aux[1];
			aux++;
		}
	}
}

static char	*insert_var(char **cmd, char *i, char *name, char *content)
{
	char	*new_cmd;
	char	*reference_point;
	int	len;
	int	offset;

	len = ft_strlen(*cmd) + ft_strlen(content) - ft_strlen(name) + 1;
	new_cmd = malloc(len);
	if (!new_cmd)
		return (NULL);
	offset = i - *cmd;
	ft_memcpy(new_cmd, *cmd, offset);
	reference_point = insert_content(new_cmd + offset, content);
	copy_rest(reference_point, *cmd + offset + ft_strlen(name) + 1);
	free(*cmd);
	*cmd = new_cmd;
	return (reference_point);
}

static char	*insert_content(char *dst, char *content)
{
	while (*content)
		*dst++ = *content++;
	return (dst);
}

static void	copy_rest(char	*dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}
