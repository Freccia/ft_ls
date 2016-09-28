/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:47:04 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:45:22 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Allocates (with malloc(3)) and returns an array of “fresh”
**     strings (all ending with ’\0’, including the array itself) obtained
**     by spliting s using the character c as a delimiter.
**     If the allocation fails the function returns NULL.
**     Example:
**     ft_strsplit("*hello*fellow***students*", ’*’)
**     returns the array: ["hello", "fellow", "students"].
*/

static size_t	ft_split_count_words(char const *s, char c)
{
	size_t	nw;

	nw = 0;
	while (*s)
	{
		while (*s == c && *s)
			++s;
		if (*s != c && *s)
		{
			++nw;
			while (*s != c && *s)
				++s;
		}
	}
	return (nw);
}

static size_t	ft_strlen_ch(char const *s, char c)
{
	size_t		len;

	len = 0;
	while (*s != c && *s)
	{
		++len;
		++s;
	}
	return (len);
}

static char		*cp_word(char const *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	if ((str = ft_strnew(ft_strlen_ch(s, c))) == NULL)
		return (NULL);
	while (s[i] != c && s[i])
	{
		str[i] = s[i];
		++i;
	}
	str[i] = '\0';
	return (str);
}

char			**ft_split_return(char const *s, char c, int nw)
{
	char	**tab;
	int		j;

	tab = NULL;
	j = 0;
	if ((tab = (char **)malloc(sizeof(char*) * nw + 1)) == NULL)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			++s;
		if (*s != c && *s)
		{
			tab[j] = NULL;
			tab[j] = cp_word(s, c);
			s += ft_strlen_ch(s, c);
			++j;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	nw;

	if (s)
	{
		nw = ft_split_count_words(s, c);
		return (ft_split_return(s, c, nw));
	}
	return (NULL);
}
