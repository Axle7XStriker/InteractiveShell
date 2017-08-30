#include "read_and_parse.h"

char* read_cmd()
{
    char *cmd;
    size_t cmd_size;
    getline(&cmd, &cmd_size, stdin);
    
    return cmd;
}

char** parse_cmd(char *cmd, const char *delim)
{
    ssize_t token_cmd_size = 32;
    char *token;
    int pos = 0;
    char **parsed_cmd = (char **)malloc(sizeof(char *) * token_cmd_size);
    if (!parsed_cmd)
    {
        fprintf(stderr, "shell: Allocation Error");
        exit(EXIT_FAILURE);
    }
    
    token = strtok(cmd, delim);
    while(token != NULL)
    {
        parsed_cmd[pos++] = token;
        if (pos == token_cmd_size)
        {
            token_cmd_size += token_cmd_size;
            parsed_cmd = realloc(parsed_cmd, token_cmd_size * sizeof(char *));
            if (!parsed_cmd)
            {
                fprintf(stderr, "shell: Allocation Error");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, delim);
    }
    parsed_cmd[pos] = NULL;
    
    return parsed_cmd;
}
