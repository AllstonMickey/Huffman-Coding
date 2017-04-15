#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char** argv)
{
	if (argc == 1) // if there is only 1 argument, get input from standard input
	{
		while (1)
		{
			char* buf[2048];
			ssize_t bytesRead = read(STDIN_FILENO, buf, 2048);
			if (bytesRead == -1)
			{
				perror(argv[0]);
				exit(errno);
			}
			ssize_t bytesWritten = write(STDOUT_FILENO, buf, bytesRead);
			if (bytesWritten == -1)
			{
				perror(argv[0]);
				exit(errno);
			}
		}
	}
	else
	{
		for (int arg_i = 1; arg_i < argc; arg_i++) // for each file
		{
			int fd = open(argv[arg_i], O_RDONLY);
			if (fd == -1)
			{
				
				perror(argv[0]);
			}
			else
			{
				char* buf[2048]; // 2048 byte buffer
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

				int closed = close(fd);
				if (closed == -1)
				{
					perror(argv[0]);
				}
			}
		}
	}

	return 0;
}

