#include "logic.h"
#include <stdio.h>

#include <stdlib.h>
// 文字列入力時の改行を捨てるユーティリティ
static void trim_newline(char* s) {
	size_t n = strlen(s);
	if (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
		s[n - 1] = '\0';
	}
}

// TODO: ユーザー入力→INSERT
void register_student(sqlite3* db) {
	
	char name[128];
	int c;

	while ((c = getchar()) != '\n' && c != EOF){}

	printf("\n=== 新規受験者登録 ===\n");
	printf("名前を入力してください:");
	if (!fgets(name, sizeof(name), stdin)) {
		fprintf(stderr, "入力エラー\n");
		return;
	}

	//改行トリム
	trim_newline(name);

	//SQL文準備
	sqlite3_stmt *stmt;
	const char *sql = "INSERT INTO students (name) VALUES (?);";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "SQL 準備エラー: %s\n", sqlite3_errmsg(db));
		return;
	}

	//バインド＆実行
	sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
	if (sqlite3_step(stmt) != SQLITE_DONE) {
		fprintf(stderr, "登録失敗: %s\n", sqlite3_errmsg(db));
	}
	else {
		printf("'%s' を登録しました。\n", name);
	}
	sqlite3_finalize(stmt);
}

// TODO: ユーザー選択→UPDATE
void update_student(sqlite3* db) {
	
}

// TODO: ユーザー選択→DELETE
void delete_student(sqlite3* db) {
	
}

	// TODO: SELECT ... ORDER BY ...
void list_sorted_results(sqlite3* db) {

}

void handle_choice(sqlite3 *db, int choice) {
	switch (choice){
		case 1: register_student(db); break;
		case 2: update_student(db); break;
		case 3: delete_student(db); break;
		case 4: list_sorted_results(db); break;
		default: break;
	}
}