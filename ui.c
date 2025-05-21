#include "ui.h"
#include <stdio.h>

int show_menu(void) {
	int choice;
	printf("\n=== メニュー ===\n");
	printf("1) 新規登録\n");
	printf("2) 変更\n");
	printf("3) 削除\n");
	printf("4) ソート結果表示\n");
	printf("0) 終了\n");
	printf("選択: ");
	if (scanf_s("%d", &choice) != 1) {
		fprintf(stderr, "入力エラー: 数字を入力してください。\n");

		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		return -1;
	}
	return choice;
}

//新規登録
int show_register(void) {

}