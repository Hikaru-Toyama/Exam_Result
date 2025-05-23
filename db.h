#ifndef DB_H
#define DB_H

#include <sqlite3.h>

// 初期化（schema.sql→data.sql）
/// @return SQLITE_OK(0) または sqlite3_open のエラーコード／-1
int db_init(const char* db_path, const char* data_sql_path);

// DB オープン
/// @return 有効な sqlite3* または NULL
sqlite3* init_db(const char* db_path);
void     close_db(sqlite3* db);

#endif // DB_H