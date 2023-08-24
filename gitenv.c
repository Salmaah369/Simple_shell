#include "shell.h"

/**
 * get_environment - returns a copy of the environment string array
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Pointer to the environment string array
 */
char **get_environment(info_t *info)
{
	if (!info->environment || info->environment_changed)
	{
		info->environment = list_to_strings(info->env_list);
		info->environment_changed = 0;
	}

	return (info->environment);
}

/**
 * unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the environment variable to unset
 * Return: 1 on success, 0 otherwise
 */
int unset_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env_list;
	size_t i = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info->environment_changed = delete_node_at_index(&(info->env_list), i);
			i = 0;
			node = info->env_list;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->environment_changed);
}

/**
 * set_environment_variable - Initialize a new environment variable,
 *                            or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the environment variable
 * @value: the value of the environment variable
 * Return: Always 0
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buf = malloc(strlen(variable) + strlen(value) + 2);
	if (!buf)
		return (1);
	strcpy(buf, variable);
	strcat(buf, "=");
	strcat(buf, value);
	node = info->env_list;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env_list), buf, 0);
	free(buf);
	info->environment_changed = 1;
	return (0);
}
