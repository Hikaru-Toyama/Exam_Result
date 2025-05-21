#ifndef DB_H
#define DB_H
#include <sqlite3.h>

// DB ������: SQL �t�@�C����ǂݍ���Ńe�[�u���쐬
int db_init(const char* sql_file);

// DB �I�[�v���^�N���[�Y
sqlite3* db_open(const char* filename);
void db_close(sqlite3* db);

#endif