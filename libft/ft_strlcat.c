/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:01:31 by vsergio           #+#    #+#             */
/*   Updated: 2022/05/15 19:03:32 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			srclen;
	size_t			dstlen;
	unsigned int	i_dst;
	int				i_src;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i_dst = ft_strlen(dst);
	i_src = 0;
	if (dstsize < 1)
		return (srclen + dstsize);
	while (src[i_src] != '\0' && i_dst < dstsize - 1)
	{
		dst[i_dst] = src[i_src];
		i_dst++;
		i_src++;
	}
	dst[i_dst] = '\0';
	if (dstsize < dstlen)
		return (srclen + dstsize);
	else
		return (dstlen + srclen);
}
