#include "platform.h"        // ← ここで access/F_OK を定義
#include <stdio.h>
#include <sqlite3.h>
#include "db.h"
#include "user.h"
#include "menu.h"

int main(void) {
    // 1) DBファイルがなければ data.sql で初期化
    if (access("sample.db", F_OK) != 0) {
        if (db_init("sample.db", "data.sql") != 0) {
            fprintf(stderr, "DB初期化に失敗しました。処理を終了します。\n");
            return 1;
        }
        printf("DBを初期化しました。\n");
    }

    // 2) DBをオープン
    sqlite3* db = init_db("sample.db");
    if (!db) {
        fprintf(stderr, "DBオープンに失敗しました。処理を終了します。\n");
        return 1;
    }
    printf("[DEBUG] DBハンドルが有効に取得できました。\n");


    // 3) メイン／サブメニューのループ
    int choice, user_id = -1;
    while (1) {
        if (user_id < 0) {
            show_main_menu();
            if (scanf("%d", &choice) != 1) break;
            if (choice == 1) register_user(db);
            else if (choice == 2 && login_user(db, &user_id) == 0) {
                while (user_id >= 0) {
                    show_user_menu();
                    if (scanf("%d", &choice) != 1) { user_id = -1; break; }
                    if (choice == 1) update_user(db, user_id);
                    else if (choice == 2) { delete_user(db, user_id); user_id = -1; }
                    else if (choice == 3) list_users(db);
                    else if (choice == 4) user_id = -1;
                    else                  printf("無効な選択です。\n");
                }
            }
            else if (choice == 3) break;
            else                  printf("無効な選択です。\n");
        }
    }

    // 4) 終了時に確実にDBを閉じる
    close_db(db);
    printf("終了しました。\n");
    return 0;
}