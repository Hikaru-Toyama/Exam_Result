#include "logic.h"
#include <stdio.h>

#include <stdlib.h>
// ��������͎��̉��s���̂Ă郆�[�e�B���e�B
static void trim_newline(char* s) {
	size_t n = strlen(s);
	if (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
		s[n - 1] = '\0';
	}
}

// TODO: ���[�U�[���́�INSERT
void register_student(sqlite3* db) {
	
	char name[128];
	int c;

	while ((c = getchar()) != '\n' && c != EOF){}

	printf("\n=== �V�K�󌱎ғo�^ ===\n");
	printf("���O����͂��Ă�������:");
	if (!fgets(name, sizeof(name), stdin)) {
		fprintf(stderr, "���̓G���[\n");
		return;
	}

	//���s�g����
	trim_newline(name);

	//SQL������
	sqlite3_stmt *stmt;
	const char *sql = "INSERT INTO students (name) VALUES (?);";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "SQL �����G���[: %s\n", sqlite3_errmsg(db));
		return;
	}

	//�o�C���h�����s
	sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
	if (sqlite3_step(stmt) != SQLITE_DONE) {
		fprintf(stderr, "�o�^���s: %s\n", sqlite3_errmsg(db));
	}
	else {
		printf("'%s' ��o�^���܂����B\n", name);
	}
	sqlite3_finalize(stmt);
}

// TODO: ���[�U�[�I����UPDATE
void update_student(sqlite3* db) {
	
}

// TODO: ���[�U�[�I����DELETE
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