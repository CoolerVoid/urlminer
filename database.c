#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "mem_ops.h"

sqlite3 *connect_sqlite()
{

	sqlite3 *db;
	int rc=0;
// in memory db
	rc = sqlite3_open(NULL, &db);

	if( rc )
	{
		DEBUG("Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}else{
		fprintf(stderr, "Start Load SQLite3 database : Successfully\n");
	}
// after use this function use sqlite3_close() to close DB
// 	sqlite3_close(db);
	return db;
}

void create_url_tables(sqlite3 *database)
{
	char *table_start=
	"CREATE TABLE url_list("
	"  urlid   INTEGER PRIMARY KEY AUTOINCREMENT,"
	"  url     varchar(1024) NOT NULL UNIQUE, "
	"  depth   INTEGER,"
	"  position INTEGER,"
	"  thread INTEGER"
	");"
	"CREATE TABLE page ("
	"  pageid  INTEGER primary key autoincrement,"
	"  source  TEXT,"
	"  urlid   INTEGER,"
	"  FOREIGN KEY(urlid) REFERENCES url_list(urlid)"
	");";
	int rc=0;
	char *ErrMsg=0;

	rc = sqlite3_exec(database, table_start, 0, 0, &ErrMsg);
   	if( rc != SQLITE_OK ){
   		DEBUG(stderr, "SQL error : %s\n", ErrMsg);
		sqlite3_free(ErrMsg);
		exit(0);
 	}else{
		fprintf(stdout, "Table created successfully\n");
 	}
}

void close_sqlite(sqlite3 *db)
{
	char *ErrMsg=0;

	if(sqlite3_close(db) == SQLITE_OK)
 		fprintf(stdout,"Close SQLite Database Sucesfullys\n");
	else {	
   		DEBUG("Close database error : %s\n", ErrMsg);
		sqlite3_free(ErrMsg);
		exit(0);	
	}

}


