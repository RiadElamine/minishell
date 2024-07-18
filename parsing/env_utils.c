/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:17:21 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/17 23:31:09 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *new_env(char *key, char *value) 
{
    t_env *new;

    new = malloc(sizeof(t_env));
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}
void env_add_back(t_env **env_lst, t_env *new) 
{
    t_env *tmp;

    if (!*env_lst)
        *env_lst = new;
    else
    {
        tmp = *env_lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}
void  intit_env_list(t_env **env_lst, char **env) 
{
    int i;
    int j;
    char *key;
    char *value;

    if (!env)
        return;
    i = 0;
    while (env[i])
    {
        j = 0;
        while (env[i] && env[i][j] != '=' && env[i][j] != '\0')
            j++;
        key = ft_substr(env[i], 0, j);
        value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j - 1);
        if (!*env_lst)
            *env_lst = new_env(key, value);
        else
         env_add_back(env_lst, new_env(key, value));
        i++;
    }
}
char *my_getenv(char *key, t_env *env_lst) 
{
    while (env_lst)
    {
        if (!ft_strcmp(key, env_lst->key))
            return env_lst->value;
        env_lst = env_lst->next;
    }
	if (ft_strcmp(key, "PATH") == 0)
		return ("/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin");
    return NULL;
}
int check_ex(char *str, int end) 
{
    int i;
    int flag;
    char quote;
    
    i = 0;
    flag = 0;
    while (str[i] && i <= end)
    {
        if (str[i] == '\"')
        {
            quote = str[i++];
            while (str[i] && str[i] != quote && i < end)
                i++;
            i++;
        }
        else if (str[i] == '\'')
        {
            quote = str[i++];
            while (str[i] && str[i] != quote && i < end)
                i++;
            if (str[i] != quote)
                flag = 1;
            i++;
        }
        else
        {
            i++;
        }
    }
    return flag;
}
