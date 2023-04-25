#include "../include/minishell.h"

char    *get_next_token(char *str, int *i)
{
    char    *token;
    char    quote;
    int     j;
    int     start;

    start = *i;
    j = 0;
    token = malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (str[*i])
    {
        if (str[*i] == '\'' || str[*i] == '\"')
        {
            quote = str[*i];
            token[j] = str[*i];
            j++;
            (*i)++;
            while (str[*i] && str[*i] != quote)
            {
                token[j] = str[*i];
                j++;
                (*i)++;
            }
            if (str[*i] == quote)
            {
                token[j] = str[*i];
                j++;
                (*i)++;
            }
            token[j] = '\0';
            return (token);
        }
        else if (str[*i] == ' ' && start != *i)
        {
            token = ft_substr(str, start, *i - start);
            (*i)++;
            return (token);
        }
        else if (str[*i] == '|')
        {
            if (start == *i)
            {
                token[0] = str[*i];
                token[1] = '\0';
                (*i)++;
                return (token);
            }
            token = ft_substr(str, start, *i - start);
            (*i)++;
            return (token);
        }
        else if (str[*i] == '<' && str[*i + 1] == '<')
        {
            if (start == *i)
            {
                token[0] = str[*i];
                token[1] = str[(*i) + 1];
                token[2] = '\0';
                (*i) += 2;
                return (token);
            }
            token = ft_substr(str, start, *i - start);
            *i += 2;
            return (token);
        }
        else if (str[*i] == '>' && str[*i + 1] == '>')
        {
            if (start == *i)
            {
                token[0] = str[*i];
                token[1] = str[(*i) + 1];
                token[2] = '\0';
                (*i) += 2;
                return (token);
            }
            token = ft_substr(str, start, *i - start);
            *i += 2;
            return (token);
        }
        else if (str[*i] == '<')
        {
            if (start == *i)
            {
                token[0] = str[*i];
                token[1] = '\0';
                (*i)++;
                return (token);
            }
            token = ft_substr(str, start, *i - start);
            (*i)++;
            return (token);
        }
        else if (str[*i] == '>')
        {
            if (start == *i)
            {
                token[0] = str[*i];
                token[1] = '\0';
                (*i)++;
                return (token);
            }
            token = ft_substr(str, start, *i - start);
            (*i)++;
            return (token);
        }
        else
        {
            if (str[*i] != ' ')
            {
                token[j] = str[*i];
                j++;
            }
        }
        (*i)++;
    }
    token[ft_strlen(token) + 1] = '\0';
    return (token);
}

t_token_type    get_token_type(char *token, t_token_type token_type)
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

void    lexer(char *str, t_shell *p)
{
    char    *token;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while ((size_t)i < ft_strlen(str))
    {
        token = get_next_token(str, &i);
        j++;
        free(token);
    }
    p->n_tokens = j;
    p->tokens = malloc(sizeof(t_token *) * j);
    i = 0;
    j = 0;
    while ((size_t)i < ft_strlen(str))
    {
        p->tokens[j] = malloc(sizeof(t_token));
        p->tokens[j]->value = get_next_token(str, &i);
        if (j > 0)
            p->tokens[j]->token_type = get_token_type(p->tokens[j]->value, p->tokens[j - 1]->token_type);
        else
            p->tokens[j]->token_type = get_token_type(p->tokens[j]->value, ARG);
        if (p->tokens[j]->token_type == APPEND)
            p->append = 1;
        if (p->tokens[j]->token_type == INFILE)
            p->infile = ft_strdup(p->tokens[j]->value);
        if (p->tokens[j]->token_type == OUTFILE)
            p->outfile = ft_strdup(p->tokens[j]->value);
        printf("TOKEN: %s\n", p->tokens[j]->value);
        printf("TOKEN_TYPE: %u\n", p->tokens[j]->token_type);
        j++;
    }
}