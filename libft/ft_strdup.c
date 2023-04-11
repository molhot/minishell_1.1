/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:48:30 by kazuki            #+#    #+#             */
/*   Updated: 2023/03/24 09:33:53 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(char const *src)
{
	char	*new;
	size_t	len;
	size_t	i;

	if (src == NULL)
		return (ft_strdup(""));
	len = ft_strlen(src);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
