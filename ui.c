#include "ui.h"
#include <stdio.h>

int show_menu(void) {
	int choice;
	printf("\n=== ���j���[ ===\n");
	printf("1) �V�K�o�^\n");
	printf("2) �ύX\n");
	printf("3) �폜\n");
	printf("4) �\�[�g���ʕ\��\n");
	printf("0) �I��\n");
	printf("�I��: ");
	if (scanf_s("%d", &choice) != 1) {
		fprintf(stderr, "���̓G���[: ��������͂��Ă��������B\n");

		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		return -1;
	}
	return choice;
}

//�V�K�o�^
int show_register(void) {

}