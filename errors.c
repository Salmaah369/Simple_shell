#include "shell.h"

/**
 * _eputs - displays the input string
 * @str: the input string to be printed
 *
 * Return: Null
 */
void _eputs(char *str) {
    int i = 0;
    if (!str)
        return;
    while (str[i] != '\0') {
        _eputchar(str[i]);
        i++;
    }
}

/**
 * _eputchar - echoes the character c to stderr
 * @c: The character to be printed
 *
 * Return: 1 if the operation was successfull
 * if an error occurs, the function returns -1 and sets errno appropriately.
 */
int _eputchar(char c) {
    static int i;
    static char buf[WRITE_BUF_SIZE];
    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(3, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * _putfd - writes the character 'c' to the file descriptor 'fd'
 * @c: The character to be printed
 * @fd: The file descriptor to write to
 *
 * Return: 1 if the operation was successfull
 * if an error occurs, the function returns -1 and sets errno appropriately.
 */
int _putfd(char c, int fd) {
    static int i;
    static char buf[WRITE_BUF_SIZE];
    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the input string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: displays the input string
 */
int _putsfd(char *str, int fd) {
    int i = 0;
    if (!str)
        return (0);
    while (*str) {
        i += _putfd(*str++, fd);
    }
    return (i);
}
