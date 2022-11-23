/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:45:26 by vsergio           #+#    #+#             */
/*   Updated: 2022/05/17 16:42:05 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*sorc;
	char		*lastd;
	const char	*lasts;

	dest = dst;
	sorc = src;
	if (dst == NULL && src == NULL)
		return (0);
	if (dest < sorc)
	{
		while (len-- > 0)
		{
			*dest++ = *sorc++;
		}
	}
	else
	{
		lastd = dest + (len - 1);
		lasts = sorc + (len - 1);
		while (len-- > 0)
			*lastd-- = *lasts--;
	}
	return (dst);
}
