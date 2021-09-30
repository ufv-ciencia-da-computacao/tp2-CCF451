#include <stdio.h>
#include<stdio.h>

int main(){
	unsigned long long x = 1;	
	printf("%d\n", __builtin_clzll((x << 64)));
	return 0;
}
