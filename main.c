#include "platform.h"        // �� ������ access/F_OK ���`
#include <stdio.h>
#include <sqlite3.h>
#include "db.h"
#include "user.h"
#include "menu.h"

int main(void) {
    // 1) DB�t�@�C�����Ȃ���� data.sql �ŏ�����
    if (access("sample.db", F_OK) != 0) {
        if (db_init("sample.db", "data.sql") != 0) {
            fprintf(stderr, "DB�������Ɏ��s���܂����B�������I�����܂��B\n");
            return 1;
        }
        printf("DB�����������܂����B\n");
    }

    // 2) DB���I�[�v��
    sqlite3* db = init_db("sample.db");
    if (!db) {
        fprintf(stderr, "DB�I�[�v���Ɏ��s���܂����B�������I�����܂��B\n");
        return 1;
    }
    printf("[DEBUG] DB�n���h�����L���Ɏ擾�ł��܂����B\n");


    // 3) ���C���^�T�u���j���[�̃��[�v
    int choice, user_id = -1;
    while (1) {
        if (user_id < 0) {
            show_main_menu();
            if (scanf("%d", &choice) != 1) break;
            if (choice == 1) register_user(db);
            else if (choice == 2 && login_user(db, &user_id) == 0) {
                while (user_id >= 0) {
                    show_user_menu();
                    if (scanf("%d", &choice) != 1) { user_id = -1; break; }
                    if (choice == 1) update_user(db, user_id);
                    else if (choice == 2) { delete_user(db, user_id); user_id = -1; }
                    else if (choice == 3) list_users(db);
                    else if (choice == 4) user_id = -1;
                    else                  printf("�����ȑI���ł��B\n");
                }
            }
            else if (choice == 3) break;
            else                  printf("�����ȑI���ł��B\n");
        }
    }

    // 4) �I�����Ɋm����DB�����
    close_db(db);
    printf("�I�����܂����B\n");
    return 0;
}