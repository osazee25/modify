#include <stdio.h>
#include <sys/stat.h>

 int is_cmd(info_t *inf, char *paths)
 {
         struct stat sts;

         (void)inf;
         if (stat(paths, &sts) || !paths)
                 return (0);

         if (sts.st_mode & S_IFREG)
          {
                 return (1);
         }
         return (0);

#include <stdio.h>
#include <stdlib.h>

char *dup_chars(char *pathstrr, int _start, int _stop)
{
    static char buff[1024];
    int x = _start, y = 0;

    while (x < _stop && pathstrr[x] != ':')
    {
        buff[y++] = pathstrr[x++];
    }

    buff[y] = '\0'; // Null-terminate the copied characters in buff
    return buff;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming _strlen, starts_with, dup_chars, and is_cmd functions are defined elsewhere...

char *find_path(info_t *inf, char *pathstrr, char *_cmd)
{
    int cur_pos = 0;
    char *paths;

    if (!pathstrr)
        return NULL;

    // Check if _cmd starts with "./" and is executable in the current directory
    if (_strlen(_cmd) > 2 && starts_with(_cmd, "./"))
    {
        if (is_cmd(inf, _cmd))
            return _cmd;
    }

    for (int x = 0; ; x++)
    {
        if (!pathstrr[x] || pathstrr[x] == ':')
        {
            // Extract the path segment from pathstrr
            paths = dup_chars(pathstrr, cur_pos, x);

            // Concatenate the path with _cmd
            if (!*paths)
                _strcat(paths, _cmd);
            else
            {
                _strcat(paths, "/");
                _strcat(paths, _cmd);
            }

            // Check if the combined path exists and is executable
            if (is_cmd(inf, paths))
                return paths;

            // If we reached the end of pathstrr, exit the loop
            if (!pathstrr[x])
                break;

            // Move to the next path segment
            cur_pos = x + 1;
        }
    }

    return NULL; // The _cmd was not found in any of the directories
}
