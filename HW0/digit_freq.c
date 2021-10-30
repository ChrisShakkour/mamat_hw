// 123456789
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

	char str[1000];
	int histogram[10]={0};
	int len;
	int index;

	scanf("%s", str);
	len = strlen(str);
	for(int i=0; i<len ; i++){
		index = str[i]-'0'; 
		if(index >= 0 && index < 10) 
			++histogram[index];
	}

	for(int i=0; i<10; i++)
		printf("%c ", histogram[i]+'0');
	
	printf("\n");
    return 0;
}
