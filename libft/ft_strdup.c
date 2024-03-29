/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:10:29 by matesant          #+#    #+#             */
/*   Updated: 2024/03/19 19:22:20 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	int		i;
	char	*nstr;

	i = 0;
	len = ft_strlen(str) + 1;
	if (!str)
		return (NULL);
	nstr = (char *)ft_calloc(len, sizeof(char));
	if (!nstr)
		return (NULL);
	while (str[i] != '\0')
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
