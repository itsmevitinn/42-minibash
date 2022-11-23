/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:08:57 by vsergio           #+#    #+#             */
/*   Updated: 2022/05/21 05:02:51 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str1;
	char	*total;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str1 = (char *)s1;
	i = 0;
	total = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (total == NULL)
		return (NULL);
	while (str1[i] != '\0')
	{
		total[i] = str1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		total[i++] = s2[j++];
	}
	total[i] = '\0';
	return (total);
}
