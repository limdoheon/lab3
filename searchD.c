/*searchD.c*/
/*디렉토리 탐색 프로그램 */

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>

void printDir(char * dirName){
	DIR *pdir;
	struct dirent *pde;
	int i = 0;
	char buff[1024];
	if (( pdir = opendir(dirName)) < 0){
		perror("opendir");
		exit(1);
	}
	printf("%s:\n",dirName);
	while((pde = readdir(pdir)) !=NULL){
		printf("%20s " ,pde -> d_name);
		if(++i % 3 == 0)
			printf("\n");
	}
	printf("\n\n\n");
	closedir(pdir);
}

void readDir(char *dirName){
	DIR *pdir;
	struct dirent *pde;
	int i = 0;
	char buff[1024];
	if ((pdir = opendir(dirName)) < 0){
		perror("opendir");
		exit(1);
	}
	printDir(dirName);
	while ((pde = readdir(pdir)) != NULL){
		if(pde ->d_type == DT_DIR && strcmp(pde -> d_name, ".") && strcmp(pde-> d_name, "..")){
			strcpy(buff, pde->d_name);
			readDir(buff);
		}
	}
	closedir(pdir);
}

int main(){
	DIR *pdir;
	readDir(".");
	return 0;
}
