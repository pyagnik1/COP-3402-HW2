#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//For Reserved Words
const char* reservedWords[] = {"const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd", "{", "}"};


const char spcialSymbols[] = {'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':', '{', '}'};

int lexoutput;
int codegenoutput;
int vmoutput;

int errora;

typedef enum {
  nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6,
  slashsym = 7, oddsym = 8, eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
  gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17,
  semicolonsym = 18, periodsym = 19, becomessym = 20, lbracesym = 21, rbracesym = 22,
  ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28,
  varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33
} token;
const char *lexSym[] = { "", "nulsym", "identsym", "numbersym", "+", "-",
                         "*",  "/", "odd", "=", "!=", "<=", "<",
                         ">", ">=", "(", ")", ",", ";",
                         ".", ":=", "{", "}""begin", "end", "if", "then",
                         "while", "do", "call", "const", "var", "procedure", "write",
                         "read" , "else"
                       };

typedef struct {
  token token;
  int numValue;
  char name[12];
  
} tokenStruct;

tokenStruct List[5000];
int Listidx = 0 ;


int main (int argc, char *argv[]) {

  int i = 0;

  int a;
  for (a = 0; a < 5000; a++) {
    List[a].token = 0;
  }


  FILE* infile;
  FILE* outfile;



  infile = fopen("input.txt", "r");
  outfile = fopen("lexoutput.txt", "w");




  int j = 0, k = 0;

  int errorCatcher;

  int ch;

  int coment = 0;

  int peakAheah = 0;
  printf("Source Program:\n");
  while ((ch = fgetc(infile)) != EOF) {
    printf("%c", ch);
  }



  infile = fopen("input.txt", "r");
  ch = fgetc(infile);

  while (ch != EOF && errora == 0) {
		//remove spaces
    if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
      ch = fgetc(infile);
      peakAheah = 0;
      continue;
    }

    if (isalpha(ch)) {
      char String[12];
      memset(String, 0, sizeof String);

      int idx = 0;
      String[idx] = ch;

      idx++;
      peakAheah = 1;

      while (isalpha(ch = fgetc(infile)) || isdigit(ch)) {
        if (idx > 10) {

          errorCatcher = 1;
          printf("\nError Var name is too long\n");
          return 0;
        }
        String[idx] = ch;
        idx++;
      }


      if (errorCatcher == 1) {
        errorCatcher = 0;
        continue;
      }

      int reservedWordsSwitch = -1;

      for (i = 0; i < 14; i++) {
        if (strcmp(String, reservedWords[i]) == 0) {
          reservedWordsSwitch = i;
        }
      }
      switch (reservedWordsSwitch) {


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
          strcpy(List[Listidx].name, String);
          break;
      }
      Listidx++;
    }

    else if (isdigit(ch)) {
      int num = ch - '0';
      int di;
      int location = 1;

      peakAheah = 1;


      while (isdigit(ch = fgetc(infile))) {
        if (location > 4) {
          printf("Error Number too long.\n");


          while (isdigit(ch = fgetc(infile))) {

          }
          errorCatcher = 1;
          printf("Error found\n");
          return 0;

          break;
        }
        di = ch - '0';
        num = 10 * num + di;
        location++;
      }

      if (isalpha(ch)) {

        printf("Error Variable does not start with letter.\n");

      }


      if (errorCatcher == 1) {
        errorCatcher = 0;
        continue;
      }

      List[Listidx].token = numbersym;
      List[Listidx].numValue = num;
      Listidx++;
    }


    else {
      peakAheah = 0;
      int spc = -1;
      for (i = 0; i < 13; i++) {
        if (ch == spcialSymbols[i]) {
          spc = i;
        }
      }

      switch (spc) {

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
          ch = fgetc(infile);
          peakAheah = 1;
          if (ch == '*') {
            coment = 1;
            peakAheah = 0;
            ch = fgetc(infile);
            while (coment == 1) {
              if (ch == '*') {
                ch = fgetc(infile);
                if (ch == '/') {
                  coment = 0;
                }
              }
              else {
                ch = fgetc(infile);
              }
            }
          }
          else {
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
          List[Listidx].token = eqlsym;
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
          ch = fgetc(infile);
          peakAheah = 1;
          if (ch == '>') {
            List[Listidx].token = neqsym;
            peakAheah = 0;
          }

          else if (ch == '=') {
            List[Listidx].token = leqsym;
            peakAheah = 0;
          }

          else {
            List[Listidx].token = lessym;
          }
          Listidx++;
          break;

        case 10:
          ch = fgetc(infile);
          peakAheah = 1;
          if (ch == '=') {
            List[Listidx].token = geqsym;
            peakAheah = 0;
          }

          else {
            List[Listidx].token = gtrsym;
          }
          Listidx++;
          break;

        case 11:
          List[Listidx].token = semicolonsym;
          Listidx++;
          break;

        case 12:
          ch = fgetc(infile);
          if (ch == '=') {
            List[Listidx].token = becomessym;
            Listidx++;
          }


          else {
           
          }
          break;


        default:
					// printf("Error Invalid symbols.\n");
          break;
      }
    }

    if (peakAheah == 0) {
      ch = fgetc(infile);
    }



  }

  fprintf(outfile, "%d", List[0].token);
  if (List[0].token == 2) {
    fprintf(outfile, "|%s", List[0].name);
  }

  else if (List[0].token == 3) {
    fprintf(outfile, "|%d", List[0].numValue);
  }

  for (i = 1; i < Listidx; i++) {
    fprintf(outfile, "|%d", List[i].token);
    if (List[i].token == 2) {
      fprintf(outfile, "|%s", List[i].name);
    }
    else if (List[i].token == 3) {
      fprintf(outfile, "|%d", List[i].numValue);
    }
  }



  printf("\n");
  infile = fopen("lexoutput.txt", "r");
  while ((ch = fgetc(infile)) != EOF) {
    printf("%c", ch);
  }
  printf("\n\n");
  fclose(infile);


  infile = fopen("lexoutput.txt", "r");
  printf("Lexeme Table:\n");
  printf("lexeme    token type\n");
  for (i = 0; i < Listidx; i++) {

    if (List[i].token == 2) {

      printf("%s\t\t%d\n", List[i].name, List[i].token);
      i++;
    }
    if (List[i].token == 3) {

      printf("%d\t\t%d\n", List[i].numValue, List[i].token);

    }
    else {

      printf("%s\t\t%d\n", lexSym[List[i].token], List[i].token);

    }
  }

  printf("Lexeme List:\n");
  for (i = 0; i < Listidx; i++) {
    printf("%d ", List[i].token);
    if (List[i].token == 2) {
      printf("%s ", List[i].name);
    }
    else if (List[i].token == 3) {
      printf("%d ", List[i].numValue);
    }
  }
  printf("\n\n");
  fclose(infile);


  fclose(infile);
  fclose(outfile);
}