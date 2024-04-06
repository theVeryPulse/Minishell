#include "environment_variables.h"
#include "libft.h"
#include <unistd.h>

int main(void)
{
	t_env_stack	*env;
	char			*value;
	char			*name;

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


	/* Add and Remove */

	name = "MYVAR";
	
	ft_printf("Add new var to env\n");
	add_to_env(&env, "MYVAR=Hello World");
	value = find_env_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);

	ft_printf("Remove new var from env\n");
	remove_from_env_by_name(&env, name);
	value = find_env_value_by_name(env, name);
	ft_printf("Search %s: >%s<\n", name, value);

	free(value);


	free_env_stack(&env);
	return 0;
}
