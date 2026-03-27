#include<stdio.h>
int main(){
	int size, i,search;
	if(scanf("%d", &size)!=1) return 1;
	int arr[size];
	for(i=0; i<size; i++){
		if(scanf("%d", &arr[i])!=1) return 1;
	}
	if(scanf("%d", &search)!=1) return 1;
	for(i=0; i<size; i++){
		if (arr[i]==search){
			printf("found at position %d\n",i);
			return 0;
		}
	}
	printf("%d not found\n",search);
	return 0;
	
}
