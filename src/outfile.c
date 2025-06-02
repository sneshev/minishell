#include "minishell.h"
#include <fcntl.h>

// for >>
int append_to_file(char *input, char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        printf("error opening/creating outfile: %s\n", filename); // error handle correctly in future..
        return (fd);
    }
    write(fd, input, ft_strlen(input));
    close(fd);
    return (1);
}

// for >
int replace_file(char *input, char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        printf("error opening/creating outfile: %s\n", filename); // error handle correctly in future..
        return (fd);
    }
    write(fd, input, ft_strlen(input));
    close(fd);
    return (1);
}
