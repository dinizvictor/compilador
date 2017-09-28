%{
#include <iostream>
#include <string>
#include <sstream>

#define YYSTYPE atributos

using namespace std;

struct atributos
{
	string label;
	string traducao;
	string tipo;
};

int yylex(void);

void yyerror(string);

static int ctdDInt = 0, ctdDFloat = 0, ctdDChar = 0, ctdDBool = 0;

string tabelaDeTipos(string tipo1, string tipo2){

	if(tipo1 == "inteiro" && tipo2 == "inteiro"){
		ctdDInt += 1;
		return "inteiro";
	}
	else{
		ctdDFloat += 1;
		return "float";
	}
}

string geraVarTemp(string tipo){

	static int nI = 0, nF = 0, nC = 0, nB = 0;
	
	if(tipo == "inteiro"){
		nI++;
		return "TMP_INT_" + to_string(nI);
	}
	if(tipo == "float"){
		nF++;
		return "TMP_FLOAT_" + to_string(nF);
	}
	if(tipo == "char"){
		nC++;
		return "TMP_CHAR_" + to_string(nC);
	}
	if(tipo == "booleano"){
		nB++;
		return "TMP_BOOL_" + to_string(nB);
	}
}



string geraLabelFinal(){
	int i = 1;
	string declaracao = ""; 

	if(ctdDInt > 0){
		declaracao = declaracao + "\tint ";
		while(i < ctdDInt){
			declaracao = declaracao + "TMP_INT_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_INT_" + to_string(i) + ";\n";
		i = 1;
	}
	if(ctdDFloat > 0){
		declaracao = declaracao + "\tfloat ";
		while(i < ctdDFloat){
			declaracao = declaracao + "TMP_FLOAT_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_FLOAT_" + to_string(i) + ";\n";
		i = 1;
	}
	if(ctdDChar > 0){
		declaracao = declaracao + "\tchar ";
		while(i < ctdDChar){
			declaracao = declaracao + "TMP_CHAR_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_CHAR_" + to_string(i) + ";\n";
		i = 1;
	}
	if(ctdDBool > 0){
		declaracao = declaracao + "\tbool ";
		while(i < ctdDBool){
			declaracao = declaracao + "TMP_BOOL_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_BOOL_" + to_string(i) + ";\n";
		i = 1;
	}

	return declaracao + "\n";
}

%}

%token TOKEN_MAIN
%token TOKEN_BEGIN

%token TOKEN_INT
%token TOKEN_FLOAT
%token TOKEN_DOUBLE
%token TOKEN_CHAR
%token TOKEN_BOOL

%token TOKEN_NULL
%token TOKEN_VOID
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_SWITCH
%token TOKEN_CASE
%token TOKEN_BREAK
%token TOKEN_DO
%token TOKEN_FOR
%token TOKEN_RETURN
%token TOKEN_PRINT
%token TOKEN_ERROR
%token TOKEN_STRUCT

%token TOKEN_NOMEVAR
%token TOKEN_NUM_INT
%token TOKEN_NUM_FLOAT
%token TOKEN_BOOLEAN
%token TOKEN_CARACTERE

%token TOKEN_MAIOR
%token TOKEN_MENOR
%token TOKEN_DIF
%token TOKEN_IGUAL
%token TOKEN_MAIORIGUAL
%token TOKEN_MENORIGUAL
%token TOKEN_E
%token TOKEN_OU

%token TOKEN_CONV_FLOAT
%token TOKEN_CONV_INT

%left TOKEN_E TOKEN_OU 
%left TOKEN_MAIOR TOKEN_MENOR TOKEN_MAIORIGUAL TOKEN_MENORIGUAL TOKEN_DIF TOKEN_IGUAL 
%left ','
%left '+' '-'
%left '*' '/'
%left '(' 
%left TOKEN_CONV_FLOAT TOKEN_CONV_INT


%start S

%%

S		    : TOKEN_BEGIN TOKEN_MAIN '(' ')' BLOCO
            {
				cout << "/*Compilador ITL*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void)\n{\n" <<
				$5.traducao << "\treturn 0;\n}" << endl; 
			}
			;

BLOCO		: '{' COMANDOS '}'
			{
				$$.label = geraLabelFinal();
				$$.traducao = $$.label + $2.traducao;
			}
			;

COMANDOS	: COMANDO COMANDOS
			{
				$$.traducao = $1.traducao + $2.traducao;
			}
			| 
			{
				$$.traducao = "";
			}
			;

COMANDO 	: E ';' 
			| ERL ';' 
			;

ERL         :'(' ERL ')'
			{
				$$.tipo = $2.tipo;
				$$.label = $2.label;
				$$.traducao = $2.traducao;
			}
 			| ERL TOKEN_MAIOR ERL
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " > " + $3.label +
				";\n";
			}
			| ERL TOKEN_MENOR ERL
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " < " + $3.label +
				";\n";
			}
			| ERL TOKEN_MAIORIGUAL ERL
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " >= " + $3.label +
				";\n";
			}
			| ERL TOKEN_MENORIGUAL ERL
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " <= " + $3.label +
				";\n";
			}
			| ERL TOKEN_DIF ERL
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " != " + $3.label +
				";\n";
			}
			| ERL TOKEN_IGUAL ERL
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " == " + $3.label +
				";\n";
			}
			| ERL TOKEN_E ERL
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " && " + $3.label +
				";\n";
			}
			| ERL TOKEN_OU ERL
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " || " + $3.label +
				";\n";
			}
			| E_BASICA
			{ }
			;	

E 			: '(' E ')'
			{
				$$.tipo = $2.tipo;
				$$.label = $2.label;
				$$.traducao = $2.traducao;
			}
			| E '+' E
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " + " + $3.label +
				";\n";
				
			}
			| E '-' E
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " - " + $3.label +
				";\n";
				
			}
			| E '*' E
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " * " + $3.label +
				";\n";
				
			}
			| E '/' E
			{
				$$.tipo = tabelaDeTipos($1.tipo, $3.tipo);

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $1.traducao + $3.traducao + "\t" +
				$$.label + " = " + $1.label + " / " + $3.label +
				";\n";
				
			}
			| TOKEN_CONV_FLOAT E
			{
				$$.tipo = "float";
				ctdDFloat += 1;

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.label + " = (float) " + $2.label +
				";\n";
			}
			| TOKEN_CONV_INT E
			{
				$$.tipo = "inteiro";
				ctdDInt += 1;

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.label + " = (int) " + $2.label +
				";\n";
			}
			| '-' E
			{
				$$.tipo = $2.tipo;

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.label + " = -" + $2.label +
				";\n";			
			}
			| E_BASICA
			{ }
			;

E_BASICA	: TOKEN_NUM_INT
			{
				ctdDInt += 1;
				$$.tipo = "inteiro";


				$$.label = geraVarTemp($$.tipo);
				$$.traducao = "\t" + $$.label + " = " + $1.traducao +
				";\n";
			}
			| TOKEN_NUM_FLOAT
			{
				ctdDFloat += 1;
				$$.tipo = "float";

				$$.label = geraVarTemp($$.tipo);
				$$.traducao = "\t" + $$.label + " = " + $1.traducao +
				";\n";
			}
			| TOKEN_NOMEVAR
			{
                $$.label = geraVarTemp("int");
                $$.traducao = "\t" + $$.label +" = " + $1.label + 
                ";\n";
			}

%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{
	yyparse();

	return 0;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				
