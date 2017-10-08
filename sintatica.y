%{
#include <iostream>
#include <string>
#include <sstream>
#include <map>

#define YYSTYPE atributos

using namespace std;

struct atributos{
	string label;
	string traducao;
	string tipo;
	string valor;
};

int yylex(void);

string MSG_ERRO = "\nErrore:\n";
string MSG_ERRO_TIPO = "\nErrore:\nTipo errato per variabile\n";
string MSG_ERRO_NDECLARADA = "\nErrore:\nVariabile non dichiarata\n";
string MSG_ERRO_DECLARADA = "\nErrore:\nVariabile già dichiarata\n";
string MSG_ERRO_INICIALIZADA = "\nErrore:\nvariabile non inizializzata\n";

void yyerror(string);

static int ctdDInt = 0, ctdDFloat = 0, ctdDChar = 0, ctdDBool = 0;
static int fazCasting;
static int tipoGeral;

static std::map<string,atributos> mapaDeVariaveis; 

int tabelaDeTipos(string tipo1, string tipo2){

	if(tipo1 == "int" && tipo2 == "int"){
		return 0;
	}
	else if(tipo1 == "float" && tipo2 == "float"){
		return 3;
	}
	else if(tipo1 == "int" && tipo2 == "float"){
		return 1;
	}
	else{
		return 2;
	}
}

string geraVarTemp(string tipo){

	static int nI = 0, nF = 0, nC = 0, nB = 0;
	
	if(tipo == "int"){
		ctdDInt += 1;
		nI++;
		return "TMP_INT_" + to_string(nI);
	}
	if(tipo == "float"){		
		ctdDFloat += 1;
		nF++;
		return "TMP_FLOAT_" + to_string(nF);
	}
	if(tipo == "char"){
		ctdDChar += 1;
		nC++;
		return "TMP_CHAR_" + to_string(nC);
	}
	if(tipo == "bool"){
		ctdDBool += 1;
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
//'e' de encontrar - PARA SABER SE A VARIAVEL JA FOI DECLARADA 
//'d' de declar - PARA SABER SE PODE DECLARAR 
bool variavelExistente(string variavel, char opcao){
	if(opcao == 'e'){
		if(variavel != ""){
			return true;
		}else{
			std::cout <<MSG_ERRO_NDECLARADA<< std::endl;
			exit(1);	
		}
	}else if(opcao == 'd'){
		if(variavel == ""){
			return true;
		}else{
			std::cout <<MSG_ERRO_DECLARADA<< std::endl;
			exit(1);	
		}
	}
}

string verificaErros(atributos $1, atributos $3, int opcao){
	
	if(opcao == 1){
		if(variavelExistente(mapaDeVariaveis[$1.label].label,'e')){
			if(mapaDeVariaveis[$1.label].tipo == "int" || mapaDeVariaveis[$1.label].tipo == "float"){
				if(mapaDeVariaveis[$1.label].tipo != $3.tipo){											
					std::cout <<MSG_ERRO_TIPO<< std::endl;
					exit(1);		
				}				
				mapaDeVariaveis[$1.label].valor = $3.traducao;
				string retorno = $3.traducao + "\t" + mapaDeVariaveis[$1.label].label + " = " + $3.label +";\n";
				return retorno;
			}else{
				std::cout <<MSG_ERRO_TIPO<< std::endl;
				exit(1);									
			}					
		}
	}else if(opcao == 2){
		if(variavelExistente(mapaDeVariaveis[$1.label].label, 'e')){
			if(mapaDeVariaveis[$1.label].tipo == "bool"){
				mapaDeVariaveis[$1.label].valor = $3.traducao;
				string retorno = $3.traducao + "\t" + mapaDeVariaveis[$1.label].label + " = " + $3.label +";\n";
				return retorno;
			}else{
				std::cout <<MSG_ERRO_TIPO<< std::endl;
				exit(1);									
			}
		}
	}	
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
%token TOKEN_WHILE
%token TOKEN_RETURN
%token TOKEN_PRINT
%token TOKEN_ERROR
%token TOKEN_STRUCT

%token TOKEN_NOMEVAR
%token TOKEN_NUM_INT
%token TOKEN_NUM_FLOAT
%token TOKEN_BOOLEAN_FALSE
%token TOKEN_BOOLEAN_TRUE
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


%token TOKEN_ATR


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
				cout << "/*Compilador ITL*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void){\n" <<
				$5.traducao << "\treturn 0;\n}" << endl; 							
			}
			;

BLOCO		: '{' COMANDOS '}'
			{
				$$.label = geraLabelFinal();
				$$.traducao = $$.label + $2.traducao;
			}
			;
BLOCO_WHILE	: '{' COMANDOS '}'
			{
				$$.traducao = $2.traducao;
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

COMANDO 	: TOKEN_NOMEVAR TOKEN_ATR E ';' 
			{
				$$.traducao = verificaErros($1, $3, 1);
			}
			| TOKEN_NOMEVAR TOKEN_ATR ERL ';' 
			{
				$$.traducao = verificaErros($1, $3, 2);
			}
			| DCL ';'
			| WHILE
			;			

DCL 		: TOKEN_INT TOKEN_NOMEVAR MLTVAR_INT
			{	
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "int";
					$$.valor = "null";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $3.traducao;

					mapaDeVariaveis[$2.label] = $$;
				}
			}
			| TOKEN_INT TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_INT
			{
				
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "int";
					$$.valor = $4.valor;			

					if($4.tipo != $$.tipo ){																
						std::cout <<MSG_ERRO_TIPO<< std::endl;
						exit(1);		
					}				

					$$.label = geraVarTemp($$.tipo);
					$$.valor = $4.traducao;
					$$.traducao = $4.traducao +  "\t" + $$.label + " = " + $4.label + ";\n" + $5.traducao; 

					mapaDeVariaveis[$2.label] = $$;
				}

			}
			| TOKEN_FLOAT TOKEN_NOMEVAR MLTVAR_FLOAT
			{
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					
					$$.tipo = "float";
					$$.valor = "null";		

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $3.traducao;

					mapaDeVariaveis[$2.label] = $$;
				}	
			}
			| TOKEN_FLOAT TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_FLOAT
			{

				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){

					$$.tipo = "float";
					$$.valor = $4.valor;

					if($4.tipo != $$.tipo ){																
						std::cout <<MSG_ERRO_TIPO<< std::endl;
						exit(1);		
					}

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $4.traducao +  "\t" + $$.label + " = " + $4.label + ";\n" + $5.traducao; 

					mapaDeVariaveis[$2.label] = $$;
				}

			}
			| TOKEN_CHAR TOKEN_NOMEVAR MLTVAR_CHAR
			{	
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "char";
					$$.valor = "null";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $3.traducao;

					mapaDeVariaveis[$2.label] = $$;
				}

			}
			| TOKEN_CHAR TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_CHAR
			{

				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					if(tipoGeral == 2){
						$$.tipo = "char";
						$$.valor = $4.valor;

						if($4.tipo != $$.tipo ){																
							std::cout <<MSG_ERRO_TIPO<< std::endl;
							exit(1);		
						}
						
						$$.label = geraVarTemp($$.tipo);
						$$.traducao = $4.traducao +  "\t" + $$.label + " = " + $4.label + ";\n" + $5.traducao; 

						mapaDeVariaveis[$2.label] = $$;
					}else{
						std::cout <<MSG_ERRO_TIPO<< std::endl;
						exit(1);
					}

				}

			}
			| TOKEN_BOOL TOKEN_NOMEVAR MLTVAR_BOOL
			{	
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "bool";
					$$.valor = "null";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $3.traducao;

					mapaDeVariaveis[$2.label] = $$;
				}
			}
			| TOKEN_BOOL TOKEN_NOMEVAR TOKEN_ATR ERL MLTVAR_BOOL
			{

				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					if ($4.valor == "0" || $4.valor == "1"){
						$$.tipo = "bool";
						$$.valor = $4.valor;				

						
						if($4.tipo != $$.tipo ){																
							std::cout <<MSG_ERRO_TIPO<< std::endl;
							exit(1);		
						}

						$$.label = geraVarTemp($$.tipo);
						$$.traducao = $4.traducao +  "\t" + $$.label + " = " + $4.label + ";\n" + $5.traducao; 

						mapaDeVariaveis[$2.label] = $$;	
					}
					else {
						std::cout << MSG_ERRO_TIPO<< std::endl;
						std::cout <<$4.valor<< std::endl;			
						exit(1);
					}
					
				}

			}
			

