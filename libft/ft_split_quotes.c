/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:35:39 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/05 18:45:43 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	int	count_splits(char *s, char c);
static int	sub_len(char *s, char c);
static void	ft_free(char **final, int offset);
static int	check_empty_string(char *s);

char	**ft_split_quotes(char const *s, char c)
{
	char	**final;
	int		splits;
	int		offset;
	int		substring;
	int		has_empty_string;

	offset = 0;
	has_empty_string = check_empty_string((char *)s);
	splits = count_splits((char *)s, c);
	final = malloc_matrix(splits, has_empty_string);
	while (offset < splits)
	{
		while (*(char *)s != '\0' && *(char *)s == c)
			s++;
		substring = sub_len((char *)s, c);
		final[offset] = ft_substr(s, 0, substring);
		if (!final[offset++])
		{
			ft_free(final, offset);
			return (NULL);
		}
		s += substring;
	}
	finish_final(final, splits, has_empty_string);
	return (final);
}

static int	check_empty_string(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (s[len - 1] == '|')
		return (1);
	return (0);
}

static void	ft_free(char **final, int offset)
{
	while (offset-- > 0)
		free(final[offset]);
	free(final);
}

static int	count_splits(char *str, char c)
{
	int	sublen;
	int	splitnum;

	splitnum = 0;
	while (*str != '\0')
	{
		while (*str && *str == c)
			str++;
		sublen = sub_len(str, c);
		str += sublen;
		if (sublen)
			splitnum++;
	}
	return (splitnum);
}

static int	sub_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39)
				i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		i++;
	}
	return (i);
}
