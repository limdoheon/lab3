/* 시스템 함수 실행 프로그램
 * SystemF.c*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void main(int argc, char *argv[]){
	if (argc < 2) {
		fprintf(stderr, "Usage : file_append command\n");
		exit(1);
	}
	execl("/bin/ls" , argv[1],argv[2],(char *)0);
	perror("execl failed to rul ls");
	exit(1);
}

