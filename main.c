#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//For Reserved Words
const char* reservedWords[]={"const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};

//For Reserved Special Symbols
const char specialSymbols[]={'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':'};

int lexoutput;
int codegenoutput;
int vmoutput;

int errorCount;

//Given enum for internal representation
typedef enum {
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym , elsesym
} token_type;
const char *lexSym[] = { "", "nulsym", "identsym", "numbersym", "plussym", "minussym",
    "multsym",  "slashsym", "oddsym", "eqsym", "neqsym", "lessym", "leqsym",
    "gtrsym", "geqsym", "lparentsym", "rparentsym", "commasym", "semicolonsym",
    "periodsym", "becomessym", "beginsym", "endsym", "ifsym", "thensym",
    "whilesym", "dosym", "callsym", "constsym", "varsym", "procsym", "writesym",
    "readsym" , "elsesym"};
//struct used to contain all tokens details
typedef struct {
    token_type tokenID;
    int numberValue;
    char name[12];
}tokenStruct;

 tokenStruct lexList[5000];
 int lexListIndex =0 ;


int main (int argc, char *argv[]){

	//init lext list
	for (int i =0; i<5000;i++){
		lexList[i].tokenID =0;

	}

	//file i/o
	FILE *infile;
	FILE 	*outfile;



	infile = fopen(argv[1],"r");

	outfile = fopen("lexout.txt", "w");

	


	int i,j=0,k=0;

	int erroCatcher,c,coment,lAhead;

	infile = fopen(argv[1],"r");

	c = fgetc(infile);

	while((c=fgetc(infile)) !=EOF){
            printf("%c", c);
        }

	while(c != EOF){

		if(c == ' ' || c == '\t' || c == '\n' ){
			c = fgetc(infile);
			lAhead = 0;
			continue;
		}
		if(isalpha(c)){
			char String[12];

			memset(String, 0, sizeof(String));

			int ind = 0;

			String[ind] = c;

			ind++;

			lAhead = 1;

			while(isalpha(c = fgetc(infile)) || isdigit(c)){
				if(ind>10){
					while(isalpha(c = fgetc(infile))|| isdigit(c)){

					}
					erroCatcher = 1;
					break;
				}

				String[ind] = c;
				ind++;
			}

			if(erroCatcher == 1){
				erroCatcher = 0;
				continue;
			}

			int rSwitch = -1;

			for(i=0; i<14;i++){
				if(strcmp(String, reservedWords[i]) == 0){
					rSwitch = i;		
				}
			}

			switch(rSwitch){
				case  0:
				lexList[lexListIndex].tokenID = constsym;
				break;

				case  1:
				lexList[lexListIndex].tokenID = varsym;
				break;

				case  2:
				lexList[lexListIndex].tokenID = procsym;
				break;

				case  3:
				lexList[lexListIndex].tokenID = callsym;
				break;

				case  4:
				lexList[lexListIndex].tokenID = beginsym;
				break;
				

				case  5:
				lexList[lexListIndex].tokenID = endsym;
				break;

				case  6:
				lexList[lexListIndex].tokenID = ifsym;
				break;

				case  7:
				lexList[lexListIndex].tokenID = thensym;
				break;

				case  8:
				lexList[lexListIndex].tokenID = elsesym;
				break;

				case  9:
				lexList[lexListIndex].tokenID = whilesym;
				break;

				case  10:
				lexList[lexListIndex].tokenID = dosym;
				break;

				case  11:
				lexList[lexListIndex].tokenID = readsym;
				break;

				case  12:
				lexList[lexListIndex].tokenID = writesym;
				break;

				case  13:
				lexList[lexListIndex].tokenID = oddsym;
				break;

				default:
				lexList[lexListIndex].tokenID = identsym;
				strcpy(lexList[lexListIndex].name, String);
				break;
			}
			lexListIndex++;

		}

		else if(isdigit(c)){
			int num = c - '0';
			int d;
			int location = 1;

			lAhead =1;

			while(isdigit(c = fgetc(infile))){
				if(location > 4){
					while(isdigit(c = fgetc(infile))){

					}
					erroCatcher =1;
					break;
				}

				d = c -'0';
				num = 10*num+d;
				location++;
			}

				if(isalnum(c)){
					while(isalpha(c = fgetc(infile))|| isdigit(c)){
						
					}
					continue;
				}

				if(erroCatcher == 1){
					erroCatcher = 0;
					continue;
				}
			lexList[lexListIndex].tokenID = numbersym;
			lexList[lexListIndex].numberValue = num;
			lexListIndex++;
		}

		else {
			lAhead = 0;
			int specs = -1;
			for(i =0; i<13; i++){
				if(c == specialSymbols[i]){
					specs = i;
				}
			}
			switch(specs){
				case 0:
				lexList[lexListIndex].tokenID = plussym;
				lexListIndex++;
				break;

				case 1:
				lexList[lexListIndex].tokenID = minussym;
				lexListIndex++;
				break;


				case 2:
				lexList[lexListIndex].tokenID = multsym;
				lexListIndex++;
				break;

				case 3:
				c =fgetc(infile);
				lAhead = 1;
				if(c == '*'){
					coment = 1;
					lAhead = 0;
					c = fgetc(infile);
					while(coment == 1){
						if(c == '*'){
							c = fgetc(infile);
							if(c == '/'){
								coment =0;

							}
						}

						else{
							c = fgetc(infile);
						}
					}
				}
				else{
					lexList[lexListIndex].tokenID = slashsym;
					lexListIndex++;
				}
				break;

				case 4:
				lexList[lexListIndex].tokenID = lparentsym;
				lexListIndex++;
				break;

				case 5:
				lexList[lexListIndex].tokenID = rparentsym;
				lexListIndex++;
				break;

				case 6:
				lexList[lexListIndex].tokenID = eqsym;
				lexListIndex++;
				break;

				case 7:
				lexList[lexListIndex].tokenID = commasym;
				lexListIndex++;
				break;

				case 8:
				lexList[lexListIndex].tokenID = periodsym;
				lexListIndex++;
				break;

				case 9:
				c = fgetc(infile);
				lAhead = 1;
				
				if(c == '>'){
					lexList[lexListIndex].tokenID = neqsym;
					lAhead = 0;
				}

				if(c == '='){
					lexList[lexListIndex].tokenID = leqsym;
					lAhead = 0;
				}

				else{
					lexList[lexListIndex].tokenID = lessym;
				}
				lexListIndex++;
				break;

				case 10:
				c = fgetc(infile);
				lAhead =1;

				if(c == '='){
					lexList[lexListIndex].tokenID = geqsym;
					lAhead =0;

				}

				else{
					lexList[lexListIndex].tokenID = gtrsym;
				}

				case 11:
				lexList[lexListIndex].tokenID = semicolonsym;
				lexListIndex ++;
				break;

				case 12:
				c = fgetc(infile);
				if(c == '='){
					lexList[lexListIndex].tokenID = becomessym;
					lexListIndex++;
				}

				else{

				}
				break;

				default:
				printf("PANIC\n");

				break;
				
			}
		}

		if(lAhead == 0){
			c = fgetc(infile);
		}
	}

	fprintf(outfile, "%d", lexList[0].tokenID);

	if(lexList[0].tokenID == 2){
		fprintf(outfile, "|%s",lexList[0].name);
	}
	if(lexList[0].tokenID == 3){
		fprintf(outfile, "|%d",lexList[0].numberValue);
	}

	for(i =1; i < lexListIndex; i++){
		fprintf(outfile, "|%d", lexList[i].tokenID);
		if(lexList[i].tokenID == 2){
			fprintf(outfile, "|%s",lexList[i].name);
		}
		if(lexList[i].tokenID == 3){
			fprintf(outfile, "|%d",lexList[i].numberValue);
		}
	}



 while((c=fgetc(infile)) !=EOF){
            printf("%c", c);
        }
        printf("\n\n");
        fclose(infile);
        
        //...prints out the symbolic representation list!
        
        infile = fopen("lexoutput.txt", "r");
        //prints out variable names in Lexeme List
        for(i=0;i<lexListIndex;i++){
            printf("%s ", lexSym[lexList[i].tokenID]);
            if(lexList[i].tokenID==2){
                printf("%s ", lexList[i].name);
            }
            else if(lexList[i].tokenID==3){
                printf("%d ",lexList[i].numberValue);
            }
        }
        printf("\n\n");

  fclose(infile);
  fclose(outfile);
}