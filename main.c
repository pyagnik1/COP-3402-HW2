#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//For Reserved Words
const char* reservedWords[]={"const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};


const char spcialSymbols[]={'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':'};

int lexoutput;
int codegenoutput;
int vmoutput;

int errora;

typedef enum {
    nulsym = 1, identsym, numsym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym , elsesym
} token_type;
const char *lexSym[] = { "", "nulsym", "identsym", "numsym", "plussym", "minussym",
    "multsym",  "slashsym", "oddsym", "eqsym", "neqsym", "lessym", "leqsym",
    "gtrsym", "geqsym", "lparentsym", "rparentsym", "commasym", "semicolonsym",
    "periodsym", "becomessym", "beginsym", "endsym", "ifsym", "thensym",
    "whilesym", "dosym", "callsym", "constsym", "varsym", "procsym", "writesym",
    "readsym" , "elsesym"};

typedef struct {
    token_type token;
    int numValue;
    char name[12];
}tokenStruct;

 tokenStruct List[5000];
 int Listidx =0 ;


int main (int argc, char *argv[]){

		int i = 0;

    int a;
    for(a=0;a<5000;a++){
        List[a].token=0;
    }
    

    FILE* infile;
    FILE* outfile;
    


    infile = fopen("input.txt", "r");
    outfile = fopen("lexoutput.txt", "w");

	


    int j=0,k=0;
   
    int errorCatcher;
    
    int c;

    int coment=0;

    int peakAheah=0;
			printf("Source Program:\n");
		  while((c=fgetc(infile)) !=EOF){
          printf("%c", c);
      }



    infile=fopen("input.txt","r");
    c=fgetc(infile);

    while(c!=EOF){
        if(c==' '||c=='\t'||c=='\r' ||c=='\n'){
            c=fgetc(infile);
            peakAheah=0;
            continue;
        }
      
        if(isalpha(c)){
            char String[12];
            memset(String, 0, sizeof String);
            
            int idx=0;
            String[idx]=c;

            idx++;
            peakAheah=1;
          
            while(isalpha(c=fgetc(infile))||isdigit(c)){
                if(idx>10){
                

                    while (isalpha(c=fgetc(infile))||isdigit(c)) {

                    }
                    errorCatcher=1;

                    break;
                }
                String[idx]=c;
                idx++;
            }

          
            if(errorCatcher==1) {
                errorCatcher=0;
                continue;
            }

            int rSwitch=-1;

            for(i=0; i<14;i++){
                if(strcmp(String, reservedWords[i])==0){
                    rSwitch=i;
                }
            }
            switch(rSwitch){

          
                case 0:
                    List[Listidx].token = constsym;
                    break;
          
                case 1:
                    List[Listidx].token = varsym;
                    break;
            
                case 2:
                    List[Listidx].token = procsym;
                    break;
              
                case 3:
                    List[Listidx].token = callsym;
                    break;
               
                case 4:
                    List[Listidx].token = beginsym;
                    break;
            
                case 5:
                    List[Listidx].token = endsym;
                    break;
             
                case 6:
                    List[Listidx].token = ifsym;
                    break;
               
                case 7:
                    List[Listidx].token = thensym;
                    break;
              
                case 8:
                    List[Listidx].token = elsesym;
                    break;
               
                case 9:
                    List[Listidx].token = whilesym;
                    break;
           
                case 10:
                    List[Listidx].token = dosym;
                    break;
       
                case 11:
                    List[Listidx].token = readsym;
                    break;
    
                case 12:
                    List[Listidx].token = writesym;
                    break;
     
                case 13:
                    List[Listidx].token = oddsym;
                    break;

                default:
                    List[Listidx].token = identsym;
                    strcpy(List[Listidx].name,String);
                    break;
            }
            Listidx++;
        }

        else if(isdigit(c)){
            int num=c-'0';
            int d;
            int location=1;

            peakAheah=1;

   
            while(isdigit(c=fgetc(infile))){
                if(location>4){



                    while (isdigit(c=fgetc(infile))) {

                    }
                    errorCatcher=1;

                    break;
                }
                d=c-'0';
                num=10*num+d;
                location++;
            }

            if(isalpha(c)){
         
                while(isalpha(c=fgetc(infile))||isdigit(c)){

                }
                continue;
             }

        
            if(errorCatcher==1) {
                errorCatcher=0;
                continue;
            }

            List[Listidx].token=numsym;
            List[Listidx].numValue=num;
            Listidx++;
        }

       
        else {
            peakAheah=0;
            int spc=-1;
            for(i=0;i<13;i++){
                if(c==spcialSymbols[i]){
                    spc=i;
                }
            }
          
            switch(spc){
             
                case 0:
                    List[Listidx].token = plussym;
                    Listidx++;
                    break;
      
                case 1:
                    List[Listidx].token = minussym;
                    Listidx++;
                    break;

                case 2:
                    List[Listidx].token = multsym;
                    Listidx++;
                    break;


                case 3:
                    c=fgetc(infile);
                    peakAheah=1;
                    if(c=='*'){
                        coment=1;
                        peakAheah=0;
                        c=fgetc(infile);
                        while(coment==1){
                            if(c=='*'){
                                c=fgetc(infile);
                                if(c=='/'){
                                    coment=0;
                                }
                            }
                            else{
                                c=fgetc(infile);
                            }
                        }
                    }
                    else{
                        List[Listidx].token = slashsym;
                        Listidx++;
                    }
                    break;

                case 4:
                    List[Listidx].token = lparentsym;
                    Listidx++;
                    break;

                case 5:
                    List[Listidx].token = rparentsym;
                    Listidx++;
                    break;

                case 6:
                    List[Listidx].token = eqsym;
                    Listidx++;
                    break;

                case 7:
                    List[Listidx].token = commasym;
                    Listidx++;
                    break;

                case 8:
                    List[Listidx].token = periodsym;
                    Listidx++;
                    break;

                case 9:
                    c=fgetc(infile);
                    peakAheah=1;
                    if(c=='>'){
                        List[Listidx].token = neqsym;
                        peakAheah=0;
                    }

                    else if(c=='='){
                        List[Listidx].token = leqsym;
                        peakAheah=0;
                    }

                    else{
                        List[Listidx].token = lessym;
                    }
                    Listidx++;
                    break;

                case 10:
                    c=fgetc(infile);
                    peakAheah=1;
                    if(c=='='){
                        List[Listidx].token = geqsym;
                        peakAheah=0;
                    }

                    else{
                        List[Listidx].token = gtrsym;
                    }
                    Listidx++;
                    break;

                case 11:
                    List[Listidx].token = semicolonsym;
                    Listidx++;
                    break;

                case 12:
                    c=fgetc(infile);
                    if(c == '='){
                        List[Listidx].token = becomessym;
                        Listidx++;
                    }

                    else{

                    }
                    break;

                default:

                    break;
            }
        }

        if(peakAheah==0){
            c=fgetc(infile);
        }

    }

    fprintf(outfile,"%d", List[0].token);
    if(List[0].token==2){
        fprintf(outfile,"|%s", List[0].name);
    }

    else if(List[0].token==3){
        fprintf(outfile,"|%d",List[0].numValue);
    }

    for(i=1;i<Listidx;i++){
        fprintf(outfile,"|%d", List[i].token);
        if(List[i].token==2){
            fprintf(outfile,"|%s", List[i].name);
        }
        else if(List[i].token==3){
            fprintf(outfile,"|%d",List[i].numValue);
        }
    }



        printf("\n");
        infile = fopen("lexoutput.txt", "r");
        while((c=fgetc(infile)) !=EOF){
            printf("%c", c);
        }
        printf("\n\n");
        fclose(infile);
        

        infile = fopen("lexoutput.txt", "r");

			


        for(i=0;i<Listidx;i++){
            printf("%d ", List[i].token);
            if(List[i].token==2){
                printf("%s ", List[i].name);
            }
            else if(List[i].token==3){
                printf("%d ",List[i].numValue);
            }
        }
        printf("\n\n");
        fclose(infile);
    
    

    if(errora==0) {
        printf("No errors found\n\n");
    }
    
    fclose(infile);
    fclose(outfile);
}