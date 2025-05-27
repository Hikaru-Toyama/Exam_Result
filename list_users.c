#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "list_users.h"


#define MAX_LEN 128

// 一覧表示
void list_users(sqlite3* db) {

    //ORDER BY user_id で id順にソート
    const char* sql = "SELECT user_id,user_name FROM users ORDER BY user_id ASC;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "一覧取得準備エラー: %s\n", sqlite3_errmsg(db));
        return;
    }
    printf("=== ユーザー一覧 ===\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("ID=%d, ユーザー=%s\n",
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_text(stmt, 3)
        );
    }
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "一覧取得中にエラーが発生しました: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
}