MLTVAR_INT	: ',' TOKEN_NOMEVAR MLTVAR_INT
			{
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "int";
					$$.valor = "null";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = "";
					
					mapaDeVariaveis[$2.label] = $$;
				}
			}
			| ',' TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_INT
			{
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "int";
					$$.valor = $4.valor;

					if($4.tipo != $$.tipo ){																
						std::cout << MSG_ERRO_TIPO<< std::endl;
						exit(1);		
					}				
								

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $5.traducao + $4.traducao + "\t" + $$.label + " = " + $4.label + ";\n" ;

					mapaDeVariaveis[$2.label] = $$;
				}
			}
			|
			{
				$$.traducao = "";
			}
			;

MLTVAR_FLOAT: ',' TOKEN_NOMEVAR MLTVAR_FLOAT
			{
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "float";
					$$.valor = "null";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = "";

					mapaDeVariaveis[$2.label] = $$;
				}
			}
			| ',' TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_FLOAT
			{
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "float";
					$$.valor = $4.valor;

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $5.traducao + $4.traducao + "\t" + $$.label + " = " + $4.label + ";\n" ;
					
					mapaDeVariaveis[$2.label] = $$;
				}
			}
			|
			{
				$$.traducao = "";
			}
			;			

MLTVAR_CHAR	: ',' TOKEN_NOMEVAR MLTVAR_CHAR
			{
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "char";
					$$.valor = "null";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = "";

					mapaDeVariaveis[$2.label] = $$;
				}
			}
			| ',' TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_CHAR
			{
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "char";
					$$.valor = $4.valor;
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $5.traducao + $4.traducao + "\t" + $$.label + " = " + $4.label + ";\n" ;
					
					mapaDeVariaveis[$2.label] = $$;
				}
			}
			|
			{
				$$.traducao = "";
			}
			;

