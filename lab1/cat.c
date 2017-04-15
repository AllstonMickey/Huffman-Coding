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
		
	}
	else // arguments (hopefully files to read) were given, read from I/O
	{
		for (int arg_i = 1; arg_i < argc; arg_i++) // for each file
		{
			int fd = open(argv[arg_i], O_RDONLY); // file descriptor of current argument
			if (fd == -1) // file can't be opened
			{
				perror(argv[0]);
			}
			else // file is opened
			{
				// read
				char* buf[2048]; // 2048 byte buffer
				ssize_t bytesRead;
				while ((bytesRead = read(fd, buf, 2048)) > 0)
				{
					ssize_t bytesWritten = write(STDOUT_FILENO, buf, 2048);
					if (bytesWritten == -1)
					{
						perror(argv[0]);
					}
				}
				if (bytesRead == -1)
				{
					perror(argv[0]);
				}

				// print
				// close
			}
		}
	}

	return 0;
}
