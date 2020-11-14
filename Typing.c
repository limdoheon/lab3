/* 타자 연습 프로그램
 * Typing.c*/
#include<stdio.h>
#include<time.h>
#include<string.h>
struct result{
	int input_len;
	int incorrect;
	float time;
};
struct result practice(char *sen){
	time_t start_time, end_time;
	char input[1024];
	struct result res;
	int check = 0;
	puts(sen);
	start_time = time(NULL);
	scanf("%[^\n]s", input);
	res.input_len = strlen(input);
	end_time = time(NULL);
	for(int i = 0 ; i< strlen(sen);i++){
		if(sen[i] != input[i]){
			check++;
		}
	}
	res.incorrect = check;
	printf("오타수 : %d\n",check);
	res.time = (float)(end_time - start_time);
	return res;
}
int main() {
	struct result first, second,third;
	float t_time;
	int total;
	char first_sen[] = "Welcome to Newyork";
	char second_sen[] = "One , Two , Three , Four";
	char third_sen[] = "Postmalone : Goodbye";

	first = practice(first_sen);
	getchar();
	second = practice(second_sen);
	getchar();
	third = practice(third_sen);

	int text_len = strlen(first_sen) + strlen(second_sen) + strlen(third_sen);
	int first_total = first.input_len - first.incorrect;
	int second_total = second.input_len - second.incorrect;
	int third_total = third.input_len - third.incorrect;

	total = first_total + second_total + third_total;
	t_time = first.time + second.time + third.time;
	printf("분당 타자수 : %.2f\n",(float)total / t_time * 60.0);
	return 0;
}
