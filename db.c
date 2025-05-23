#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "platform.h"
#include "db.h"

// SQL �t�@�C�����ۂ��Ɠǂݍ��� exec ���郆�[�e�B���e�B
static int exec_sql_file(sqlite3* db, const char* path) {
    FILE* fp = fopen(path, "rb");
    if (!fp) {
        fprintf(stderr, "[db_init] SQL�t�@�C�����J���܂���: %s\n", path);
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    rewind(fp);

    char* buf = malloc(len + 1);
    if (!buf || fread(buf, 1, len, fp) != (size_t)len) {
        fprintf(stderr, "[db_init] Failed to read SQL file: %s\n", path);
        fclose(fp);
        free(buf);
        return -1;
    }
    buf[len] = '\0';
    fclose(fp);

    char* err = NULL;
    int rc = sqlite3_exec(db, buf, NULL, NULL, &err);
    free(buf);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "[db_init] %s ���s�G���[: %s\n", path, err);
        sqlite3_free(err);
        return -1;
    }
    return 0;
}

// �������Fschema.sql �� data.sql
int db_init(const char* db_path, const char* data_sql_path) {
    sqlite3* db = NULL;
    int rc = sqlite3_open(db_path, &db);
    printf("[DEBUG db_init] sqlite3_open(\"%s\") rc=%d, db=%p\n", db_path, rc, (void*)db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "[db_init] �f�[�^�x�[�X�̃I�[�v���Ɏ��s���܂���: %s\n", sqlite3_errmsg(db));
        if (db) sqlite3_close(db);
        return rc;
    }

    if (exec_sql_file(db, "schema.sql") != 0 ||
        exec_sql_file(db, data_sql_path) != 0) {
        fprintf(stderr, "[db_init] �������X�N���v�g���s���ɃG���[���������܂����B\n");
        sqlite3_close(db);
        return -1;
    }

    sqlite3_close(db);
    return SQLITE_OK;
}

// DB �I�[�v��
sqlite3* init_db(const char* db_path) {
    sqlite3* db = NULL;
    int rc = sqlite3_open(db_path, &db);
    printf("[�f�o�b�O init_db] sqlite3_open(\"%s\") rc=%d, db=%p\n", db_path, rc, (void*)db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "[init_db] �f�[�^�x�[�X�̃I�[�v���Ɏ��s���܂���: %s\n", sqlite3_errmsg(db));
        if (db) sqlite3_close(db);
        return NULL;
    }
    return db;
}

void close_db(sqlite3* db) {
    if (db) sqlite3_close(db);
}