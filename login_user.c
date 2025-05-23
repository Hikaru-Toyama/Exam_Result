#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "login_user.h"

#define MAX_LEN 128


// ���O�C��
int login_user(sqlite3* db, int* out_id) {
    char user[MAX_LEN], pass[MAX_LEN];
    printf("���[�U�[��: ");
    if (scanf("%127s", user) != 1) {
        fprintf(stderr, "���̓G���[: ���[�U�[�����s���ł��B\n");
        return -1;
    }
    printf("�p�X���[�h: ");
    if (scanf("%127s", pass) != 1) {
        fprintf(stderr, "���̓G���[: �p�X���[�h���s���ł��B\n");
        return -1;
    }

    const char* sql = "SELECT id FROM users WHERE username=? AND password=?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "���O�C�������G���[: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pass, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *out_id = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        printf("���O�C�������I (ID=%d)\n", *out_id);
        return 0;
    }
    else {
        fprintf(stderr, "���O�C�����s: ���[�U�[���܂��̓p�X���[�h���Ⴂ�܂��B\n");
        sqlite3_finalize(stmt);
        return -1;
    }
}