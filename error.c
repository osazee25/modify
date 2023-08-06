#include "shell.h"

/**
 *_eputs - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *s) {
    if (!s)
        return;

    for (int x = 0; s[x] != '\0'; x++) {
        _eputchar(s[x]);
    }
}

/**
 * _eputchar - writes the character ch to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 * _putfd - writes the char ch to given file descriptor
 * @ch: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char ch, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @s: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *s, int fd) {
    if (!s)
        return 0;

    int u = 0;

    for (; *s; s++) {
        u += _putfd(*s, fd);
    }

    return u;
}
