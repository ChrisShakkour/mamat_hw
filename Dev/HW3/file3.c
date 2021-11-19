//file3.c
#include <stdio.h>
#include <stdlib.h>
#include "file3.h"
#include "file2.h"
int file3_function(){
	printf("This is file3_function()\n");
	file2_function();
	return 0;
}
