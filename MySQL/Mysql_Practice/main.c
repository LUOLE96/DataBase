#include <stdio.h>
#include <mysql/mysql.h>

int main(void)
{
    MYSQL mysql;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    int rc, i, fields;
    int rows;
    char *query_str = NULL;

    if(NULL == mysql_init(&mysql)){//分配和初始化对象
        printf("mysql_init:%s\n",mysql_error(&mysql));
        return -1;
    }
    //尝试与运行在主机上的MySQL数据库引擎建立连接
    if(NULL == mysql_real_connect(&mysql,"127.0.0.1","root","LUOLE123....","mydb61",3306,NULL,0))
    {
      printf("mysql_real_connect():%s\n",mysql_error(&mysql));
      return -1;
    }
    printf("Connection Mysql success!\n");


    query_str = "select * from runoob_tbl";
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if(0 != rc){
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return -1;
    }

    res = mysql_store_result(&mysql);
    if(NULL == res){
        printf("mysql_restore_result(): %s\n", mysql_error(&mysql));
        return -1;
    }
    rows = mysql_num_rows(res);
    printf("The total rows is: %d\n", rows);
    fields = mysql_num_fields(res);
    printf("The total fields is: %d\n", fields);
    while((row == mysql_fetch_row(res))){
        for (i = 0; i < fields; i++) {
            printf("%s\t", row[i]);}
        printf("\n");
    }
    mysql_close(&mysql);
    return 0;
}
