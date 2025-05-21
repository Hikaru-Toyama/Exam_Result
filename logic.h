#ifndef LOGIC_H
#define LOGIC_H
#include <sqlite3.h>

void register_student(sqlite3* db);
void update_student(sqlite3* db);
void delete_student(sqlite3* db);
void list_sorted_results(sqlite3* db);
void handle_choice(sqlite3* db, int choice);

#endif
