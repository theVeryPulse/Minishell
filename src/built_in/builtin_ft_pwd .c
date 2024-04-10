#include <unistd.h>
#include <stdio.h>

#define PATH_MAX (4096)

int ft_pwd(void) {
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("%s\n", cwd);
	} else {
		perror("No such file or directory");
		return (1);
	}
	return (0);
}
