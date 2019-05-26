
#include "mat.h"
/**
 * Error handling all sanarios available
 * */
int error(int err_num,char* str){
    switch (err_num){
        case CHARINVALID:
            fprintf(stderr,"There is an invalid char %s among your parameters \n",str);
            break;
        case PARAMSOVER:
            fprintf(stderr, "Too many parameters \n" );
            break;
        case SHORTPARAM:
            fprintf(stderr,"Not enough params\n");
            break;
        case UNDEFCOMM:
            fprintf(stderr, "Command not valid %s\n", str);
            break;
        case LEADASM:
            fprintf(stderr, "Mat name has leading , \n");
            break;
        case UNDEFMAT:
            fprintf(stderr, "mat name not valid %s\n", str);
            break;
        case ASTROV:
            fprintf(stderr,"Consecutive ,, in your command please try again\n");
            break;
        case ENDAST:
            fprintf(stderr,"Warning INVALID ending \",\" in your command %s\n",str);
            break;
        default:
            fprintf(stderr,"Uncaught error check your command:%s against syntax\n",str);
            break;



    }
    return FAIL;
}
/*
 * reminder of syntax
 * called when 5 fails occurs on user input*/
void syntax(){
    fprintf(stderr,"Please Pay attention to the syntax\n"
                   "correct syntax \n"
                   "|\t|\t|\n"
                   "V\tV\tV\n"
                   "COMMAND_NAMES_ARE_IN_ONE_WORD => THEN HIT SPACE\n"
                   "MAT_(A-F)----(MUST BE ALL CAPS)\n"
                   "list of all available operations:\n"
                   "read_mat\n"
                   "print_mat\n"
                   "add_mat\n"
                   "sub_mat\n"
                   "mul_mat\n"
                   "mul_scalar\n"
                   "trans_mat\n"
                   "stop\n"
                   "see commands full parameters above\n"
                   "Thank you\n\n\n");
}

void welcome(){


    printf(
            "************************************************************************\n"
            "******************* Welcome to the Maman 22 ****************************\n"
            "************************************************************************\n"
            "           you can enter commands to operates on matrix\n"
            "              List and syntax of possible commands:\n\n"
            "Enter your command as shown below \n");
    printf("* operation to perform* *space* parameters delim by , \n"
           "read_mat MAT_A,53,78,-978,3.1415,...\t(up to 16 params)\n"
           "print_mat MAT_B   *syntax* -> MAT[A->F]\n"
           "add_mat mat_b,mat_c,MAT_F  \tsyntax*-> mat[a]+mat[b]=mat[c]\n"
           "sub_mat       same as add_mat       \n"
           "mul-mat       same as add_mat       \n"
           "trans_mat MAT_A,MAT_E   transpose the matrix (can be the same one)\n"
           "stop   \tto stop TYPE ONLY stop WITHOUT ANY PARAMS\n\n\n"
           "please enter your command\n");
}