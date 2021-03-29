#include "holberton.h"

/**
 * read_textfile - reads a text file and prints it to the standard output
 * @filename: name of the file to be read
 * @letters: number of letters to read and print
 *
 * Return: the number of letters printed, or 0 if it failed
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	ssize_t k;
	int fd;
	char *buf;

	if (!filename)
		return (0);
		buf = malloc(sizeof(char) * letters+1);
	if (buf == NULL)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	    free(buf);
		return (0);
	k = read(fd, buf, sizeof(char) * letters);
	if (k ==-1)
	{
		free(buf);
		close(fd);
		return (0);
	}
	k = write(STDOUT_FILENO, buf, k);
	if (k == -1)
	{
		free(buf);
		close(fd);
		return (0);
	}
	free(buf);
	close(fd);
	return (k);
}
