#include "main.h"
void add_environment_variable(char *name, char *value) 
{
    char *envs;
    env_capacity = ENV_CAPACITY;
    if (env_count >= env_capacity)
    {
        /* Increase the capacity if needed */
            perror("No space in array");
            exit(EXIT_FAILURE);
    }
    envs = (char *)malloc(my_strlen(name)+ my_strlen(value) + 2);
    if (!envs)
    {
	    perror("Malloc");
            exit(EXIT_FAILURE);
    }

    my_strcpy(envs, name);
    my_strcat(envs, "=");
    my_strcat(envs, value);


    __envp[env_count] = my_strdup(envs);
    env_vars[env_count].name = my_strdup(name);
    env_vars[env_count].value = my_strdup(value);

    if(!__envp[env_count] && !env_vars[env_count].name && !env_vars[env_count].value)
    {
	    perror("Malloc");
	    exit(EXIT_FAILURE);
    }
    env_count++;
}

void free_environment()
{
	int i;
        for (i = 0; i < env_count; i++) 
        {
            if(env_vars[i].name && env_vars[i].value)
            {
                free(env_vars[i].name);
                free(env_vars[i].value);
            }
	    if(__envp[i])
	    {
		    free(__envp[i]);
	    }
        }
        env_count = 0;
        env_capacity = 0;
}

char *get_command_path(char *command)
{
    char *path = get_env("PATH");
    char *dir;
    char *path_copy = my_strdup(path);

    dir = my_strtok(path_copy, ":");
    while (dir)
    {
        char *command_path = (char *)malloc(my_strlen(dir) + my_strlen(command) + 2);
        my_strcpy(command_path, dir);
	my_strcat(command_path, "/"); 
	my_strcat(command_path, command);

        if (access(command_path, X_OK) == 0)
        {
            free(path_copy);
            return command_path;
	}

      
        free(command_path);
        dir = my_strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
