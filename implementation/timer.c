#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

int main(){
	int time_start, time_now;
	int revise = 0;
	float points = 0, points_in_activity;
	char ch;
	int ratio = 0, addtion, subtraction;

	time_start = (int)(clock()/CLOCKS_PER_SEC);
	printf("Please enter former points:");
	scanf("%f", &points);

	while (1)
	{
		if (kbhit()) {
			ch = getch();
			printf("\n%c", ch);
			if (ch == ':'){
				revise = (int)(clock()/CLOCKS_PER_SEC);
				scanf("%d", &ratio);
				points += points_in_activity;
			}
			else if (ch == '+'){
				scanf("%d", &addtion);
				points += addtion;
			}
			else if (ch == '-'){
				scanf("%d", &subtraction);
				points -= subtraction;
			}
		}
		else {
			time_now = (int)(clock()/CLOCKS_PER_SEC);
			points_in_activity = (time_now - time_start - revise) * ratio * 1.0 / 60;
			printf("Current Points:%.1f\r", points + points_in_activity);
		}
		sleep(1);
	}
	return 0;
}