MLTVAR_BOOL : ',' TOKEN_NOMEVAR MLTVAR_BOOL
			{
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "bool";
					$$.valor = "null";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = "";

					mapaDeVariaveis[$2.label] = $$;
				}
			}
			| ',' TOKEN_NOMEVAR TOKEN_ATR ERL MLTVAR_BOOL
			{
				if(variavelExistente(mapaDeVariaveis[$2.label].label, 'd')){
					$$.tipo = "bool";
					$$.valor = $4.valor;

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $5.traducao + $4.traducao + "\t" + $$.label + " = " + $4.label + ";\n" ;
					
					mapaDeVariaveis[$2.label] = $$;
				}
			}
			|
			{
				$$.traducao = "";
			}
			;			

WHILE 		: TOKEN_WHILE '(' ERL ')' BLOCO_WHILE
			{
				$$.traducao = "\n\twhile ("+$3.label+"){\n"+$5.traducao+"\t}\n";
			}
			;

ERL         : '(' ERL ')'
			{
				$$.tipo = $2.tipo;
				$$.label = $2.label;
				$$.traducao = $2.traducao;
			}
 			| ERL TOKEN_MAIOR ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " > " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " > " + labelCasting +
					";\n";
				}
				else{		
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " > " + $3.label +
					";\n";
				}

			}
			| ERL TOKEN_MENOR ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " < " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " < " + labelCasting +
					";\n";
				}
				else{		
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " < " + $3.label +
					";\n";
				}
			}
			| ERL TOKEN_MAIORIGUAL ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " >= " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " >= " + labelCasting +
					";\n";
				}
				else{		
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " >= " + $3.label +
					";\n";
				}
			}
			| ERL TOKEN_MENORIGUAL ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " <= " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " <= " + labelCasting +
					";\n";
				}
				else{		
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " <= " + $3.label +
					";\n";
				}
			}
			| ERL TOKEN_DIF ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " != " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " != " + labelCasting +
					";\n";
				}
				else{		
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " != " + $3.label +
					";\n";
				}
			}
			| ERL TOKEN_IGUAL ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " == " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " == " + labelCasting +
					";\n";
				}
				else{		
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " == " + $3.label +
					";\n";
				}
			}
			| ERL TOKEN_E ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " && " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " && " + labelCasting +
					";\n";
				}
				else{		
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " && " + $3.label +
					";\n";
				}
			}
			| ERL TOKEN_OU ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " || " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " || " + labelCasting +
					";\n";
				}
				else{		
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " || " + $3.label +
					";\n";
				}
			}
			| E_BASICA
			{ 
				$$.traducao = $1.traducao;
			}
			;	

