/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:57:32 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/09 11:57:35 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*token_quote(char *str, int *i)
{
	char	quote;
	int		start;

	quote = str[*i];
	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*token_dredir(char *str, int *i, int start)
{
	char	*token;

	if (start == *i)
	{
		token = (char *)malloc(sizeof(char) * 3);
		token[0] = str[*i];
		token[1] = str[(*i) + 1];
		token[2] = '\0';
		(*i) += 2;
		return (token);
	}
	*i += 2;
	return (ft_substr(str, start, *i - start));
}

char	*token_pipe(char *str, int *i, int start)
{
	char	*token;

	if (start == *i)
	{
		token = (char *)malloc(sizeof(char) * 2);
		token[0] = str[*i];
		token[1] = '\0';
		(*i)++;
		return (token);
	}
	(*i)++;
	return (ft_substr(str, start, *i - start));
}
