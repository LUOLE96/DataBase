#include <stdio.h>
#include "sqlite3.h"

int main(int argc,char **argv)
{
	if(argc < 2)
	{
		perror("param must >= 2");
		return -1;
	}
	sqlite3 *db = NULL;
	int result;
	result = sqlite3_open(argv[1],&db);
	if(result != SQLITE_OK)
	{
		printf("open sqlite error : %s\n",sqlite_errmsg(db));
		return -1;
	}
	printf("open sqlite3 ok\n");

	sqlite3_close(db);

}
