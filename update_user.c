#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "update_user.h"


#define MAX_LEN 128

// ���X�V(�p�X���[�h�̂�)
int update_user(sqlite3* db, int user_id) {
    char pass[MAX_LEN];
    printf("�V�����p�X���[�h: ");
    if (scanf("%127s", pass) != 1) {
        fprintf(stderr, "���̓G���[: �p�X���[�h���s���ł��B\n");
        return -1;
    }

    const char* sql = "UPDATE users SET password=? WHERE user_id=?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "�X�V�����G���[: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, pass, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, user_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "�X�V���s: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    printf("�p�X���[�h���u%s�v�ɍX�V���܂����B\n", pass);
    return 0;
}