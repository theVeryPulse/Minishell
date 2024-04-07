#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int main(void)
{
	t_env	*env;
	char		*value;
	char		*name;

	env_build(&env);

	/* Search */

	name = "USER";
	value = env_get_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);
	free(value);

	name = "LANGUAGE";
	value = env_get_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);
	free(value);

	name = "HOME";
	value = env_get_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);
	free(value);


	/* Add , update and remove */

	name = "MYVAR";
	
	ft_printf("Add new var to env\n");
	env_update_name_value(&env, "MYVAR=Hello World");
	value = env_get_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);
	free(value);

	ft_printf("Change existing variable\n");
	env_update_name_value(&env, "USER=super");
	value = env_get_value_by_name(env, "USER");
	ft_printf("Search USER: >%s<\n", value);
	free(value);

	ft_printf("Remove new var from env\n");
	env_remove_by_name(&env, name);
	value = env_get_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);

	free(value);

	char **envp = env_build_envp(env);
	char **iter = envp;
	while (iter && *iter)
	{
		ft_printf("%s\n", *iter);
		free(*iter);
		iter++;
	}
	free(envp);

	env_free(&env);
	return 0;
}
