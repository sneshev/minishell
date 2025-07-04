#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>

// execution
char	*get_cmd(char *cmd);

// files
int		replace_file(char *input, char *filename);
int		append_to_file(char *input, char *filename);


#endif