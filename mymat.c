#include "mat.h"


/**
 * Maman 22
 * Binny Friedman 315634949
 * */

struct
{
    char name[9];
} mats[] = {
        {"MAT_A"},
        {"MAT_B"},
        {"MAT_C"},
        {"MAT_D"},
        {"MAT_E"},
        {"MAT_F"},
        {"NULL"}
};

/*stuct for validating command prompts*/
struct
{
    char* name;
    int params_num;
    int type;
    void (*func)(void);
} cmd[] = {
        {"read_mat",17,MATDOUBLES, read_mat},
        {"print_mat",1,ONLYMAT,print_mat},
        {"add_mat",3,ONLYMAT, add_mat},
        {"sub_mat",3,ONLYMAT, sub_mat},
        {"mul_mat",3,ONLYMAT, mul_mat},
        {"stop",ZERO,ZERO,stop},
        {"mul_scalar",3,MULSCALAR, mul_scalar},
        {"trans_mat",2,ONLYMAT, trans_mat},
        {"not_valid",ZERO,ZERO, NULL}
};


/*initializes all members of a matrix to zero*/
void initializeMAT(mat a)
{

    int i, j;
    for (i = ZERO; i < SIZE; ++i)
    {
        for (j = ZERO; j < SIZE; ++j)
        {
            a[i][j] = ZERO;
        }
    }
}
/*Reset to temp params*/
void freeTemp(){
    initializeMAT(mat_temp);
    scommand =NULL;
}



/*checks for invalid chars among the read mat command params*/
int cleanCOMM(char *str){
    int i=ZERO;
    while (i<strlen(str)){
        if(isdigit(str[i])==ZERO&&str[i]!='.'&&str[i]!='\n'&&str[i]!='-'){
            /*found an invalid char*/
            return FAIL;
        }
        i++;
    }
    return OK;
}

/*compares the token extracted from user command against mat DB
 * and returns its position id*/
int findMAT(char *mat_name ){
    int j;
    for (j = ZERO; j<6;)
    {
        if (strcmp(mat_name, mats[j].name) == ZERO){
            break;
        }
        j++;
    }
    if (j ==6)
    {
        return FAIL;
    }
    return j;
}


/*cleans user prompt from all extra blanks replacing to , where necessary*/
int removeAllBlanks(char * str)
{
    int i, j,count=ZERO;
    int len = strlen(str);

    for(i=ZERO; i<len; i++)
    {
        /*skips the first string aka command*/

        /*after command*/
        if(str[i] == ' '||str[i]=='\t'||str[i]=='\n')
        {
            for(j=i; j<len; j++)
            {
                str[j] = str[j+1];
            }
            len--;
            /* If a character is removed then make sure i doesn't increments*/
            i--;
        }
        if(str[i]==','&&i<len-1){/*consecutive ,, in command*/
            if(str[i+1]==','){
                return error(ASTROV,str);
            }
        }
        if(count<2&&(str[i] != ' '&&str[i]!='\t'&&str[i]!='\n')){
            if(count==ZERO){
                while (str[i] != ' '&&str[i]!='\t'&&str[i]!='\n'){
                    i++;
                }
                if(strncmp(str,"stop",4)==0) return OK;
                count++;
                str[i]= ',';
            } else{
                count++;
                if(str[i]==','){
                    return error(LEADASM,str);
                }
            }
        }
    }
    if(str[len-1]==',')return error(ENDAST,str);

    str[len]= '\0';/*seal the last char as NULL*/
    return OK;
}


/*main validation to user command input*/
int validate(mat*  arrlist[],char* command)
{
    int first=FAIL,second=FAIL,third=FAIL;
    int chain [3];
    char *token; /*command*/
    char *args = NULL;/*parameters*/
    const char r[2] = ",";
    const char q[2] = "\0";/*in case of read_mat we send all params to func*/
    int i,p;

    chain[0]=first;/*makes sure unauthorized commands are not sent my mistake*/
    chain[1]=second;
    chain[2]=third;
    token = strtok(command,r);
    for (i = ZERO; cmd[i].func != NULL; )
    {
        if (strncmp(token, cmd[i].name,strlen(cmd[i].name)) == ZERO){
            comm_num=i;
            break;/*command is found */
        }
        i++;
    }


    if (cmd[i].func == NULL)/*no such command*/
    {
        return error(UNDEFCOMM,token);
    }

    /**
     * if the command has no parameters aka stop
     * */
    if(cmd[i].params_num==ZERO){
        args = strtok(NULL,r);
        if(args==NULL){
            (*(cmd[i].func))();
            return OK;
        }
        return error(PARAMSOVER,args);
    }

    /**
     * if the command is read mat
     * */
    if (cmd[i].type==MATDOUBLES)
    {
        args= strtok(NULL, r);
        first = findMAT(args);
        if(first==FAIL) {/*no such mat*/
            return error(UNDEFMAT,args);
        }
        scommand = strtok(NULL,q);
        temp_p.first_param=arrlist[first];
        (*(cmd[i].func))();/*call to function*/
        return OK;
    }

    /*case add_mat,sub mat,mul_mat,trans_mat,print_mat,mul_scalar:*/
    if(cmd[i].type==ONLYMAT||cmd[i].type==MULSCALAR) {
        p=ZERO;
        args= strtok(NULL,r);
        while (p<=cmd[i].params_num&&args!=NULL){
            if(cmd[i].type==MULSCALAR&&p==1){
                if(cleanCOMM(args)==FAIL){
                    return error(CHARINVALID,args);}
                scalar_num =strtol(args,(char**)args+5,10);
                args = strtok(NULL,r);
                p++;
            }
            chain[p] = findMAT(args);
            if(chain[p]==FAIL){
                return error(UNDEFMAT,args);
            }
                set_temp(p, chain[p], arrlist);
                args= strtok(NULL,r);
                /*using temp global pointers allows us to use void
 *               func and call them dynamically */
                p++;
        }
        /*Checks all possible error causes up to this point*/
        if(p<cmd[i].params_num||args!=NULL) {
            if (args == NULL) {
                return error(SHORTPARAM,args);
            }

            if(args!=NULL){
                return error(PARAMSOVER,args);
            }
        } else {
            (*(cmd[i].func))();
            return OK;
        }

    }/*To not let uncaught errors effect the running of the program*/
    return error(FAIL,args);
}




int main(void) {
    char command[MAXINPUT];
    char *comm;
    int ct=ZERO;
    mat *A=calloc(1,sizeof(mat)),
    *B=calloc(1,sizeof(mat)),
    *C=calloc(1,sizeof(mat)),
    *D=calloc(1,sizeof(mat)),
    *E=calloc(1,sizeof(mat)),
    *F=calloc(1,sizeof(mat));
    mat* arrList[6];
    arrList[0]= A;
    arrList[1]=B;
    arrList[2]=C;
    arrList[3]=D;
    arrList[4]=E;
    arrList[5]=F;

    welcome();
    for(;;) {
        if (fgets(command, MAXINPUT, stdin) != NULL) {
            comm = command;
            if (removeAllBlanks(comm) != FAIL) {
                if(validate(arrList,comm)!=FAIL){
                    printf("your command %s was successful\n", cmd[comm_num].name);
                } else{
                    ct++;
                }
            }
            if (ct==5){ syntax(); ct=ZERO;}
            freeTemp();
            printf("Enter another command\n");
        }
    }
}
