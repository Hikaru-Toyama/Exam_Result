#ifndef DB_H
#define DB_H
#include <sqlite3.h>

// DB 初期化: SQL ファイルを読み込んでテーブル作成
int db_init(const char* sql_file);

// DB オープン／クローズ
sqlite3* db_open(const char* filename);
void db_close(sqlite3* db);

#endif