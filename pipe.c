#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<memory.h>




int main()
{
	int fd[2];
	if( pipe(fd)< 0 )
	{
		perror("pipe");
		exit(1);
	}
	pid_t id = fork();
	if(id<0)
	{
		perror("fork");
		exit(2);
	}
	if(id == 0)
	{
		char buf[1024];
	//	memset(buf, '\0', sizeof(buf));
		close(fd[1]);
		while(1)
		{
			memset(buf, '\0', sizeof(buf));
			printf("parent#\n:");
			int _s = read(fd[0],buf,sizeof(buf));
			if(_s > 0)
				buf[_s] = '\0';
			printf("%s\n",buf);
		}
	}
	else  //father
	{
		close(fd[0]);
	    const char* msg = "hello!";	
		while(1)
		{	
			write(fd[1],msg,sizeof(msg));
			sleep(1);
		}
	}
	return 0;
}
