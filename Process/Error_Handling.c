#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc,char *argv[])
{
	FILE *fp;
	char *buf;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		perror("aaa");
		printf("sterror:%s\n",strerror(errno));
		exit(1);
	}
	perror("perror");
	errno=12;
	printf("strerror:%s\n",strerror(errno));
	fclose(fp);
	return 0;
}

