/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:32:46 by barbizu-          #+#    #+#             */
/*   Updated: 2023/04/27 12:32:50 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*get_next_token(char *str, int *i)
{
	int		j;
	int		start;

	start = *i;
	while (str[*i] && str[*i] == ' ')
	{
		(*i)++;
		start++;
	}
	j = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			return (token_quote(str, i));
		else if (str[*i] == ' ' && start != *i && (*i)++)
			return (ft_substr(str, start, *i - start));
		else if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>'
				&& str[*i + 1] == '>'))
			return (token_dredir(str, i, start));
		else if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
			return (token_pipe(str, i, start));
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

t_token_type	get_token_type(char *token, t_token_type token_type)
{
	if (!ft_strncmp(token, "|", ft_strlen(token)))
		return (PIPE);
	else if (!ft_strncmp(token, ">", ft_strlen(token)))
		return (OUTPUT);
	else if (!ft_strncmp(token, "<", ft_strlen(token)))
		return (INPUT);
	else if (!ft_strncmp(token, ">>", ft_strlen(token)))
		return (APPEND);
	else if (!ft_strncmp(token, "<<", ft_strlen(token)))
		return (HERE_DOC);
	else if (token_type == OUTPUT || token_type == APPEND)
		return (OUTFILE);
	else if (token_type == INPUT)
		return (INFILE);
	else if (token_type == CMD)
		return (ARG);
	else
		return (CMD);
}

int	count_tokens(char *str)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	while ((size_t)i < ft_strlen(str))
	{
		token = get_next_token(str, &i);
		j++;
		free(token);
	}
	return (j);
}

void	lexer(char *str, t_shell *p)
{
	int		i;
	int		j;

	i = 0;
	p->n_tokens = count_tokens(str);
	p->tokens = malloc(sizeof(t_token *) * p->n_tokens);
	j = 0;
	while ((size_t)i < ft_strlen(str))
	{
		p->tokens[j] = malloc(sizeof(t_token));
		p->tokens[j]->value = get_next_token(str, &i);
		if (j > 0)
			p->tokens[j]->token_type = get_token_type(p->tokens[j]->value,
					p->tokens[j - 1]->token_type);
		else
			p->tokens[j]->token_type = get_token_type(p->tokens[j]->value, ARG);
		if (p->tokens[j]->token_type == APPEND)
			p->append = 1;
		j++;
	}
}
