#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

end() {
	printf("\n\n");
	system("pause");
	system("cls");
}

int scan(FILE* fp) {	//���� ���� �� ��ȯ
	fseek(fp, 0, SEEK_SET);
	int mon, day, count = 0;
	char todo[100];
	while (1) {
		mon = -1;
		fscanf(fp, "%d %d %[^\n]s\n", &mon, &day, todo);
		if (mon < 0)
			break;
		count++;
	}
	return count;
}

check(FILE* dfp) {	//done ����Ʈ�� 10�� ���Ϸ� ���� - move
	FILE* dtp = fopen("done.tmp", "w");
	int mon, day;
	char todo[100];
	fscanf(dfp, "%d %d %[^\n]s\n", &mon, &day, todo);
	while (1) {
		mon = -1;
		fscanf(dfp, "%d %d %[^\n]s\n", &mon, &day, todo);
		if (mon < 0)
			break;
		fprintf(dtp, "%d %d %s\n", mon, day, todo);
	}
	fclose(dtp);
	fclose(dfp);
	remove("done.txt");
	rename("done.tmp", "done.txt");
}

print(FILE* fp) {	//���� ���� ��� - show
	int mon, day, num = 1;
	char todo[100];
	while (1) {
		mon = -1;
		fscanf(fp, "%d %d %[^\n]s\n", &mon, &day, todo);
		if (mon < 0)
			break;
		printf("%d. %d\t%d\t%s\n", num, mon, day, todo);
		num++;
	}
}

add(FILE* lfp) {	//���� �߰�
	int mon, day;
	char todo[100];
	printf("��, ��, �� �� ������ �Է����ּ���\n\n> ");
	scanf("%d %d %[^\n]s", &mon, &day, todo);
	if (mon > 12 || day > 31)
		printf("\nERROR!\n��¥�� �߸��Ǿ����ϴ�.\n");
	else {
		fprintf(lfp, "%d %d %s\n", mon, day, todo);
		printf("\nSUCCESS!\n����� �Ϸ��߽��ϴ�.\n");
	}
	end();
	fclose(lfp);
}

show(FILE* lfp) {	//���� ��ȸ
	FILE* dfp = fopen("done.txt", "a+");
	printf("�� ��ü ���� ��ȸ ��\n\n");
	printf("T O D O\n");
	printf("______________________________________\n");
	printf("   ��\t��\t�� ��\n");
	print(lfp);
	printf("\nD O N E\n");
	printf("______________________________________\n");
	printf("   ��\t��\t�� ��\n");
	print(dfp);
	end();
	fclose(lfp);
	fclose(dfp);
}

move(FILE* lfp) {	//���� �Ϸ�
	FILE* ltp = fopen("list.tmp", "w");
	FILE* dfp = fopen("done.txt", "a+");
	int n, mon, day, count = 0;
	char todo[100];
	printf("�� ���� �Ϸ� �̵� ��\n\n�̵��� ���� ��ȣ�� �Է����ּ���.\n\n");
	printf("   ��\t��\t�� ��\n");
	print(lfp);
	printf("\n> ");
	scanf("%d", &n);
	if (n > scan(lfp))
		printf("\nERROR!\n���� ��ȣ�� �߸��Ǿ����ϴ�.\n");
	else {
		fseek(lfp, 0, SEEK_SET);
		while (n != count) {
			mon = -1;
			fscanf(lfp, "%d %d %[^\n]s\n", &mon, &day, todo);
			if (mon < 0)
				break;
			count++;
		}
		fprintf(dfp, "%d %d %s\n", mon, day, todo);
		printf("\nSUCCESS!\n�̵��� �Ϸ��߽��ϴ�.\n");
		fseek(lfp, 0, SEEK_SET);
		while (1) {
			mon = -1;
			fscanf(lfp, "%d %d %[^\n]s\n", &mon, &day, todo);
			if (mon < 0)
				break;
			if (n != count)
				fprintf(ltp, "%d %d %s\n", mon, day, todo);
			count++;
		}
	}
	fseek(dfp, 0, SEEK_SET);
	if (10 < scan(dfp)) {
		fseek(dfp, 0, SEEK_SET);
		check(dfp);
	}
	else
		fclose(dfp);
	end();
	fclose(lfp);
	fclose(ltp);
	remove("list.txt");
	rename("list.tmp", "list.txt");
}

del(FILE* lfp) {	//���� ����
	FILE* tfp = fopen("temp.tmp", "w");
	int mon, day, n, count = 1;
	char todo[100];
	printf("�� ���� ���� ��\n\n������ ���� ��ȣ�� �Է����ּ���.\n\n");
	printf("   ��\t��\t�� ��\n");
	print(lfp);
	printf("\n> ");
	scanf("%d", &n);
	if (n > scan(lfp))
		printf("\nERROR!\n���� ��ȣ�� �߸��Ǿ����ϴ�.\n");
	else {
		fseek(lfp, 0, SEEK_SET);
		while (1) {
			mon = -1;
			fscanf(lfp, "%d %d %[^\n]s\n", &mon, &day, todo);
			if (mon < 0)
				break;
			if (n != count)
				fprintf(tfp, "%d %d %s\n", mon, day, todo);
			count++;
		}
	}
	printf("\nSUCCESS!\n������ �Ϸ��߽��ϴ�.\n");
	end();
	fclose(lfp);
	fclose(tfp);
	remove("list.txt");
	rename("temp.tmp", "list.txt");
}

int main() {
	system("title To Do List");
	system("color 0b");
	int n;
	while (1) {
		FILE* lfp = fopen("list.txt", "a+");
		printf("�� TO DO LIST ��\n\n\tMade by. Hermes\n\n");
		printf("1. ���� �߰�\n2. ���� ��ȸ\n3. ���� �Ϸ�\n4. ���� ����\n5. ����\n\n> ");
		scanf("%d", &n);
		system("cls");
		switch (n) {
		case 1:
			add(lfp);
			break;
		case 2:
			show(lfp);
			break;
		case 3:
			move(lfp);
			break;
		case 4:
			del(lfp);
			break;
		case 5:
			fclose(lfp);
			exit(1);
		default:
			printf("\nERROR!\n�߸��� ��ȣ�Դϴ�.\n");
			end();
		}
	}
	return 0;
}