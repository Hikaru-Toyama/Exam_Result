#ifndef DELETE_USER_H
#define DELETE_USER_H

#include <sqlite3.h>

// ユーザー削除
int delete_user(sqlite3* db, int user_id);

#endif
