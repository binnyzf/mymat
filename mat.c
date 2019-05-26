
#include "mat.h"
/**
 * Copys one matrix to another*/
void arrcpy(mat *from,mat *to){
    int i, j;
    for (i = 0; i < SIZE;i++){
        for (j = 0; j < SIZE;j++) {
            (*to)[i][j]= (*from)[i][j];
        }
    }
}
/*sets the temp for command execution*/
void set_temp(int i, int j, mat **arrlist){
    switch (i){
        case 0:
            temp_p.first_param=arrlist[j];
        case 1:
            temp_p.second_param=arrlist[j];
        case 2:
            temp_p.result=arrlist[j];
        default:
            NULL;
    }
}


/**
 * Prints a matrix in tab form
 * */
void print_mat()
{
    int i, j;
    mat* a;
    a = temp_p.first_param;
    for (i = 0; i < SIZE; ++i)
    {
        for (j = 0; j < SIZE; ++j)
        {
            printf("%f\t", (*a)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Filles in a matrix then prints its contents*/
void read_mat() {
    char r[2] = ",";
    int i=0, j=0;
    mat *a;
    a= temp_p.first_param;
    scommand = strtok(scommand,r);
    while (i < SIZE && scommand != NULL) {
        while (j < SIZE) {
            if (scommand == NULL) { break; }
            if (cleanCOMM(scommand) == FAIL) {
                error(CHARINVALID,scommand);
                /*found incompatible data types in arguments from user*/
                initializeMAT(*a); break; }
            sscanf(scommand,"%le",&(*a)[i][j]);
            scommand = strtok(NULL, r);
            j++;
        }
        j = 0;
        i++;
    }
    if(scommand!=NULL){
        error(PARAMSOVER,scommand);/*parameters over 16*/
        initializeMAT(*temp_p.first_param);
    }
    else {
        print_mat();
    }
}
/**Exits  the program**/
void stop()
{
    fprintf(stdout,"Goodbye hope to see you soon\n");
    exit(0);
}

/**
 * Adds a matrix to another and stores the result int he third
 * */

void add_mat()
{
    int i, j;
    mat* a, * b, * c;
    a = temp_p.first_param;
    b = temp_p.second_param;
    c = &mat_temp;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            (*c)[i][j] = ((*a)[i][j] + (*b)[i][j]);
        }
    }
    arrcpy(c,temp_p.result);
    temp_p.first_param = temp_p.result;
    print_mat();
}
/**
 * Transpose of a matrix is obtained by changing rows to columns and columns to rows.
 * In other words, transpose of A[][] is obtained by changing A[i][j] to A[j][i].*/
void trans_mat()
{
    int i, j;
    mat *a,*b;
    a = temp_p.first_param;
    b = temp_p.second_param;
    for (i = 0; i < SIZE;i++){
        for (j = 0; j < SIZE;j++) {
            mat_temp[j][i]=(*a)[i][j];
        }
    }
    arrcpy(&mat_temp,b);
    temp_p.first_param = temp_p.second_param;
    print_mat();
}

/**
 * Adds a matrix to another and stores the result in the third
 * */

void sub_mat()
{
    int i,j;
    mat *a,*b,*c;
    a = temp_p.first_param;
    b = temp_p.second_param;
    c = temp_p.result;
    for (i=0; i < SIZE; i++)
    {
        for (j=0; j < SIZE; j++)
        {
            mat_temp[i][j] = ((*a)[i][j] - (*b)[i][j]);
        }
    }
    arrcpy(&mat_temp,c);
    temp_p.first_param = temp_p.result;
    print_mat();
}

/**
 * Multiplly's each element of a by number b and stores the product in c*/
void mul_scalar()
{
    int b,i,j;
    mat* a, * c;
    b = scalar_num;
    a = temp_p.first_param;
    c = temp_p.result;
    if(a!=NULL) {
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                mat_temp[i][j] = ((*a)[i][j] * b);
            }
        }
    }
    arrcpy(&mat_temp,c);
    temp_p.first_param = temp_p.result;
    print_mat();
}
/**
 * Mulltiplys  a matrix to another and stores the result in the third.
 *  The product is calculated by multiplying the rows of a by the columns of b element by element.
 * */

void mul_mat()
{
    int i, j, k;
    float sum = 0;
    mat *a,*b,*c;
    a = temp_p.first_param;
    b = temp_p.second_param;
    c = temp_p.result;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            for (k = 0; k < SIZE; k++)
            {
                sum += ((*a)[i][k]) * ((*b)[k][j]);
            }

            mat_temp[i][j] = sum;
            sum = 0;
        }
    }
    arrcpy(&mat_temp,c);
    temp_p.first_param = temp_p.result;
    print_mat();
}