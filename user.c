// src/user.c
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "user.h"

#define MAX_LEN 128

// 新規登録
int register_user(sqlite3* db) {
    char user[MAX_LEN], pass[MAX_LEN], mail[MAX_LEN];
    printf("新規ユーザー名: ");
    if (scanf("%127s", user) != 1) {
        fprintf(stderr, "入力エラー: ユーザー名が不正です。\n");
        return -1;
    }
    printf("パスワード: ");
    if (scanf("%127s", pass) != 1) {
        fprintf(stderr, "入力エラー: パスワードが不正です。\n");
        return -1;
    }
    printf("メールアドレス: ");
    if (scanf("%127s", mail) != 1) {
        fprintf(stderr, "入力エラー: メールアドレスが不正です。\n");
        return -1;
    }

    const char* sql = "INSERT INTO users(username,password,email) VALUES(?,?,?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "登録準備エラー: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pass, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, mail, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "登録失敗: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    printf("ユーザー「%s」を登録しました。\n", user);
    return 0;
}

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

// 情報更新
int update_user(sqlite3* db, int user_id) {
    char mail[MAX_LEN];
    printf("新しいメールアドレス: ");
    if (scanf("%127s", mail) != 1) {
        fprintf(stderr, "入力エラー: メールアドレスが不正です。\n");
        return -1;
    }

    const char* sql = "UPDATE users SET email=? WHERE id=?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "更新準備エラー: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, mail, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, user_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "更新失敗: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    printf("メールアドレスを「%s」に更新しました。\n", mail);
    return 0;
}

// アカウント削除
int delete_user(sqlite3* db, int user_id) {
    const char* sql = "DELETE FROM users WHERE id=?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "削除準備エラー: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_int(stmt, 1, user_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "削除失敗: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    printf("アカウント(ID=%d)を削除しました。\n", user_id);
    return 0;
}

// 一覧表示
void list_users(sqlite3* db) {
    const char* sql = "SELECT id,username,email,created FROM users;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "一覧取得準備エラー: %s\n", sqlite3_errmsg(db));
        return;
    }
    printf("=== ユーザー一覧 ===\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("ID=%d, ユーザー=%s, メール=%s, 登録日=%s\n",
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