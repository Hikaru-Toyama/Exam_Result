#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "register_user.h"


#define MAX_LEN 128

// �V�K�o�^
int register_user(sqlite3* db) {
    char user[MAX_LEN], pass[MAX_LEN];
    printf("�V�K���[�U�[��: ");
    if (scanf("%127s", user) != 1) {
        fprintf(stderr, "���̓G���[: ���[�U�[�����s���ł��B\n");
        return -1;
    } 
    
    printf("�p�X���[�h: ");
    if (scanf("%127s", pass) != 1) {
        fprintf(stderr, "���̓G���[: �p�X���[�h���s���ł��B\n");
        return -1;
    }
   
    const char* sql = "INSERT INTO users(user_name,password) VALUES(?,?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "�o�^�����G���[: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pass, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "�o�^���s: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    printf("���[�U�[�u%s�v��o�^���܂����B\n", user);
    return 0;
}