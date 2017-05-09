#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 30

typedef struct String{
	char *content;
	int length;
}string;

typedef struct Matrix{
	int row;
	int col;
	int **content;
}matrix;


void input_string(char*,char*);

string initString();

int min(int,int);

int dis(string, string, int, int);

matrix editDis(string,string);

void matrixPrint(matrix);

string initString(){
	string temp;	
	temp.content = (char *)malloc(sizeof(char)*MAX_LENGTH);
	temp.length = 0;
	return temp;	
}

void input_string(char* a,char* b){

	puts("Input the first string:");
	gets(a);

	puts("Input the second string:");
	gets(b);
	
}


int min(int a,int b){
	return a <= b ? a : b;
}

int dis(string a, string b, int i, int j){

	if(i == 0){

		return j;		

	}else if(j == 0){

		return i;

	}else if(i == 1 && j==1){

		return (a.content[i] == b.content[j]? 0 : 1);

	}else{
		
		return 	min(
					min(
						dis(a, b, i-1, j-1) + (a.content[i] == b.content[j] ? 0 : 1),
						dis(a, b, i, j-1) + 1
						),
					dis(a, b, i-1, j) + 1
				);		

	}

}



matrix editDis(string a,string b){

	matrix Matrix;

	int i,j;
	
	Matrix.row = a.length + 1;
	Matrix.col = b.length + 1;

	Matrix.content = (int **)malloc(sizeof(int)*Matrix.row);

	for (i = 0; i <= Matrix.col; ++i){

		Matrix.content[i] = (int *)malloc(sizeof(int)*Matrix.col);

	}	


	for (i = 0; i < Matrix.row; i++){

		for (j = 0; j < Matrix.col; j++){
			
			Matrix.content[i][j] = dis(a,b,i,j);

		}

	}

	return Matrix;

}

void matrixPrint(matrix Matrix){

	for (int i = 0; i < Matrix.row; i++){

		for (int j = 0; j < Matrix.col; j++){
			
			printf("%d\t",Matrix.content[i][j]);	

		}

		printf("\n");

	}

}

int main(int argc, char const *argv[]){

	string a = initString();
	string b = initString();	

	matrix Matrix;

	input_string(a.content,b.content);

	a.length = strlen(a.content);
	b.length = strlen(b.content);


	Matrix =  editDis(a,b);

	printf("\n");

	matrixPrint(Matrix);

	printf("\n");

	printf("The dis is :%d\n", Matrix.content[Matrix.row-1][Matrix.col-1]);

	return 0;
}
