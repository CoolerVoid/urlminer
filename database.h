#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "mem_ops.h"

sqlite3 *connect_sqlite();
void create_url_tables(sqlite3 *database);
void close_sqlite(sqlite3 *db);
