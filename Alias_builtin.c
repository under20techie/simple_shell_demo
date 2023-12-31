#include "main.h"
void add_alias(char *alias, char *command) 
{
    alias_count = 0;
    if (alias_count >= MAX_ALIAS_COUNT) 
    {
        perror("Alias: Maximum number of aliases reached.");
        return;
    }

    aliases[alias_count].alias = my_strdup(alias);
    aliases[alias_count].command = my_strdup(command);
    alias_count++;
}

void list_aliases() 
{
    int i;
    for (i = 0; i < alias_count; i++) 
    {
        printf("alias %s='%s'\n", aliases[i].alias, aliases[i].command);
    }
}

void remove_alias(char *alias) 
{
    int i, j;
    for (i = 0; i < alias_count; i++)
    {
        if (_strcmp(aliases[i].alias, alias) == 0) 
        {
            free(aliases[i].alias);
            free(aliases[i].command);
            /* Shift the elements after the removed alias
            */
            for (j = i; j < alias_count; j++)
            {
                aliases[j] = aliases[j + 1];
            }
            alias_count--;
            return;
        }
    }
}

char *get_alias(char *alias) 
{
    int i;
    for (i = 0; i < alias_count; i++) 
    {
        if (_strcmp(aliases[i].alias, alias) == 0) 
        { 
            return aliases[i].command;
        }
    }
    return NULL;
}

void free_aliases() 
{
    int i;
    for (i = 0; i < alias_count; i++) 
    {
        if(aliases[i].alias && aliases[i].command)
        {
            free(aliases[i].alias);
            free(aliases[i].command);
        }
    }
    alias_count = 0;
}
