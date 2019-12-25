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

	const char *select_sql = "select * from class";
	char *errmsg = NULL;
	char **result_2 = NULL;
	int row = 0,column = 0;
	if(sqlite3_get_table(db,select_sql,&result_2,&row,&column,&errmsg) != SQLITE_OK){
		printf("select error : %s\n",errmsg);
		goto err;
	}

	printf("查到%d条记录\n",row);
	int i,j,index = column;
	for(i = 0;i < row;i++){
		printf("---------------------------\n");
		for(j = 0;j < column;j++){
			printf("%s %s\n",result_2[j],result_2[index++]);
		}
	}
	
	sqlite3_free_table(result_2);//不管数据库是否查询成功，释放查询结果
	sqlite3_close(db);
	return 0;

err:
	sqlite3_free(errmsg);
	sqlite3_close(db);
	return -1;

}
