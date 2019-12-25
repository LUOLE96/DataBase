#include <stdio.h>
#include "sqlite3.h"
#include <string.h>

typedef struct class
{
	int cid;
	char cname[16];
	char caddr[16];
}class_t;

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
		printf("open sqlite error : %s\n",sqlite3_errmsg(db));
		return -1;
	}
	printf("open sqlite3 ok\n");
#if 0
	const char *create_sql = "create table class(cid int primary key,cname text,address text)";
	char *errmsg = NULL;

	if(SQLITE_OK != sqlite3_exec(db,create_sql,NULL,NULL,&errmsg)){
		printf("exec sql error : %s\n",errmsg);
		goto err;
	}
	printf("create table success\n");
#endif
#if 0
	const char *insert_sql = "insert into class values(1,\'class_1\',\'room_1\')";
	char *errmsg = NULL;
	if(sqlite3_exec(db,insert_sql,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("jinsert error : %s\n",errmsg);
		goto err;

	}
#endif
	//事物开始
	class_t cls[2] = {
		{2,"class_2","room_2"},
		{3,"class_3","room_3"},
	};

	char insert_sql[512] = "";
	char *errmsg = NULL;
	int i;
	for(i = 0;i < 2;i++)
	{
		bzero(insert_sql,sizeof(insert_sql));
		sprintf(insert_sql,"insert into class values(%d,\'%s\',\'%s\')",cls[i].cid,cls[i].cname,cls[i].caddr);
		if(sqlite3_exec(db,insert_sql,NULL,NULL,&errmsg) != SQLITE_OK){
			printf("insert error : %s\n",errmsg);
			goto err;
		}
	}
	//事物结束
	
	sqlite3_close(db);
	return 0;

err:
	sqlite3_free(errmsg);
	sqlite3_close(db);
	return -1;

}
