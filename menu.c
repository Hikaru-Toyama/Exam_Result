#include <stdio.h>
#include "menu.h"

void show_main_menu() {
    puts("1: 新規登録");
    puts("2: ログイン");
    puts("3: 終了");
    printf("選択してください> ");
}

void show_user_menu() {
    puts("1: 変更");
    puts("2: 削除");
    puts("3: ユーザー一覧");
    puts("4: ログアウト");
    printf("選択してください> ");
}