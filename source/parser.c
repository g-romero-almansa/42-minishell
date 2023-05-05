/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:32:58 by barbizu-          #+#    #+#             */
/*   Updated: 2023/04/27 12:33:00 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	join_tokens(t_shell *p, int start, int end, int n)
{
	char	*join;
	char	*temp;

	join = ft_strdup(p->tokens[start]->value);
	start++;
	while (start < end)
	{
		temp = ft_strjoin(join, " ");
		free(join);
		join = ft_strjoin(temp, p->tokens[start]->value);
		free(temp);
		start++;
	}
	p->pipes[n]->str = ft_strdup(join);
	free(join);
}

void	init_parser(t_shell *p)
{
	int	i;
	int	start;
	int	pipes;

	i = 0;
	start = 0;
	pipes = 0;
	p->pipes = malloc(sizeof(t_pipes *) * (p->n_pipes + 2));
	while (i <= p->n_pipes)
	{
		p->pipes[i] = malloc(sizeof(t_pipes));
		i++;
	}
	p->pipes[i] = NULL;
	i = 0;
	while (i < p->n_tokens)
	{
		if (p->tokens[i]->token_type == PIPE)
		{
			join_tokens(p, start, i, pipes);
			start = i + 1;
			pipes++;
		}
		i++;
	}
	join_tokens(p, start, i, pipes);
}

void	parser(t_shell *p)
{
	int		i;
	char	*temp;
	char	*sub;

	i = 0;
	while (i < p->n_tokens)
	{
		if (!ft_strncmp(p->tokens[i]->value, "|",
				ft_strlen(p->tokens[i]->value)))
			p->n_pipes++;
		if (ft_strchr(p->tokens[i]->value, '\'') != NULL)
		{
			sub = ft_strchr(p->tokens[i]->value, '\'');
			p->interp = 0;
			temp = ft_substr(sub, 1,
					ft_strlen(p->tokens[i]->value) - 2);
			free(p->tokens[i]->value);
			p->tokens[i]->value = ft_strdup(temp);
			free(temp);
		}
		else if (ft_strchr(p->tokens[i]->value, '\"') != NULL)
		{
			sub = ft_strchr(p->tokens[i]->value, '\"');
			temp = ft_substr(sub, 1,
					ft_strlen(p->tokens[i]->value) - 2);
			free(p->tokens[i]->value);
			p->tokens[i]->value = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
	init_parser(p);
}
