#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @inf: the info struct
 * @paths: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *inf, char *paths)
{
	if (inf == NULL || paths == NULL)
	return 0;
	
	struct stat sts;
	if (stat(paths, &sts) != 0)
	return 0;

	return S_ISREG(sts.st_mode) ? 1 : 0;
}

/**
 * dup_chars - duplicates characters
 * @pathstrr: the PATH string
 * @_start: starting index
 * @_stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstrr, int _start, int _stop)
{
	int x, y;
	char *buff;

	if (pathstrr == NULL || _start >= _stop || _start < 0)
	return NULL;

	buff = (char *)malloc((_stop - _start + 1) * sizeof(char));
	if (buff == NULL)
	return NULL; /*Memory allocation failed*/

	for (x = _start, y = 0; x < _stop; x++)
	{
	if (pathstrr[x] != ':')
	{
	buff[y++] = pathstrr[x];
	}
	}
	buff[y] = '\0'; 

	return buff;
}

/**
 * free_dup_chars - frees the buffer allocated by dup_chars
 * @buff: pointer to the buffer
 */
void free_dup_chars(char *buff)
{
	free(buff);
}

/**
 * find_path - finds this cmd in the PATH string
 * @inf: the info struct
 * @pathstrr: the PATH string
 * @_cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *inf, char *pathstrr, char *_cmd)
{
	int cur_pos = 0;
	char *paths = NULL;

	if (!pathstrr)
	return NULL;

	if ((_strlen(_cmd) > 2) && starts_with(_cmd, "./"))
	{
	if (is_cmd(inf, _cmd))
	return _cmd;
	}

	for (int x = 0; pathstrr[x]; x++)
	{
	if (pathstrr[x] == ':')
	{
		paths = dup_chars(pathstrr, cur_pos, x);
	/* Check if the current path is an empty string, meaning it represents
	 the current directory*/
		if (!*paths)
	{
                /* Allocate memory to hold the full path of the command*/
	paths = (char *)malloc((_strlen(_cmd) + 3) * sizeof(char)); // +3 for './' and '\0'
	if (paths == NULL)
	return NULL; /* Memory allocation failed*/

                /* Copy "./" and the command name to the paths buffer*/
		_strcpy(paths, "./");
		_strcat(paths, _cmd);
	}
	else
	{
	/*Allocate memory to hold the full path of the command*/
	paths = (char *)malloc((_strlen(paths) + _strlen(_cmd) + 2)
	 * sizeof(char));
	
	if (paths == NULL)
	return NULL; /* Memory allocation failed*/

	/* Concatenate the current path, '/', and the command name to the paths 
	buffer*/
		_strcpy(paths, paths);
		_strcat(paths, "/");
		_strcat(paths, _cmd);
	}

	/* Check if the concatenated path is an executable command*/
	if (is_cmd(inf, paths))
	return paths;

	/* Free the memory allocated for the paths buffer*/
	free(paths);

	/* Move to the next position in the PATH string*/
	cur_pos = x + 1;
	}
	}

	return NULL; /* Command not found in the PATH string*/
	}
