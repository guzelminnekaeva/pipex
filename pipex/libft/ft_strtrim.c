/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:49 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/03/19 16:26:29 by zhizdahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	char	*m;
	int		start_len;
	int		end_len;
	int		len;
	int		i;

	i = 0;
	start_len = 0;
	end_len = 0;
	if (!s1 || !set)
		return (0);
	while (s1[i] && ft_strchr(set, s1[i++]))
		start_len++;
	len = ft_strlen(s1);
	i = len - 1;
	while (len > start_len && ft_strchr(set, s1[i--]))
		end_len++;
	m = (char *)malloc(len - end_len - start_len + 1);
	if (!m)
		return (0);
	m = ft_memcpy(m, &s1[start_len], len - end_len - start_len);
	m[len - end_len - start_len] = 0;
	free(s1);
	free(set);
	return (m);
}
