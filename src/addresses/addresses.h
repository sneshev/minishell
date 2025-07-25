#ifndef ADDRESSES_H
# define ADDRESSES_H

#include "../minishell.h"
#include "../structs.h"


// line
void set_g_line(char *new_line);
char *get_g_line();
void free_g_line();

// exit_code
void set_exit_code(int new_code);
int get_exit_code();

// tokens
void set_g_tokens(char **new_tokens);
char **get_g_tokens();
void free_g_tokens();

// list
void set_g_list(t_list *new_g_list);
t_list *get_g_list();
t_list **get_g_list_addr();
void free_g_list();

// env
void set_g_env(t_env *new_g_env);
t_env *get_g_env();
t_env **get_g_env_addr();
void free_g_env();

// environment
void set_g_environment(char **new_environment);
char **get_g_environment();
void free_g_environment();



#endif