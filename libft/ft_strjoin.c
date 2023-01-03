/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:08:57 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/03 16:03:51 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_strings(char *s1, char *s2, int frees);
char	*ft_strjoin(char *s1, char *s2, int frees)
{
	char	*full_string;
	int		index_full;
	int		index_s2;

	if (!s1 || !s2)
		return (NULL);
	index_full = 0;
	index_s2 = 0;
	full_string = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (full_string == NULL)
		return (NULL);
	while (s1[index_full] != '\0')
	{
		full_string[index_full] = s1[index_full];
		index_full++;
	}
	while (s2[index_s2] != '\0')
	{
		full_string[index_full++] = s2[index_s2++];
	}
	full_string[index_full] = '\0';
	if (frees)
		free_strings(s1, s2, frees);
	return (full_string);
}

void	free_strings(char *s1, char *s2, int frees)
{
	if (frees == 'f')
	{
		if (s1)
			free(s1);
	}
	else if (frees == 's')
	{
		if (s2)
			free(s2);
	}
	else if (frees == 'a')
	{
		if (s1 && s2)
		{
			free(s1);
			free(s2);
		}
	}
}
