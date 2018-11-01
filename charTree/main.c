#include "tree.h"
#include <mysql.h>

#include <sys/time.h>
#include <unistd.h>

#define NUMBER_WORDS    100

/*
	CR_COMMANDS_OUT_OF_SYNC：命令以一个不适当的次序被执行。
	CR_SERVER_GONE_ERROR：MySQL服务器关闭了。
	CR_SERVER_LOST：对服务器的连接在查询期间失去。
	CR_UNKNOWN_ERROR：发生一个未知的错误
*/

static inline void _mysql_check(MYSQL * con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(EXIT_FAILURE);
}

void main(){

	TrieNode* root = NULL;
	createTree(&root);

	MYSQL *con = mysql_init(NULL);
	if (con == NULL) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(EXIT_FAILURE);
	}

	if (!mysql_real_connect(con, "127.0.0.1", "root", "newpassword", "words", 0, NULL, 0)) {
		_mysql_check(con);
	}  


	puts("mariadb is connect and run succesed!");



	printf("use words\n");

	char* str = "select* from words;";
	if (mysql_real_query(con, str,strlen(str))){
		printf("wrong \n");
		_mysql_check(con);
	}
	printf("%s\n",str);
// ----------------------------------------------------------- 

    MYSQL_RES * res = mysql_store_result(con);
    if (NULL == res)
	{
		printf("error!\n");
        _mysql_check(con);
	}

    MYSQL_ROW row;
    unsigned rlen = mysql_num_fields(res);
    printf("mariadb now row length = %u\n", rlen);
    
 	int counter = 0;
    while ((row = mysql_fetch_row(res))) {
        char* temp = row[1];
		int i = 0;
		int isword = 1;
		for(i = 0; i < strlen(temp); i++){
			if(temp[i] > 'z' || temp[i] < 'a'){
				isword = 0;
				break;
			}
				
		}
		if(isword == 1){
			//if(strcmp(row[1],"childe") == 0)
			//{
			//	printf("%s--------------\n" , row[1]);
			//	getchar();
			//}
			insertTree(root,row[1]);
            //printf("%s ", row[1]);
        	//putchar('\n');
			counter = counter + 1;
		}
		//if(counter == NUMBER_WORDS)
		//	break;
    }
	
	mysql_free_result(res);
	//mysql_close(con); 

	printf(" %d words in database\n",counter);

	long long start_time, end_time;

	struct timeval tv;

	gettimeofday(&tv,NULL);



// --------------- search in mysql databases ( Segmentation fault (core dumped) )-----------------------
    // SELECT * FROM fruits WHERE f_name IN('apple','orange');
	int total_counter = 100000;
	start_time = tv.tv_sec*1000*1000 + tv.tv_usec;
	
	int counter_query = 0;
	int result_counter = 0;
	char* str_mysql = "select* from words where word IN('alternative');";
	for(counter_query = 0 ; counter_query < total_counter; counter_query++){

		if (mysql_real_query(con, str_mysql,strlen(str_mysql))){
			printf("query fail\n");
			_mysql_check(con);
		}

		MYSQL_RES * res_mysql = mysql_store_result(con);
		if (NULL == res_mysql)
		{
			printf("error res_mysql!\n");
		    _mysql_check(con);
		}

		MYSQL_ROW row_mysql;

		while ((row_mysql = mysql_fetch_row(res_mysql))) {
			result_counter++;
			//printf("find words in databases!\n");
		}
	}

	if(result_counter == total_counter){
		gettimeofday(&tv,NULL);
		end_time = tv.tv_sec*1000*1000+tv.tv_usec;
		printf("time_val in dataBase = %lld\n",end_time-start_time);
	}

// -------------------- search in tree -------------------
	result_counter = 0;
	char* search_word = "alternative";
	start_time = tv.tv_sec*1000*1000 + tv.tv_usec;
	for(counter_query = 0 ; counter_query < total_counter; counter_query++){
		if( search(root,search_word) == 1 )
			result_counter++;
	}
	if(result_counter == total_counter){
		gettimeofday(&tv,NULL);
		end_time = tv.tv_sec*1000*1000+tv.tv_usec;
		printf("time_val in tree = %lld\n",end_time-start_time);
	}

	return;


// ----------------------------------------------------------- 

	// ------ make up tree of word , store the word
	//char* train_string = "liqing";
	//char* string_1 = "lijunjie";
	//char* string_2 = "linjunjie";

	//char* search_1 = "lijunjie";
	//char* search_2 = "linyoujia";

	//TrieNode* root = NULL;
	//createTree(&root);
	
	//insertTree(root,train_string);
	//insertTree(root,string_1);
	//insertTree(root,string_2);


	// ------ search word
	char search_string[100];
	printf("input search string : ");
	scanf("%s",search_string); 
	while(1){
		if( search(root,search_string) == 1 )
			printf("%s is in the set\n",search_string);
		else
			printf("%s is ----- not in set\n",search_string);
		printf("input search string : ");
		scanf("%s",search_string);
	}

}
