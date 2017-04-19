#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv)
{
	int arg_i;
	if (argc == 1) // if there's only one argument
	{
		arg_i = 0; // set the index to 0, only read input from keyboard
	}
	else // more than one argument -> try to read & write each file in argv
	{
		arg_i = 1; // the first file has index 1 in argv
	}

	while (argv[arg_i] != NULL) // while there is given input
	{
		int fd;
		if (arg_i == 0)
		{
			fd = STDIN_FILENO;
		}
		else
		{
			fd = open(argv[arg_i], O_RDONLY); // open it as read only
		}

		if (fd == -1)
		{
			perror(argv[0]);
		}
		else // file opened successfully
		{
			// read the file into a string buffer, 2048 bytes at a time, then write from the buffer.
			char* buf[2048]; // 2048 byte string buffer
			ssize_t bytesRead;
			while ((bytesRead = read(fd, buf, 2048)) > 0)
			{
				ssize_t bytesWritten = write(STDOUT_FILENO, buf, bytesRead);
				if (bytesWritten == -1)
				{
					perror(argv[0]);
				}
			}
			if (bytesRead == -1)
			{
				perror(argv[0]);
			}

			if (fd != STDIN_FILENO) // if a file was read
			{
				if (close(fd) == -1)
				{
					perror(argv[0]);
				}
			}
		}
		++arg_i; // go onto the next file
	}

	return 0;
}

