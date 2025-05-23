#ifndef USER_H
#define USER_H

#include <sqlite3.h>

// ƒ†[ƒU[‘€ì
int register_user(sqlite3* db);
int login_user(sqlite3* db, int* out_user_id);
int update_user(sqlite3* db, int user_id);
int delete_user(sqlite3* db, int user_id);
void list_users(sqlite3* db);

#endif // USER_H