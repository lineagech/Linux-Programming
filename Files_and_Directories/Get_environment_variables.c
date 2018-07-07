#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char *path=getenv("PATH");
	if(path)
		printf("PATH:%s\n",path);
	return 0;
}
//echo $PATH


