#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "update_user.h"


#define MAX_LEN 128

// 情報更新(パスワードのみ)
int update_user(sqlite3* db, int user_id) {
    char pass[MAX_LEN];
    printf("新しいパスワード: ");
    if (scanf("%127s", pass) != 1) {
        fprintf(stderr, "入力エラー: パスワードが不正です。\n");
        return -1;
    }

    const char* sql = "UPDATE users SET password=? WHERE user_id=?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "更新準備エラー: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, pass, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, user_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "更新失敗: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    printf("パスワードを「%s」に更新しました。\n", pass);
    return 0;
}