#include "../free_and_null.h"
#include "libft.h"
#include <unistd.h>

void	search_exec_and_replace_arg(char **arg, char **paths)
{
	char	*exe;
	char	**path;

	path = paths;
	while (path && *path)
	{
		exe = ft_format_string("%s/%s", *path, *arg);
		if (access(exe, F_OK) == 0)
		{
			free_and_null((void **)arg);
			*arg = exe;
			break ;
		}
		free_and_null((void **)&exe);
		path++;
	}
}
