#ifndef LOGIN_USER_H
#define LOGIN_USER_H

#include <sqlite3.h>

// ���[�U�[���O�C��
int login_user(sqlite3* db, int* out_user_id);

#endif