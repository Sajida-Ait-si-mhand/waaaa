#include "minishell.h"

// void ft_env_export_once(t_minishell data)
// {
//     int i = 0;
//     t_env *head = NULL;
//     t_env *last_node = NULL;
//     while(data.envirement[i] != NULL)
//     {
//         t_env *cmd_env = (t_env *)malloc(sizeof(t_env));
//         if (!cmd_env)
//             exit(1);
//         char *equal_env = strchr(data.envirement[i], '=');
//         if (equal_env != NULL)
//         {
//             cmd_env->key = strndup(data.envirement[i], equal_env - data.envirement[i]);
//             cmd_env->value = strndup(equal_env + 1, ft_strlen(data.envirement[i] + 1 ));
// 			cmd_env->equal = '=';
// 			cmd_env->next = NULL;
//         }
//         if( last_node == NULL)
//             head = cmd_env;
//         else
//             last_node->next = cmd_env;
//         last_node = cmd_env;
//         printf("declare -x %s %c %s\n",cmd_env->key, cmd_env->equal, cmd_env->value);
//         i++;
//     }
// }
 
// void ft_add_to_export_arg(t_minishell data)
// {
//     int i = 0;
//     t_env *head = NULL;
//     t_env *last_node = NULL;
//     while(data.envirement[i] != NULL)
//     {
//         t_env *cmd_env = (t_env *)malloc(sizeof(t_env));
//         if (!cmd_env)
//             exit(1);
//         char *equal_env = strchr(data.envirement[i], '=');
//         if (equal_env != NULL)
//         {
//             cmd_env->key = strndup(data.envirement[i], equal_env - data.envirement[i]);
//             cmd_env->value = strndup(equal_env + 1, ft_strlen(data.envirement[i] + 1 ));
// 			cmd_env->equal = '=';
// 			cmd_env->next = NULL;
//         }
//         if( last_node == NULL)
//             head = cmd_env;
//         else
//             last_node->next = cmd_env;
//         last_node = cmd_env;
//         i++;
//     }
// }

void sort_env(t_senv *node)
{
   if (node == NULL || node->next == NULL)
    return ;
    t_senv *next_node = node->next;

    while (next_node)
    {
        if (ft_strcmp(node->skey, next_node->skey) > 0)
        {
            char  *tmp_key = node->skey;
            node->skey =  next_node->skey;
            next_node->skey = tmp_key;

            char  *tmp_value = node->svalue;
            node->svalue =  next_node->svalue;
            next_node->svalue = tmp_value;
        }
        next_node = next_node->next;
    }
    sort_env(node->next);
}

void ft_env_export_once(t_minishell data)
{
    t_senv *head = NULL;
    t_senv *last_node = NULL;

     int i = 0;

    while (data.envirement[i] != NULL)
    {
        t_senv *cmd_env = (t_senv *)malloc(sizeof(t_senv));
        if (!cmd_env)
            exit(1);

        char *equal_env = strchr(data.envirement[i], '=');
        if (equal_env != NULL)
        {
            cmd_env->skey = strndup(data.envirement[i], equal_env - data.envirement[i]);
            cmd_env->svalue = strndup(equal_env + 1, strlen(data.envirement[i] + 1));
            cmd_env->sequal = '=';
            cmd_env->next = NULL;
        }

        if (last_node == NULL)
            head = cmd_env;
        else
            last_node->next = cmd_env;

        last_node = cmd_env;
        i++;
    }
    t_senv *current = head;
    while (current) {
        sort_env(head); 
        current = current->next;
    }

    current = head;
    while (current) {
        printf("declare -x %s %c %s\n", current->skey, current->sequal, current->svalue);
        current = current->next;
    }
}


//pupose : to slot between the key and the value and print them as well 

void ft_add_to_export_arg(t_minishell data)
{
    // if (data.tokens->data || data.tokens->next_token->data || data.tokens->next_token->next_token->data)
    //     return ;
    t_env *expo = malloc(sizeof(t_env ));
    if (!expo)
        return ;
    // data.tokens->data = data.tokens->next_token->data;
    // Handling the numbers error:
    int i = 0;
    while (data.tokens->next_token->data[i] >= '0' && data.tokens->next_token->data[i] <= '9')
    {
        printf("bash: export: `%s': not a valid identifier\n", data.tokens->next_token->data);
        i++;
    } 
    //copy the new args and add them (in the process)
    int j = 0; // testeur
    while ((ft_strchr(data.tokens->next_token->data, '=') && data.tokens->next_token->data && data.tokens->next_token))
    {
        printf(" \033[0;31m data.tokens->data[i] :%s \033[0m\n", data.tokens->next_token->data);
        char *word =  ft_strchr(data.tokens->next_token->data, '=');
        printf( "\033[36m word: %s \033[0m\n", word);
        expo->equal = '=';
        if (word != NULL) 
        {
            expo->value = strndup(data.tokens->next_token->data, word - data.tokens->next_token->data);
            expo->key = strndup(  word +1, ft_strlen(data.tokens->next_token->data + 1) );
            printf("\033[36m expo->value: %s \033[0m\n", expo->value);
            printf("\033[36m expo->key: %s \033[0m\n", expo->key);
        }
        // printf("word ---->%s\n", word);
        // printf("\033[32m data.tokens->data -->%s \033[0m\n", data.tokens->data);
        // printf("\033[32m export->value -->%s \033[0m\n", expo->value);

        data.tokens = data.tokens->next_token;
        if (! data.tokens->next_token)
            return ;
        // j++; // testeur
    }



    // Move to the next token
    data.tokens = data.tokens->next_token;
    j++;
}

void ft_export (t_minishell data)
{
    if (data.tokens != NULL && data.tokens->next_token == NULL)
       ft_env_export_once(data);
    else
    {
        printf("\033[0;31m Ila dis kra \033[0m\n");
        ft_add_to_export_arg(data);
    }
}
