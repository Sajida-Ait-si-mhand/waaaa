
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
//--->Sajida: new header Declarations
# include <string.h>
#include <signal.h>
# include "libft/libft.h"

//--->Sajida: 
typedef struct s_env
{
	char			*value;
	char			*test;
	char			*key;
	char			equal;
	struct s_env 	*next;
}	t_env;

typedef struct s_senv
{
	char *svalue;
	char *skey;
	char sequal;
	struct s_senv *next;
} t_senv;
/// Sajida

typedef enum e_token_type
{
	WORD,
	PIPE, 
	HER_DOC,
	OUT_REDIR,
	APPEND,
	INP_REDIR
}					token_type;

typedef struct s_token
{
	char			*data;
	token_type		data_type;
	struct s_token	*next_token;
	struct s_token	*prev_token;
}	t_token;

typedef struct s_redir
{
	token_type		red_type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_node
{
	char				**cmd;
	t_redir				*redir;
	struct s_node	*next_node;
	struct s_node	*prev_node;
}	t_node;

typedef struct s_minishell
{
	t_env *env_gr;
	char	**envirement;
	char	*command;
	t_token	*tokens;
	t_node	*nodes;
}					t_minishell;

extern t_minishell	minishell;

t_token *ft_tokenize(t_minishell g_minishell);
int		 is_space(char *line);
void	ft_lstadd_back(t_token **lst, t_token *new);
char	*get_word(char *str, int i);
void	ft_put_token(char **line, enum e_token_type token_t, t_token **tokens_list);
int		ft_put_word_token(char **line, enum e_token_type token_t, t_token **tokens_list);
size_t	ft_strlen(const char *str); 	
t_token	*rm_qotes(t_token *tokens);
t_token	*parsing(t_minishell g_minishell);
t_token	*rmp_dollar(t_token *tokens);
int		count_pipe(t_token *tokens);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
int		is_not_alpanum(char c);
 //Sajida
int ft_strcmp(char *s1, char *s2);
void ft_sigint(int x);
void ft_echo(t_minishell cmd);
int ft_cd(t_minishell data);
void ft_pwd(t_minishell cmd);
void check_command(t_minishell data);
void ft_env(t_minishell data);
void ft_exit(t_minishell data);
void ft_unset(t_env *env_list,t_minishell data);
void ft_backup(t_env **head, t_minishell data);
void ft_env_unset(t_minishell data);
void	ft_putendl_fd(char *s, int fd);
void ft_export (t_minishell data);
void ft_env_export_once(t_minishell data, int active);
void sort_env(t_senv *node);
void ft_add_to_export_arg(t_minishell data);
char *ft_strndup(char *str, int j);
// void ft_add_to_export_aloha(t_minishell data);
// minitest in the end of prog
// cat lksdj < dalkf;> sdkfj<<sdf >>dslfj |ksdjj|osdfij|sdkfj+
# endif
