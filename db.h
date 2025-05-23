#ifndef DB_H
#define DB_H

#include <sqlite3.h>

// �������ischema.sql��data.sql�j
/// @return SQLITE_OK(0) �܂��� sqlite3_open �̃G���[�R�[�h�^-1
int db_init(const char* db_path, const char* data_sql_path);

// DB �I�[�v��
/// @return �L���� sqlite3* �܂��� NULL
sqlite3* init_db(const char* db_path);
void     close_db(sqlite3* db);

#endif // DB_H