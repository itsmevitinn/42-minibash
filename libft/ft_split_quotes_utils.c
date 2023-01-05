/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:14:41 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/05 18:31:40 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**malloc_matrix(int splits, int has_empty_string)
{
	char	**temp;

	if (has_empty_string)
		temp = malloc(sizeof(char *) * (splits + 2));
	else
		temp = malloc(sizeof(char *) * (splits + 1));
	return (temp);
}

void	finish_final(char **final, int splits, int has_empty_string)
{
	if (has_empty_string)
	{
		final[splits++] = ft_strdup("");
		final[splits] = NULL;
	}
	else
		final[splits] = NULL;
}
