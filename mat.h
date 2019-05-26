

#ifndef TRYOUTS_MAT_H
#define TRYOUTS_MAT_H

#endif


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#define SIZE 4
#define MATDOUBLES 34
#define ONLYMAT 33
#define MULSCALAR 32
#define ZERO 0
#define OK 1
#define FAIL -1
#define MAXINPUT 256


/*Error handlers*/
#define CHARINVALID 45
#define PARAMSOVER 46
#define SHORTPARAM 47
#define UNDEFMAT 48
#define UNDEFCOMM 49
#define ASTROV 50
#define LEADASM 51
#define ENDAST 52



double mat_temp[SIZE][SIZE];
typedef double mat[SIZE][SIZE];

char *scommand;
int comm_num;
double mat_temp[SIZE][SIZE];
void read_mat(void);
void print_mat(void);
void add_mat(void);
void sub_mat(void);
void mul_mat(void);
void mul_scalar(void);
void trans_mat(void);
void stop(void);
int validate(mat* [] ,char* command);
int cleanCOMM(char *str);
void freeTemp(void);
void arrcpy(mat *from,mat *to);
void initializeMAT(mat a);
void set_temp(int i, int j, mat **arrlist);
int error(int, char*);
void syntax();
void welcome();


int scalar_num;


typedef struct tnode{
    mat *first_param;
    mat *second_param;
    mat *result;
}params;

params temp_p;
