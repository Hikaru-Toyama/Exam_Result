#include "db.h"
#include <stdio.h>
#include <stdlib.h>

sqlite3* db_open(const char* filename) {
	sqlite3* db;
	if (sqlite3_open(filename, &db) != SQLITE_OK) {
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		return NULL;
	}
	return db;
}

int db_init(const char* sql_file) {
	sqlite3* db = db_open("sample.db");
	if (!db)return 1;
	FILE* fp = fopen(sql_file, "rb");
	if (!fp)return 1;
	fseek(fp, 0, SEEK_END);
	long len = ftell(fp); rewind(fp);
	char* buf = malloc(len + 1);
	fread(buf, 1, len, fp);
	buf[len] = '\0';
	fclose(fp);
	char* err = NULL;
	int rc = sqlite3_exec(db, buf, NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err);
		sqlite3_free(err);
	}
	free(buf);
	db_close(db);
	return rc != SQLITE_OK;
}

void db_close(sqlite3* db) {
	sqlite3_close(db);
}