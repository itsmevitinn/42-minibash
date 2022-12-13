/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:09:07 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/09 21:55:31 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	content_len(char *str);
static int	name_len(char *str);
static void	fill_array(char **array, char *str);

char **split_env(char *str)
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
