#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "delete_user.h"

#define MAX_LEN 128

// �A�J�E���g�폜
int delete_user(sqlite3* db, int user_id) {
    const char* sql = "DELETE FROM users WHERE id=?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "�폜�����G���[: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_int(stmt, 1, user_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "�폜���s: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    printf("�A�J�E���g(ID=%d)���폜���܂����B\n", user_id);
    return 0;
}