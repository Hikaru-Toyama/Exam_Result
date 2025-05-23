#ifndef UPDATE_USER_H
#define UPDATE_USER_H

#include <sqlite3.h>

// ユーザー更新
int update_user(sqlite3* db, int user_id);

#endif