E 			: '(' E ')'
			{
				$$.tipo = $2.tipo;
				$$.label = $2.label;
				$$.traducao = $2.traducao;
			}
			| E '+' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraVarTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " + " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraVarTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " + " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " + " + $3.label +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " + " + $3.label +
					";\n";
				}

				
			}
			| E '-' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraVarTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " - " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraVarTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " - " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " - " + $3.label +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " - " + $3.label +
					";\n";
				}
				
			}
			| E '*' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraVarTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " * " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraVarTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " * " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " * " + $3.label +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " * " + $3.label +
					";\n";
				}
				
			}
			| E '/' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraVarTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.label + ";\n";

					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + labelCasting + " / " + $3.label +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraVarTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.label + ";\n";
					
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.label + " = " + $1.label + " / " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " / " + $3.label +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.label = geraVarTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.label + " = " + $1.label + " / " + $3.label +
					";\n";
				}
			}
			| TOKEN_CONV_FLOAT E
			{
				$$.tipo = "float";
				
				$$.label = geraVarTemp($$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.label + " = (float) " + $2.label +
				";\n";
			}
			| TOKEN_CONV_INT E
			{
				$$.tipo = "int";
				
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
			{ 
				$$.traducao = $1.traducao;
			}
			;

E_BASICA	: TOKEN_NUM_INT
			{
				tipoGeral = 1;
				$$.tipo = "int";
				$$.label = geraVarTemp($$.tipo);
				$$.valor = $1.traducao;
				$$.traducao = "\t" + $$.label + " = " + $1.traducao +
				";\n";
			}
			| TOKEN_NUM_FLOAT
			{
				tipoGeral = 1;
				$$.tipo = "float";
				$$.label = geraVarTemp($$.tipo);
				$$.valor = $1.traducao;
				$$.traducao = "\t" + $$.label + " = " + $1.traducao +
				";\n";
			}
			| TOKEN_NOMEVAR
			{

                if(mapaDeVariaveis.find($1.label) != mapaDeVariaveis.end()){
					if(mapaDeVariaveis[$1.label].tipo == "float" || mapaDeVariaveis[$1.label].tipo == "int"){

						if(mapaDeVariaveis[$1.label].valor != "null"){						

							$$.label = mapaDeVariaveis[$1.label].label;
							$$.valor = mapaDeVariaveis[$1.label].valor;
							$$.tipo = mapaDeVariaveis[$1.label].tipo;
							$$.traducao = ""; 

						}
						else{
							std::cout <<mapaDeVariaveis[$1.label].label<<MSG_ERRO_INICIALIZADA << std::endl;
							exit(1);															
						}
					}
					else{
						std::cout <<MSG_ERRO_TIPO<< std::endl;
						exit(1);									
					}
				}
				else{
					std::cout <<MSG_ERRO_NDECLARADA<< std::endl;
					exit(1);									
				}



			}
			| TOKEN_BOOLEAN_FALSE
			{
				$$.tipo = "bool";
				$$.label = geraVarTemp($$.tipo);
				$$.valor = "0";
				$$.traducao = "\t" + $$.label + " = " + $$.valor +
				";\n";
			}
			| TOKEN_BOOLEAN_TRUE
			{
				$$.tipo = "bool";
				$$.label = geraVarTemp($$.tipo);
				$$.valor = "1";
				$$.traducao = "\t" + $$.label + " = " + $$.valor +
				";\n";
			}
			| TOKEN_CARACTERE
			{
				tipoGeral = 2;
				$$.tipo = "char";
				$$.label = geraVarTemp($$.tipo);
				$$.valor = $1.traducao;
				$$.traducao = "\t" + $$.label + " = " + $1.traducao +
				";\n";
			}					
            ;


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
