#include "minishell.h"
#include <fcntl.h>


// void append_to_file(char *input, char *filename)
// {

// }

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int replace_file(char *input, char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        printf("error opening/creating outfile\n"); // error handle correctly in future..
        return (fd);
    }
    write(fd, input, ft_strlen(input));
    return (1);
}



// int main()
// {
//     char *str = "haha";
//     printf("%d", replace_file(str, "outfile.c"));
// }
