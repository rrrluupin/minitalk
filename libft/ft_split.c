/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlupin <rlupin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:37:53 by rlupin            #+#    #+#             */
/*   Updated: 2021/11/15 15:26:43 by rlupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	size_t	count;
	int		is_delim;

	count = 0;
	is_delim = 0;
	while (*s)
	{
		if (*s != c)
			is_delim = 1;
		else if (*s == c && is_delim == 1)
		{
			count++;
			is_delim = 0;
		}
		s++;
	}
	if (is_delim == 1)
		count++;
	return (count);
}

static int	char_count(const char *src, char c)
{
	size_t	word_length;

	word_length = 0;
	while (*src != c && *src != 0)
	{
		word_length++;
		src++;
	}
	return (word_length);
}

static char	**freeall(char **strings, int word)
{
	while (word)
	{
		free(strings[word]);
		word--;
	}
	free(strings);
	return (NULL);
}

static char	**add_words(char const *s, char c, char **strings, size_t word)
{
	size_t	current_c;

	while (*s)
	{
		if (*s != c)
		{
			strings[word] = malloc(sizeof(char) * (char_count(s, c) + 1));
			if (!strings[word])
			{
				freeall(strings, word);
				return (NULL);
			}
			current_c = 0;
			while (*s != c && *s != 0)
				strings[word][current_c++] = *s++;
			strings[word++][current_c] = 0;
			s--;
		}
		s++;
	}
	strings[word] = 0;
	return (strings);
}

char	**ft_split(char const *src, char c)
{
	char	**strings;
	size_t	word;

	if (!src)
		return (NULL);
	strings = malloc(sizeof(char *) * (word_count(src, c) + 1));
	if (!strings)
		return (NULL);
	word = 0;
	return (add_words(src, c, strings, word));
}
