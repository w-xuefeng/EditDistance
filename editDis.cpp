#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define MAX_LENGTH 30

typedef struct String{
	char *content;
	uint32_t length;
}string;

typedef struct Matrix{
	uint32_t row;
	uint32_t col;
	uint32_t **content;
	uint32_t **label;
};


void input_string(char*,char*);

string initString();

uint32_t min(uint32_t,uint32_t);

uint32_t dis(string, string, uint32_t, uint32_t, Matrix);

Matrix editDis(string,string);

void matrixPruint32_t(Matrix);


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


uint32_t min(uint32_t a,uint32_t b){
	return a <= b ? a : b;
}

uint32_t dis(string a, string b, uint32_t i, uint32_t j, Matrix matrix){
	
	if (matrix.label[i][j]==1)
		return matrix.content[i][j];
    printf("calculte (%d,%d)\n", i,j);
	uint32_t distance;
	if(i == 0){
		distance=j;

	}else if(j == 0){
		distance=i;
	}else{
		distance=min(
					min(
						dis(a, b, i-1, j-1,matrix) + (a.content[i-1] == b.content[j-1] ? 0 : 1),
						dis(a, b, i, j-1,matrix) + 1
					   ),
					dis(a, b, i-1, j,matrix) + 1
				);		

	}
	matrix.content[i][j]=distance;
	matrix.label[i][j]=1;
	return distance;
}



Matrix editDis(string a,string b){

	Matrix matrix;

	uint32_t i,j;
	
	matrix.row = a.length+1; // [0, a.length] [0,matrix.row)
	matrix.col = b.length+1;

	matrix.content = (uint32_t **)malloc( sizeof(uint32_t*) * matrix.row);
	matrix.label   = (uint32_t **)malloc( sizeof(uint32_t*) * matrix.row);

	for (i = 0; i < matrix.row; ++i){
		matrix.content[i] = (uint32_t *) malloc( sizeof(uint32_t) * matrix.col);
		matrix.label[i] = (uint32_t *) calloc(  matrix.col, sizeof(uint32_t));
	}	

	uint32_t distance= dis(a,b, matrix.row-1, matrix.col-1, matrix);
	printf("distance is %d", distance);

	return matrix;

}

void matrixPruint32_t(Matrix matrix){

	for (uint32_t i = 0; i < matrix.row; i++){
		for (uint32_t j = 0; j < matrix.col; j++){
			printf("%d\t",matrix.content[i][j]);	
		}
		printf("\n");
	}
}

int main(uint32_t argc, char const *argv[]){

	string a = initString();
	string b = initString();	

	Matrix matrix;

	input_string(a.content,b.content);

	a.length = strlen(a.content);
	b.length = strlen(b.content);

	matrix =  editDis(a,b);

	printf("\n");

	printf("The Matrix of  %s and %s is :\n", a.content, b.content);

	matrixPruint32_t(matrix);

	printf("\n");

	printf("The Edite Distance of %s and %s is :%d\n", a.content, b.content, matrix.content[matrix.row-1][matrix.col-1]);

	free(a.content);
	free(b.content);
	uint32_t i,j;
	for (i = 0; i < matrix.row; i++){
		free(matrix.content[i]);	
	}
	free(matrix.content);
	return 0;
}
