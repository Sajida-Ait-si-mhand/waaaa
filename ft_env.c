
#include "minishell.h"
//hnaya dert wahed l copy l env bax n9der n9arenha m3a l key w nchof xno radi i5sni n delete

void ft_backup(t_env **head, t_minishell data)
{
    t_env *tmp = *head;

    t_env *prev = NULL;

    if (data.tokens == NULL || data.tokens->next_token == NULL)
        return ;

    while (tmp)
    {
        tmp->test = data.tokens->next_token->data;

        printf("\033[0;31m %s \033[0m", tmp->test);
        printf("------>%s\n", tmp->key);
        printf("------>%s\n", tmp->value);

        // I need to add first the riginal->test than remove it 
        if (tmp->test != NULL && !ft_strcmp(tmp->key, tmp->test))
        {
            free(tmp->key);
            free(tmp->value);

            printf("\033[36m   /\\  \033[0m \n");  // First line with forward slash and backslash
            printf("\033[36m  /  \\ \033[0m \n");  // Second line
            printf("\033[36m /    \\ \033[0m \n");  // Third line
            printf("\033[36m|   *   | \033[0m \n");  // star line
            printf("\033[36m \\    /\033[0m \n");  // Fourth line with backslash and forward slash
            printf("\033[36m  \\  / \033[0m \n");  // Fifth line
            printf("\033[36m   \\/  \033[0m \n");

            if (prev == NULL)
            {
                *head = tmp->next;
            }
            else 
            {
                // Skip over the current node
                prev->next = tmp->next;
            }

            // free(tmp);  // Free the current node
            // break;  
            free(tmp);
            tmp = (prev == NULL) ? *head : prev->next;  // Adjust the current pointer
            continue; 
        }
        prev = tmp ;
        tmp = tmp->next;
    }
}

// I called the function normaly of env.
void ft_env(t_minishell data)
{
    int i = 0;
    t_env *head = NULL;
    t_env *last_node = NULL;
    
    while(data.envirement[i] != NULL)
    {
        t_env *cmd_env = (t_env *)malloc(sizeof(t_env));
        if (!cmd_env)
            exit(1);
        char *equal_env = strchr(data.envirement[i], '=');
        if (equal_env != NULL)
        {
            cmd_env->key = strndup(data.envirement[i], equal_env - data.envirement[i]);
            cmd_env->value = strndup(equal_env + 1, ft_strlen(data.envirement[i] + 1 ));
			cmd_env->equal = '=';
			cmd_env->next = NULL;
            printf("%s", cmd_env->key);
            printf("%c", cmd_env->equal);
            printf("%s\n", cmd_env->value);
        }
        if( last_node == NULL)
            head = cmd_env;
        else
            last_node->next = cmd_env;
        last_node = cmd_env;
        i++;
    }
}

// void ft_backup(t_env **head, t_minishell data)
// {
//     t_env *current = *head;
//     t_env *prev = NULL;

//     if (data.tokens == NULL || data.tokens->next_token == NULL)
//         return;

//     while (current != NULL)
//     {
//         current->test = data.tokens->next_token->data;  // Token containing the key to unset

//         // If the key matches the token, unset it
//         if (current->test != NULL && !ft_strcmp(current->key, current->test))
//         {
//             printf("\033[36m Unsetting key: %s \033[0m\n", current->key);
//             // printf("%s<------------", current->key);
//             free(current->key);
//             free(current->value);

//             // Unlink the node from the list
//             if (prev == NULL) 
//             {
//                 // If current node is the head
//                 *head = current->next;
//             } 
//             else 
//             {
//                 // Skip the current node
//                 prev->next = current->next;
//             }

//             free(current);  // Free the node memory
//             current = (prev == NULL) ? *head : prev->next;  // Move the current pointer forward
//             continue;  // Skip to the next iteration after deletion
//         }

//         // If the key wasn't unset, proceed to the next node
//         prev = current;
//         current = current->next;
//     printf("%s<------------", current->key);
//     }
//     printf("outloop %s s<------------", current->key);
// }

// void ft_env(t_minishell data)
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
//             printf("%s", cmd_env->key);
//             printf("%c", cmd_env->equal);
//             printf("%s\n", cmd_env->value);
//         }
//         if( last_node == NULL)
//             head = cmd_env;
//         else
//             last_node->next = cmd_env;
//         last_node = cmd_env;
//         i++;
//     }
// }