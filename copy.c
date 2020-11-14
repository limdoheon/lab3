/* copy.c
 * 공유 메모리를 사용한 파일*/

#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SHMSIZE 128
#define SHMNAME "/sh_mem"
#define BUFSIZE 256
#define SOURCE_FILE "ONE.txt"
#define TARGET_FILE "TWO.txt"

int main(){
	int *val;
	struct timespec *tms;
	pid_t pid;
	void *shmaddr;
	int shmd;
	FILE *file;

	if((shmd = shm_open(SHMNAME, O_CREAT | O_RDWR, 0666)) ==-1){
		perror("shm_open");
		exit(1);
	}
	if(ftruncate(shmd, SHMSIZE) !=0){
		perror("ftruncate");
		exit(1);
	}
	if((shmaddr = mmap(NULL, SHMSIZE , PROT_WRITE | PROT_READ , MAP_SHARED ,shmd , 0)) == MAP_FAILED){
		perror("mmap");
		exit(1);
	}

	pid = fork();
	if(pid ==0){
		if((file = fopen(SOURCE_FILE, "r")) == NULL){
			perror("fopen");
			exit(1);
		}
		char read_buf[BUFSIZE];

		fgets(read_buf, BUFSIZE , file);
		strcpy((char *) shmaddr, read_buf);
		fclose(file);
	}
	else if (pid > 0){
		sleep(1);
		file = fopen(TARGET_FILE, "w");
		fputs(shmaddr, file);

		if(shm_unlink(SHMNAME) == -1){
			perror("shm_unlink");
			exit(1);
		}
	}
	else{
		perror("fork");
		exit(1);
	}
	close(shmd);

	return 0;
}

