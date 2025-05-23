// src/user.c
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "user.h"

#define MAX_LEN 128

// �V�K�o�^
int register_user(sqlite3* db) {
    char user[MAX_LEN], pass[MAX_LEN], mail[MAX_LEN];
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
    printf("���[���A�h���X: ");
    if (scanf("%127s", mail) != 1) {
        fprintf(stderr, "���̓G���[: ���[���A�h���X���s���ł��B\n");
        return -1;
    }

    const char* sql = "INSERT INTO users(username,password,email) VALUES(?,?,?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "�o�^�����G���[: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pass, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, mail, -1, SQLITE_STATIC);

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

// ���O�C��
int login_user(sqlite3* db, int* out_id) {
    char user[MAX_LEN], pass[MAX_LEN];
    printf("���[�U�[��: ");
    if (scanf("%127s", user) != 1) {
        fprintf(stderr, "���̓G���[: ���[�U�[�����s���ł��B\n");
        return -1;
    }
    printf("�p�X���[�h: ");
    if (scanf("%127s", pass) != 1) {
        fprintf(stderr, "���̓G���[: �p�X���[�h���s���ł��B\n");
        return -1;
    }

    const char* sql = "SELECT id FROM users WHERE username=? AND password=?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "���O�C�������G���[: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pass, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *out_id = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        printf("���O�C�������I (ID=%d)\n", *out_id);
        return 0;
    }
    else {
        fprintf(stderr, "���O�C�����s: ���[�U�[���܂��̓p�X���[�h���Ⴂ�܂��B\n");
        sqlite3_finalize(stmt);
        return -1;
    }
}

// ���X�V
int update_user(sqlite3* db, int user_id) {
    char mail[MAX_LEN];
    printf("�V�������[���A�h���X: ");
    if (scanf("%127s", mail) != 1) {
        fprintf(stderr, "���̓G���[: ���[���A�h���X���s���ł��B\n");
        return -1;
    }

    const char* sql = "UPDATE users SET email=? WHERE id=?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "�X�V�����G���[: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, mail, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, user_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "�X�V���s: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    printf("���[���A�h���X���u%s�v�ɍX�V���܂����B\n", mail);
    return 0;
}

// �A�J�E���g�폜
int delete_user(sqlite3* db, int user_id) {
    const char* sql = "DELETE FROM users WHERE id=?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "�폜�����G���[: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_int(stmt, 1, user_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "�폜���s: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    printf("�A�J�E���g(ID=%d)���폜���܂����B\n", user_id);
    return 0;
}

// �ꗗ�\��
void list_users(sqlite3* db) {
    const char* sql = "SELECT id,username,email,created FROM users;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "�ꗗ�擾�����G���[: %s\n", sqlite3_errmsg(db));
        return;
    }
    printf("=== ���[�U�[�ꗗ ===\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("ID=%d, ���[�U�[=%s, ���[��=%s, �o�^��=%s\n",
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_text(stmt, 3)
        );
    }
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "�ꗗ�擾���ɃG���[���������܂���: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
}