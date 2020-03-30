#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int n, char **argv)
{
	int fd;

	fd = open("ok", O_RDWR);
	char **str;
	str = (char**)malloc(4*sizeof(char*));
	str[0] = strdup("/bin/echo");
	//str[1] = strdup("-n");
	str[1] = strdup("hello world motherfuckers");
	str[3] = NULL;
	if (fork() == 0)
	{
		dup2(fd, 1);
		if (execve("/bin/echo", str, NULL) == -1){
			perror("minishell");
		};
		exit(0);
	}
	else{
		int m;
		wait(&m);

	}
	return 0;
}