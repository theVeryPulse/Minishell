#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int main(void)
{
	t_env_stack	*env;
	char		*value;
	char		*name;

	build_env_stack(&env);

	/* Search */

	name = "USER";
	value = find_env_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);
	free(value);

	name = "LANGUAGE";
	value = find_env_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);
	free(value);

	name = "HOME";
	value = find_env_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);
	free(value);


	/* Add , update and remove */

	name = "MYVAR";
	
	ft_printf("Add new var to env\n");
	update_in_env(&env, "MYVAR=Hello World");
	value = find_env_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);
	free(value);

	ft_printf("Change existing variable\n");
	update_in_env(&env, "USER=super");
	value = find_env_value_by_name(env, "USER");
	ft_printf("Search USER: >%s<\n", value);
	free(value);

	ft_printf("Remove new var from env\n");
	remove_from_env_by_name(&env, name);
	value = find_env_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);

	free(value);

	char **envp = build_envp(env);
	char **iter = envp;
	while (iter && *iter)
	{
		ft_printf("%s\n", *iter);
		free(*iter);
		iter++;
	}
	free(envp);

	free_env_stack(&env);
	return 0;
}
