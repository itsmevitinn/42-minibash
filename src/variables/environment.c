/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:09:07 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/25 13:57:26 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	content_len(char *str);
static int	name_len(char *str);
static void	fill_array(char **array, char *str);
extern char	**environ;

void	initialize_env(t_var_lst **env_lst)
{
	int		i;
	char	**temp;

	i = 0;
	*env_lst = NULL;
	while (environ[i])
	{
		temp = split_env(environ[i]);
		ft_varadd_back(env_lst, ft_var_new(*temp, *(temp + 1)));
		free(temp);
		i++;
	}
}

char	**split_env(char *str)
{
	char	**array;

	if (!str || !name_len(str))
		return (NULL);
	array = malloc(sizeof(char *) * 2);
	if (!array)
		return (NULL);
	*array = malloc(name_len(str) + 1);
	*(array + 1) = malloc (content_len(str) + 1);
	if (!*array || !*(array + 1))
	{
		free(*array);
		free(*(array + 1));
		return (NULL);
	}
	fill_array(array, str);
	return (array);
}

static int	name_len(char *str)
{
	int	len;

	len = 0;
	while (*str && *str != '=')
	{
		len++;
		str++;
	}
	return (len);
}

static int	content_len(char *str)
{
	int	len;

	len = 0;
	while (*str && *str != '=')
		str++;
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}

static void	fill_array(char **array, char *str)
{
	int	i;

	i = 0;
	while (*str != '=' && *str)
		array[0][i++] = *str++;
	array[0][i] = '\0';
	if (*str)
		str++;
	i = 0;
	while (*str)
		array[1][i++] = *str++;
	array[1][i] = '\0';
}
