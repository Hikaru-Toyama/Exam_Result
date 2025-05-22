#include <stdio.h>
#include "db.h"
//#include "logic.h"
#include "ui.h"

int main(void) {
    // 1) DB 初期化
    if (db_init("data.sql") != 0) {
        fprintf(stderr, "DB 初期化に失敗しました。\n");
        return 1;
    }
    // 2) DB オープン
    sqlite3* db = db_open("sample.db");
    if (!db) return 1;

    //// 3) メインループ
    //while (1) {
    //    int choice = show_menu();
    //    if (choice == 0) break;
    //    handle_choice(db, choice);
    //}

    // 4) 終了処理
    db_close(db);
    return 0;
}