#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "login_user.h"

#define MAX_LEN 128


// ログイン
int login_user(sqlite3* db, int* out_id) {
    char user[MAX_LEN], pass[MAX_LEN];
    printf("ユーザー名: ");
    if (scanf("%127s", user) != 1) {
        fprintf(stderr, "入力エラー: ユーザー名が不正です。\n");
        return -1;
    }
    printf("パスワード: ");
    if (scanf("%127s", pass) != 1) {
        fprintf(stderr, "入力エラー: パスワードが不正です。\n");
        return -1;
    }

    const char* sql = "SELECT id FROM users WHERE username=? AND password=?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "ログイン準備エラー: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pass, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *out_id = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        printf("ログイン成功！ (ID=%d)\n", *out_id);
        return 0;
    }
    else {
        fprintf(stderr, "ログイン失敗: ユーザー名またはパスワードが違います。\n");
        sqlite3_finalize(stmt);
        return -1;
    }
}