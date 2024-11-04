#include "minishell.h"

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

void ft_env_export_once(t_minishell data, int active)
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
    
    if (active == 1)
        sort_env(head);
    
    t_senv *current = head;
    while (current)
    {
        if (active == 1)
            printf("declare -x %s=%s\n", current->skey, current->svalue);
        current = current->next;
    }
}
void ft_add_to_export_arg(t_minishell data) 
{

    int i ;

    i = 0;
    t_env *expo = malloc(sizeof(t_env));

    if (!expo) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (data.tokens->next_token->data[i] >= '0' && data.tokens->next_token->data[i] <= '9') {
        printf("bash: export: `%s': not a valid identifier\n", data.tokens->next_token->data);
        free(expo);
        return;
    }

    char *splitVar = ft_strchr(data.tokens->next_token->data, '=');
    if (splitVar != NULL) {
        expo->key = ft_strndup(data.tokens->next_token->data, splitVar - data.tokens->next_token->data);
        expo->value = ft_strndup(splitVar + 1, strlen(splitVar + 1));
    }
    i = 0;
    while (data.envirement[i] != NULL) {
        i++;
    }

    // Allocate memory for the new environment variable string
    char *new_env_str = malloc(ft_strlen(expo->key) + 1 + ft_strlen(expo->value) + 1);
    if (!new_env_str) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Concatenate the key, equal sign, and value into the new string
    printf("%s=%s", expo->key, expo->value);

    // Assign the new string to the next available position in the array
    data.envirement[i] = new_env_str;
    data.envirement[i + 1] = NULL; // Null-terminate the array

    printf("Exporting: %s=%s\n", expo->key, expo->value);
}

void ft_export(t_minishell data)
{
    int active = 1;

    if (data.tokens != NULL && data.tokens->next_token == NULL)
    {
        ft_env_export_once(data, active);
    }
    else
    {
        active = 0;
        ft_add_to_export_arg(data);
        ft_env_export_once(data, active);
    }
}
