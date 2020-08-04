#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

end() {
	printf("\n\n");
	system("pause");
	system("cls");
}

int scan(FILE* fp) {	//파일 행의 수 반환
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

check(FILE* dfp) {	//done 리스트를 10개 이하로 유지 - move
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

print(FILE* fp) {	//파일 내용 출력 - show
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

add(FILE* lfp) {	//일정 추가
	int mon, day;
	char todo[100];
	printf("월, 일, 할 일 순으로 입력해주세요\n\n> ");
	scanf("%d %d %[^\n]s", &mon, &day, todo);
	if (mon > 12 || day > 31)
		printf("\nERROR!\n날짜가 잘못되었습니다.\n");
	else {
		fprintf(lfp, "%d %d %s\n", mon, day, todo);
		printf("\nSUCCESS!\n등록을 완료했습니다.\n");
	}
	end();
	fclose(lfp);
}

show(FILE* lfp) {	//일정 조회
	FILE* dfp = fopen("done.txt", "a+");
	printf("※ 전체 일정 조회 ※\n\n");
	printf("T O D O\n");
	printf("______________________________________\n");
	printf("   월\t일\t할 일\n");
	print(lfp);
	printf("\nD O N E\n");
	printf("______________________________________\n");
	printf("   월\t일\t할 일\n");
	print(dfp);
	end();
	fclose(lfp);
	fclose(dfp);
}

move(FILE* lfp) {	//일정 완료
	FILE* ltp = fopen("list.tmp", "w");
	FILE* dfp = fopen("done.txt", "a+");
	int n, mon, day, count = 0;
	char todo[100];
	printf("※ 일정 완료 이동 ※\n\n이동할 일정 번호를 입력해주세요.\n\n");
	printf("   월\t일\t할 일\n");
	print(lfp);
	printf("\n> ");
	scanf("%d", &n);
	if (n > scan(lfp))
		printf("\nERROR!\n일정 번호가 잘못되었습니다.\n");
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
		printf("\nSUCCESS!\n이동을 완료했습니다.\n");
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

del(FILE* lfp) {	//일정 삭제
	FILE* tfp = fopen("temp.tmp", "w");
	int mon, day, n, count = 1;
	char todo[100];
	printf("※ 일정 삭제 ※\n\n삭제할 일정 번호를 입력해주세요.\n\n");
	printf("   월\t일\t할 일\n");
	print(lfp);
	printf("\n> ");
	scanf("%d", &n);
	if (n > scan(lfp))
		printf("\nERROR!\n일정 번호가 잘못되었습니다.\n");
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
	printf("\nSUCCESS!\n삭제를 완료했습니다.\n");
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
		printf("※ TO DO LIST ※\n\n\tMade by. Hermes\n\n");
		printf("1. 일정 추가\n2. 일정 조회\n3. 일정 완료\n4. 일정 삭제\n5. 종료\n\n> ");
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
			printf("\nERROR!\n잘못된 번호입니다.\n");
			end();
		}
	}
	return 0;
}