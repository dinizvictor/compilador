%{
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stack>

#define YYSTYPE Atributos

using namespace std;

struct Atributos{
	string nomeVariavel;
	string labelTemp;
	string traducao;
	string tipo;
	string valor;
	string varTamString;
	int tamanho;	
};

typedef	std::map<string,Atributos> MapaDeVariaveis;

struct Contexto{
	MapaDeVariaveis mapa;
	bool interrompivel;
	string rotuloInicio;
	string rotuloFim;
};


typedef std::stack<Contexto> PilhaContexto;


static PilhaContexto pilhaDeContextos;

void empilhaMapa(bool interrompivel, string rotuloInicio, string rotuloFim){

	Contexto c;
	c.interrompivel = interrompivel;
	c.rotuloInicio = rotuloInicio;
	c.rotuloFim = rotuloFim;
	pilhaDeContextos.push(c);

}

void desempilhaMapa(){

	pilhaDeContextos.pop();
	
}

int yylex(void);

string MSG_ERRO = "\nErrore:\n";
string MSG_ERRO_TIPO = "\nErrore:\nTipo errato per variabile";
string MSG_ERRO_NDECLARADA = "\nErrore:\nVariabile non dichiarata";
string MSG_ERRO_DECLARADA = "\nErrore:\nVariabile già dichiarata";
string MSG_ERRO_INICIALIZADA = "\nErrore:\nvariabile non inizializzata";
string MSG_ERRO_CONTEXTONAOINTERROMPIVEL = "\nErrore:\ncontesto non interrompibile";

void yyerror(string);

static int ctdDInt = 0, ctdDFloat = 0, ctdDChar = 0, ctdDBool = 0, ctdDString = 0, ctdDStringTam = 0;
static string switchPar, sFimIFs,sFSwitch;
static int nCL = 0;
static int fazCasting;
static int tipoGeral;
static int ctdLinhas = 1;

void indicaErro(string MSG){

	std::cout<<MSG<<" (linea "<<ctdLinhas<<")\n"<<std::endl;

}

void contaLinha(){
	ctdLinhas++;
}

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

void adicionaVariavelContexto(Atributos a){

	pilhaDeContextos.top().mapa[a.nomeVariavel] = a;

}

string geraLabelTemp(string tipo){

	static int nI = 0, nF = 0, nC = 0, nB = 0, nS = 0, nST = 0;
	
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
	if(tipo == "string"){
		ctdDString += 1;
		nS++;
		return "TMP_STRING_" + to_string(nS);
	}
	if(tipo == "string_tam"){
		ctdDStringTam += 1;
		nST++;
		return "TMP_STRING_TAM_" + to_string(nST);
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
	}
	i = 1;
	if(ctdDStringTam > 0){
		declaracao = declaracao + "\tint ";
		while(i < ctdDStringTam){
			declaracao = declaracao + "TMP_STRING_TAM_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_STRING_TAM_" + to_string(i) + ";\n";
	}
	i = 1;
	if(ctdDFloat > 0){
		declaracao = declaracao + "\tfloat ";
		while(i < ctdDFloat){
			declaracao = declaracao + "TMP_FLOAT_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_FLOAT_" + to_string(i) + ";\n";		
	}
	i = 1;
	if(ctdDChar > 0){
		declaracao = declaracao + "\tchar ";
		while(i < ctdDChar){
			declaracao = declaracao + "TMP_CHAR_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_CHAR_" + to_string(i) + ";\n";		
	}
	i = 1;
	if(ctdDString > 0){			
		while(i <= ctdDString){
			declaracao = declaracao + "\tchar * TMP_STRING_" + to_string(i) + ";\n";
			i++;
		}				
	}
	i = 1;
	if(ctdDBool > 0){
		declaracao = declaracao + "\tint ";
		while(i < ctdDBool){
			declaracao = declaracao + "TMP_BOOL_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_BOOL_" + to_string(i) + ";\n";		
	}

	return declaracao + "\n";
}


static int nRotulo = 0;

string geraRotulo(){

	nRotulo++;
	return "ROTULO_" + to_string(nRotulo);

}

void atualizarPilhaContextos(Atributos a){

	PilhaContexto pilhaAux;
	bool achou = 0;
	string variavel = pilhaDeContextos.top().mapa[a.nomeVariavel].nomeVariavel;
	if(variavel != ""){
		pilhaDeContextos.top().mapa[a.nomeVariavel] = a;
	}
	else if(pilhaDeContextos.size() > 1){

		pilhaAux.push(pilhaDeContextos.top());
		
		pilhaDeContextos.pop();

		do{

			variavel = pilhaDeContextos.top().mapa[a.nomeVariavel].nomeVariavel;
			
			if(variavel != ""){
				
				achou = 1;
				pilhaDeContextos.top().mapa[a.nomeVariavel] = a;				

			}
			
			pilhaAux.push(pilhaDeContextos.top());
			pilhaDeContextos.pop();
			

		}while(!pilhaDeContextos.empty() || !achou);
		
		//Retornando os contextos para a pilhaDeContextos...

		while(!pilhaAux.empty()){
			
			pilhaDeContextos.push(pilhaAux.top());
			pilhaAux.pop();

		}

	}

}

Contexto retornarContextoDaVariavel(string nomeVariavel){
	Contexto c;
	string variavel = pilhaDeContextos.top().mapa[nomeVariavel].labelTemp;
	if(variavel != ""){
		c = pilhaDeContextos.top();
		return c;
	}
	else if(pilhaDeContextos.size() > 1){
		PilhaContexto copiaPilha;
		copiaPilha = pilhaDeContextos;
		copiaPilha.pop();
		do{

			c = copiaPilha.top();
			variavel = c.mapa[nomeVariavel].labelTemp;
			if(variavel != ""){
				
				return c;
			}
			copiaPilha.pop();

		}while(copiaPilha.size() >= 1);

	}

	return c;

}

//'e' de encontrar - PARA SABER SE A VARIAVEL JA FOI DECLARADA 
//'d' de declarar - PARA SABER SE PODE DECLARAR 

bool verificaNosContextosAnteriores(string nomeVariavel, char opcao){
	string variavel;
	
	if(opcao == 'e'){
		PilhaContexto copiaPilha;
		copiaPilha = pilhaDeContextos;
		
		copiaPilha.pop();
		
		Contexto c;

		do{

			variavel = copiaPilha.top().mapa[nomeVariavel].nomeVariavel; //Verifica novamente
			c = copiaPilha.top();
			variavel = c.mapa[nomeVariavel].nomeVariavel;
			if(variavel != ""){
				return true;
			}
			copiaPilha.pop();
		
		}while(copiaPilha.size() >= 1);

		return false;

	}
	else if(opcao == 'd'){
		PilhaContexto copiaPilha;
		copiaPilha = pilhaDeContextos;
		copiaPilha.pop();
		
		Contexto c;
		do{
			
			variavel = copiaPilha.top().mapa[nomeVariavel].nomeVariavel; //Verifica novamente
			c = copiaPilha.top(); 
			variavel = c.mapa[nomeVariavel].nomeVariavel;
			if(variavel == ""){
				return true;
			}
			copiaPilha.pop();

		}while(copiaPilha.size() >= 1);

		return false;
	}

}

bool variavelExistente(string nomeVariavel, char opcao){

	string variavel = pilhaDeContextos.top().mapa[nomeVariavel].nomeVariavel;
	
		if(opcao == 'e'){
			if(variavel != ""){
				return true;
			}
			else if(pilhaDeContextos.size() > 1){
				
				bool achou = verificaNosContextosAnteriores(nomeVariavel, opcao);
				if(achou){
					return true;
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);
				}
				
			}
			else{
				indicaErro(MSG_ERRO_NDECLARADA);
				exit(1);	
			}
		}else if(opcao == 'd'){
			if(variavel == ""){
				return true;
			}
			else if(pilhaDeContextos.size() > 1){
				bool podeDeclarar = verificaNosContextosAnteriores(nomeVariavel, opcao);
				if(podeDeclarar){
					return true;
				}
				else{
					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);
				}
				
			}
			else{
				indicaErro(MSG_ERRO_NDECLARADA);
				exit(1);	
			}
		}			
				
}


string verificaErros(Atributos $1, Atributos $3, int opcao){
	if(opcao == 1){
		if(variavelExistente($1.nomeVariavel,'e')){
			Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
			if(c.mapa[$1.nomeVariavel].tipo == "int" || c.mapa[$1.labelTemp].tipo == "float"){
				
				if(c.mapa[$1.nomeVariavel].tipo != $3.tipo){											
					indicaErro(MSG_ERRO_TIPO);
					exit(1);		
				}
				c.mapa[$1.nomeVariavel].valor = $3.traducao;
				atualizarPilhaContextos(c.mapa[$1.nomeVariavel]);
				
				string retorno = $3.traducao + "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $3.labelTemp +";\n";
				
				return retorno;
			}else{
				indicaErro(MSG_ERRO_TIPO);
				exit(1);									
			}					
		}
	}else if(opcao == 2){
		if(variavelExistente($1.nomeVariavel, 'e')){
			Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
			if(c.mapa[$1.nomeVariavel].tipo == "int"){
				c.mapa[$1.nomeVariavel].valor = $3.traducao;
				
				atualizarPilhaContextos(c.mapa[$1.nomeVariavel]);
				
				string retorno = $3.traducao + "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $3.labelTemp +";\n";
				
				return retorno;
			}else{
				indicaErro(MSG_ERRO_TIPO);
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
%token TOKEN_STR

%token TOKEN_NULL
%token TOKEN_VOID
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_ELSEIF
%token TOKEN_SWITCH
%token TOKEN_CASE
%token TOKEN_DEFAULT
%token TOKEN_IMP
  
%token TOKEN_BREAK
%token TOKEN_CONTINUE

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
%token TOKEN_STRING

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
%token TOKEN_SCANF

%token TOKEN_COMENT
%token TOKEN_COM_INT 
%token TOKEN_COM_END 
%token TOKEN_LINECOMENT

%left TOKEN_E TOKEN_OU 
%left TOKEN_MAIOR TOKEN_MENOR TOKEN_MAIORIGUAL TOKEN_MENORIGUAL TOKEN_DIF TOKEN_IGUAL 
%left ','
%left '+' '-'
%left '*' '/'
%left '(' 
%left TOKEN_CONV_FLOAT TOKEN_CONV_INT


%start S

%%

S		    : BLOCO_GLOBAL TOKEN_BEGIN TOKEN_MAIN '(' ')' BLOCO_MAIN 
            {
            	
            	$$.labelTemp = geraLabelFinal();
				cout << "/*Compilador ITL*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\nint main(void){\n" <<
				$$.labelTemp << $1.traducao +$6.traducao << "\treturn 0;\n}" << endl; 							
				
			}
			;

BLOCO_GLOBAL: EMP_GLOBAL DCL_GLOBAL
			{
				$$.traducao = $2.traducao;
			}
			| BLOCO_MAIN
			;

EMP_GLOBAL	:
			{	
				//Empilha o Escopo Global
				empilhaMapa(0,"","");
			}

BLOCO_MAIN	: EMP_MAIN '{' COMANDOS '}'
			{
				$$.traducao = $3.traducao;
			}
			| BLOCO_NI
			| BLOCO_LOOP
			;

EMP_MAIN 	:
			{

				//Empilha o Main
				empilhaMapa(0,"","");
				

			}

BLOCO_NI	: EMP_NI '{' COMANDOS '}'
			{
				$$.traducao = $3.traducao;
			}
			;

EMP_NI 		:
			{
				//Empilha o Bloco não interrompível
				empilhaMapa(0,"","");
				

			}

BLOCO_LOOP	: EMP_LOOP '{' COMANDOS '}'
			{
				$$.traducao = $3.traducao;
			}
			;

BLOCO_SWITCH: EMP_LOOP '(' CASES ')'
			{
				

				$$.traducao = $3.traducao;
			}
			;	

EMP_LOOP	:
			{
				//Empilha o Bloco interrompível
				empilhaMapa(1,geraRotulo(),geraRotulo());
				

			}

								

COMANDOS	: COMANDO COMANDOS
			{
				$$.traducao = $1.traducao + $2.traducao;
			}
			| 
			{
				$$.traducao = "";
			}
			;

COMANDO 	: 
			| ATR
			| ATR_RL
			| DCL ';'
			| CONCATENACAO ';'
			| IF
			| SWITCH
			| WHILE
			| DO_WHILE
			| FOR
			| BREAK ';'
			| SCANF ';'
			| PRINT ';'
     	 	| CONTINUE ';'
			| COMENT
			;
ATR_RL		: TOKEN_NOMEVAR TOKEN_ATR ERL ';'
			{
				$$.traducao = verificaErros($1, $3, 2);
			}
			;

ATR 		: TOKEN_NOMEVAR TOKEN_ATR E ';'
			{
				$$.traducao = verificaErros($1, $3, 1);
			}
			;

DCL_GLOBAL	: DCL ';' DCL_GLOBAL
			{
				$$.traducao = $1.traducao + $3.traducao;
			}
			|
			{
				$$.traducao = "";
			}
			;			

DCL 		: TOKEN_INT TOKEN_NOMEVAR MLTVAR_INT
			{	
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "int";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $3.traducao;
					adicionaVariavelContexto($$);
										
				}
			}
			| TOKEN_INT TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_INT
			{
				
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "int";
					$$.valor = $4.valor;			

					if($4.tipo != $$.tipo ){																
						indicaErro(MSG_ERRO_TIPO);
						exit(1);		
					}				
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.valor = $4.traducao;
					$$.traducao = $4.traducao + "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" + $5.traducao; 

					adicionaVariavelContexto($$);
				}

			}
			| TOKEN_FLOAT TOKEN_NOMEVAR MLTVAR_FLOAT
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					
					$$.tipo = "float";
					$$.valor = "null";		
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $3.traducao;

					adicionaVariavelContexto($$);
				}	
			}
			| TOKEN_FLOAT TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_FLOAT
			{

				if(variavelExistente($2.nomeVariavel, 'd')){

					$$.tipo = "float";
					$$.valor = $4.valor;

					if($4.tipo != $$.tipo ){																
						indicaErro(MSG_ERRO_TIPO);
						exit(1);		
					}
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $4.traducao +  "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" + $5.traducao; 

					adicionaVariavelContexto($$);
				}

			}
			| TOKEN_CHAR TOKEN_NOMEVAR MLTVAR_CHAR
			{	
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "char";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $3.traducao;

					adicionaVariavelContexto($$);
				}

			}
			| TOKEN_CHAR TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_CHAR
			{

				if(variavelExistente($2.nomeVariavel, 'd')){
					if(tipoGeral == 2){
						$$.tipo = "char";
						$$.valor = $4.valor;

						if($4.tipo != $$.tipo ){																
							indicaErro(MSG_ERRO_TIPO);
							exit(1);		
						}
						$$.nomeVariavel = $2.nomeVariavel;
						$$.labelTemp = geraLabelTemp($$.tipo);
						$$.traducao = $4.traducao +  "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" + $5.traducao; 

						adicionaVariavelContexto($$);
					}else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}

				}

			}
			|TOKEN_STR TOKEN_NOMEVAR MLTVAR_STRING
			{	
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "string";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.varTamString = geraLabelTemp("string_tam");
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $3.traducao;
					adicionaVariavelContexto($$);
				}

			}	
			| TOKEN_STR TOKEN_NOMEVAR TOKEN_ATR ES MLTVAR_STRING
			{

				if(variavelExistente($2.nomeVariavel, 'd')){
					if(tipoGeral == 2){
						$$.tipo = "string";
						$$.valor = $4.valor;						

						if($4.tipo != $$.tipo ){																
							indicaErro(MSG_ERRO_TIPO);
							exit(1);		
						}

						$$.tamanho = $4.tamanho;
						$$.varTamString = $4.varTamString;
						$$.nomeVariavel = $2.nomeVariavel;						
						$$.labelTemp = $4.labelTemp;
						$$.varTamString	= $4.varTamString;

						$$.traducao = $4.traducao + $5.traducao; 

						adicionaVariavelContexto($$);
					}else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}

				}

			}
			| TOKEN_BOOL TOKEN_NOMEVAR MLTVAR_BOOL
			{	
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "bool";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $3.traducao;

					adicionaVariavelContexto($$);
				}
			}
			| TOKEN_BOOL TOKEN_NOMEVAR TOKEN_ATR ERL MLTVAR_BOOL
			{

				if(variavelExistente($2.nomeVariavel, 'd')){
					if ($4.valor == "0" || $4.valor == "1"){
						$$.tipo = "bool";
						$$.valor = $4.valor;				

						
						if($4.tipo != $$.tipo ){																
							indicaErro(MSG_ERRO_TIPO);
							exit(1);		
						}
						$$.nomeVariavel = $2.nomeVariavel;
						$$.labelTemp = geraLabelTemp($$.tipo);
						$$.traducao = $4.traducao +  "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" + $5.traducao; 

						adicionaVariavelContexto($$);	
					}
					else {
						indicaErro(MSG_ERRO_TIPO);
						std::cout <<$4.valor<< std::endl;			
						exit(1);
					}
					
				}

			}
			

MLTVAR_INT	: ',' TOKEN_NOMEVAR MLTVAR_INT
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "int";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "";
					
					adicionaVariavelContexto($$);
				}
			}
			| ',' TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_INT
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "int";
					$$.valor = $4.valor;

					if($4.tipo != $$.tipo ){																
						indicaErro(MSG_ERRO_TIPO);
						exit(1);		
					}				
								
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $5.traducao + $4.traducao + "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" ;

					adicionaVariavelContexto($$);
				}
			}
			|
			{
				$$.traducao = "";
			}
			;

MLTVAR_FLOAT: ',' TOKEN_NOMEVAR MLTVAR_FLOAT
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "float";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "";

					adicionaVariavelContexto($$);
				}
			}
			| ',' TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_FLOAT
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "float";
					$$.valor = $4.valor;
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $5.traducao + $4.traducao + "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" ;
					
					adicionaVariavelContexto($$);
				}
			}
			|
			{
				$$.traducao = "";
			}
			;			

MLTVAR_CHAR	: ',' TOKEN_NOMEVAR MLTVAR_CHAR
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "char";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "";

					adicionaVariavelContexto($$);
				}
			}
			| ',' TOKEN_NOMEVAR TOKEN_ATR E MLTVAR_CHAR
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "char";
					$$.valor = $4.valor;
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $5.traducao + $4.traducao + "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" ;
					
					adicionaVariavelContexto($$);
				}
			}
			|
			{
				$$.traducao = "";
			}
			;

MLTVAR_STRING : ',' TOKEN_NOMEVAR MLTVAR_STRING
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "string";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.varTamString = geraLabelTemp("string_tam");
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "";

					adicionaVariavelContexto($$);
				}
			}
			| ',' TOKEN_NOMEVAR TOKEN_ATR ES MLTVAR_STRING
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "string";
					
					$$.valor = $4.valor;
					$$.tamanho = $4.tamanho;
					$$.varTamString = $4.varTamString;
					$$.nomeVariavel = $2.nomeVariavel;						
					$$.labelTemp = $4.labelTemp;
					$$.varTamString	= $4.varTamString;


					$$.traducao = $4.traducao + $5.traducao ;
					
					adicionaVariavelContexto($$);
				}
			}
			|
			{
				$$.traducao = "";
			}
			;


MLTVAR_BOOL : ',' TOKEN_NOMEVAR MLTVAR_BOOL
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "bool";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "";

					adicionaVariavelContexto($$);
				}
			}
			| ',' TOKEN_NOMEVAR TOKEN_ATR ERL MLTVAR_BOOL
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "bool";
					$$.valor = $4.valor;
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $5.traducao + $4.traducao + "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" ;
					
					adicionaVariavelContexto($$);
				}
			}
			|
			{
				$$.traducao = "";
			}
			;

COMENT      : TOKEN_MAIOR TOKEN_COMENT TOKEN_COM_END 
			{
				$$.traducao = "\n\t/*" + $2.traducao + "*/\n\n";
			}
			| TOKEN_COM_INT TOKEN_LINECOMENT
			{
				$$.traducao = "\n\t/" + $2.traducao + "\n";
			}
			;						

IF 			: TOKEN_IF '(' ERL ')' BLOCO_NI
			{	

				string sFimIF = geraRotulo();

					
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//IF COMEÇA\n" + $3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto "+ sFimIF +";\n" + $5.traducao +
				"\n\t"+ sFimIF +":\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();
			}
			| TOKEN_IF '(' ERL ')' BLOCO_NI ELSEIF
			{		

				string sElseIF = geraRotulo(); 
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//IF COMEÇA\n"+$3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto " + sElseIF +";\n" +
				$5.traducao + "\tgoto "+ sFimIFs +";\n\n\t" + sElseIF +":\n" + $6.traducao;        	
        		
        		desempilhaMapa();

			}
			| TOKEN_IF '(' ERL ')' BLOCO_NI ELSE
			{		
        		string sFimIF = geraRotulo();       	
        		string sElse = geraRotulo();
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//IF COMEÇA\n"+$3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto "+  sElse + ";\n" +
				$5.traducao +"\t"+ sElse +":\n" + $6.traducao;

				desempilhaMapa();
       		 	
			}
			;

ELSE: 		TOKEN_ELSE BLOCO_NI
			{
  				sFimIFs = geraRotulo();      	        
  				string sElse = geraRotulo();  			
  				
  				$$.traducao = "\t//ELSE COMEÇA\n" + $2.traducao+"\t" + 
				sFimIFs +":\n\t//ELSE TERMINA\n\t"+
				"//IF TERMINA\n\n";
  				
  				desempilhaMapa();
			}
			;
ELSEIF  	: TOKEN_ELSEIF '(' ERL ')' BLOCO_NI
			{		
        		sFimIFs = geraRotulo();
				
				string sElseIF = geraRotulo();      			
      							
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t//ELSEIF COMEÇA\n"+$3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto " + sFimIFs + ";\n" +
				$5.traducao + 
				"\n\t" + sFimIFs + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();				
			}
			| TOKEN_ELSEIF '(' ERL ')' BLOCO_NI ELSEIF
			{		
				string sFimIF = geraRotulo();
				string sElseIF = geraRotulo(); 				
        						
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//ELSEIF COMEÇA\n\t" + sElseIF + ":\n"+$3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto " + sFimIF + ";\n" +
				$5.traducao + "\n\t" + sFimIF + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();			
			}
			| TOKEN_ELSEIF '(' ERL ')' BLOCO_NI ELSE
			{
        		string sFimIF = geraRotulo();
				string sElse = geraRotulo();
				string sElseIF = geraRotulo();  				

				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t//ELSEIF COMEÇA\n"+ $3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto " + sElse +";\n" +
				$5.traducao + "\tgoto "+ sFimIFs +";\n\n\t" +sElse+":\n"+ $6.traducao;
				desempilhaMapa();
			}
			;

WHILE 		: TOKEN_WHILE ERL BLOCO_LOOP
			{	
  				string sWhile = pilhaDeContextos.top().rotuloInicio;
  				string sFWhile = pilhaDeContextos.top().rotuloFim;				
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t" + sWhile +":\n\t" + "//WHILE COMEÇA\n"+ $2.traducao +
				"\t" + $$.labelTemp + " = !" + $2.labelTemp + ";\n" +
				 "\tif("+$$.labelTemp+")goto "+sFWhile+"\n"+$3.traducao+"\tgoto " + 
				sWhile +";\n\t"+ sFWhile + ":\n\t//WHILE TERMINA\n";
  				
  				desempilhaMapa();
			}
			;

DO_WHILE 	: TOKEN_DO BLOCO_LOOP  ERL ';'
			{	
  				string sDWhile = pilhaDeContextos.top().rotuloInicio;
  				string sFDWhile = pilhaDeContextos.top().rotuloFim;				
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t" + sDWhile +":\n"+ "\t//DO_WHILE COMEÇA\n"+ $3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				$2.traducao+"\tif("+$$.labelTemp+") goto "+sFDWhile+";\n\tgoto " + 
				sDWhile +";\n\t"+ sFDWhile + ":\n\t//DO_WHILE TERMINA\n";
  				
  				desempilhaMapa();
			}
			;

FOR			: TOKEN_FOR '('COMANDO ERL ';' E ')' BLOCO_LOOP		
			{
				string sFor = pilhaDeContextos.top().rotuloInicio;
  				string sFFor = pilhaDeContextos.top().rotuloFim;	

				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t" + sFor +":\n"+"\t//FOR COMEÇA\n"+ $3.traducao + $4.traducao +
				"\t" + $$.labelTemp + " = !" + $4.labelTemp + ";\n" +
				 "\t" + "if("+$$.labelTemp+") goto "+ sFFor +";\n"+$8.traducao + $6.traducao + "\tgoto "+sFor+";\n\t"+ sFFor + ":\n\t//FOR TERMINA\n";
  				
  				desempilhaMapa();
			}
			;

SWITCH 		: TOKEN_SWITCH '('E_BASICA ',' BLOCO_SWITCH ')' ';'
			{

				$$.traducao = "\n\t//SWITCH COMEÇA\n" + $5.traducao + "\t" + sFSwitch +":\n\t//SWITCH TERMINA\n";

				desempilhaMapa();
			}
			;

CASES 		: CASE CASES
			{
				$$.traducao = $1.traducao + $2.traducao;
			}
			|	DEFAULT 
			{
				$$.traducao = $1.traducao;	
			}
			| CASE
			{
				$$.traducao = $1.traducao;
			}

			
CASE 		: TOKEN_CASE  CASE_VALUE TOKEN_IMP COMANDOS
			{

				string sFimIF = geraRotulo();
  				sFSwitch = pilhaDeContextos.top().rotuloFim;

				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $2.traducao + "\t"+ $$.labelTemp + " = !"+ $2.labelTemp + "\n\tif( "+$$.labelTemp+") goto " +sFimIF + ";\n"+ $4.traducao + "\n\t" + sFimIF +":\n";
			}
			;
DEFAULT     : TOKEN_DEFAULT TOKEN_IMP COMANDOS 
			{
				$$.traducao = $3.traducao + "\n";
			}

CASE_VALUE	: E_BASICA
			{

				$$.tipo = "bool";
				$$.valor = $1.traducao;
				$$.labelTemp = geraLabelTemp("bool");				
				$$.traducao = $$.valor + "\t" + $$.labelTemp + " = " + $1.labelTemp + " == " + switchPar +";\n";
			}
			;

BREAK       : TOKEN_BREAK
			{
       			
				PilhaContexto copiaPilha = pilhaDeContextos;
        		while(!copiaPilha.empty()){
        			if(copiaPilha.top().interrompivel == 1){
        				$$.traducao = "\t//BREAK\n\tgoto " + copiaPilha.top().rotuloFim + ";\n";
        				
        				break;
        			}
        			if(copiaPilha.size() == 1){
        				indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
						exit(1);
        			}
        			
        			copiaPilha.pop();
        			
        		}
        		
      		}

CONTINUE 	: TOKEN_CONTINUE
			{
				PilhaContexto copiaPilha = pilhaDeContextos;
        		while(!copiaPilha.empty()){
        			if(copiaPilha.top().interrompivel == 1){
        				$$.traducao = "\t//CONTINUE\n\tgoto " + copiaPilha.top().rotuloInicio + ";\n";
        				
        				break;
        			}
        			if(copiaPilha.size() == 1){
        				indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
						exit(1);
        			}
        			
        			copiaPilha.pop();
        			
        		}
			}

ERL         : '(' ERL ')'
			{
				$$.tipo = $2.tipo;
				$$.labelTemp = $2.labelTemp;
				$$.traducao = $2.traducao;
			}
 			| ERL TOKEN_MAIOR ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " > " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " > " + labelCasting +
					";\n";
					cout<< $1.labelTemp;
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " > " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_MENOR ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " < " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " < " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " < " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_MAIORIGUAL ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " >= " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " >= " + labelCasting +
					";\n";
					
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " >= " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_MENORIGUAL ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " <= " + $3.labelTemp +
					";\n";


				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " <= " + labelCasting +
					";\n";
				}
				else{		EL:
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " <= " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_DIF ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " != " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " != " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " != " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_IGUAL ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " == " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " == " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " == " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_E ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " && " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " && " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " && " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_OU ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " || " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " || " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " || " + $3.labelTemp +
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
				$$.labelTemp = $2.labelTemp;
				$$.traducao = $2.traducao;
			}
			| E '+' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " + " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " + " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " + " + $3.labelTemp +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " + " + $3.labelTemp +
					";\n";
				}

				
			}
			| E '-' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " - " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " - " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " - " + $3.labelTemp +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " - " + $3.labelTemp +
					";\n";
				}
				
			}
			| E '*' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " * " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " * " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " * " + $3.labelTemp +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " * " + $3.labelTemp +
					";\n";
				}
				
			}
			| E '/' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " / " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " / " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " / " + $3.labelTemp +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " / " + $3.labelTemp +
					";\n";
				}
			}
			| TOKEN_CONV_FLOAT E
			{
				$$.tipo = "float";
				
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.nomeVariavel + " = (float) " + $2.nomeVariavel +
				";\n";
			}
			| TOKEN_CONV_INT E
			{
				$$.tipo = "int";
				
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.nomeVariavel + " = (int) " + $2.nomeVariavel +
				";\n";
			}
			| '-' E
			{
				$$.tipo = $2.tipo;

				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.nomeVariavel + " = -" + $2.nomeVariavel +
				";\n";			
			}
			| E '+''+'
			{
				$$.tipo = $1.tipo;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $1.traducao + "\t" + $1.labelTemp + " = " + $1.labelTemp + " + 1 ;\n";
			}
			| E '-''-'
			{
				$$.tipo = $1.tipo;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $1.traducao + "\t" + $1.labelTemp + " = -" + $1.labelTemp + " - 1 ;\n";
			}
			| E_BASICA
			{ 
				$$.traducao = $1.traducao;
			}
			;

ES 			: TOKEN_STRING 
			{
				tipoGeral = 2;
				$$.tipo = "string";
				$$.labelTemp = geraLabelTemp($$.tipo);
				
				//remover aspas 	
				string removerAspas = $1.traducao;
				string semAspas = $1.traducao.erase(0, 1);
				int lenSemAspas = semAspas.length() - 1;
				$$.valor  = semAspas.erase(lenSemAspas, 1); //valor sem aspas
				$$.tamanho = $$.valor.length() + 1;					

				$$.varTamString	= geraLabelTemp("string_tam");
				$$.traducao = "\t" + $$.varTamString + " = " + to_string($$.tamanho) + ";\n\t" + $$.labelTemp + " = (char*)malloc(" + 
				$$.varTamString + " * sizeof(char));\n\t" + "strcat(" + $$.labelTemp + ", '" + $$.valor + "')" +
				";\n";
			}			
			| TOKEN_NOMEVAR
			{

                if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
					if(c.mapa[$1.nomeVariavel].tipo == "string"){
						if(c.mapa[$1.nomeVariavel].valor != "null"){						

							$$.nomeVariavel = $1.nomeVariavel;
							$$.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;							
							$$.valor = pilhaDeContextos.top().mapa[$$.nomeVariavel].valor;
							$$.tipo = pilhaDeContextos.top().mapa[$$.nomeVariavel].tipo;
							$$.tamanho =pilhaDeContextos.top().mapa[$$.nomeVariavel].tamanho;
							$$.varTamString = pilhaDeContextos.top().mapa[$$.nomeVariavel].varTamString;
							$$.traducao = ""; 

						}
						else{
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);									
					}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
			}
			;


CONCATENACAO : TOKEN_NOMEVAR TOKEN_ATR ES '.' ES
			{	
				if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);

                	if(c.mapa[$1.nomeVariavel].tipo == "string") {
						if(c.mapa[$1.nomeVariavel].valor != "null"){						

							$1.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;														
							$1.tamanho = pilhaDeContextos.top().mapa[$$.nomeVariavel].tamanho;							
							$1.varTamString = pilhaDeContextos.top().mapa[$$.nomeVariavel].varTamString;
							$1.tipo = pilhaDeContextos.top().mapa[$$.nomeVariavel].tipo;

						}
						else{
							$1.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;														
							$1.tamanho = 0;							
							$1.varTamString = geraLabelTemp("string_tam");
							$1.tipo = pilhaDeContextos.top().mapa[$$.nomeVariavel].tipo;
						}
						
							$$.labelTemp = geraLabelTemp($1.tipo);	
							string varTamString = geraLabelTemp("string_tam");
							string concat = "";
							concat = concat + $3.valor + $5.valor;
							$1.valor = 	concat;				
							$1.tamanho = $1.valor.length() - 1;

							

							$$.traducao = "\n\t//concatenacao\n" + $3.traducao + $5.traducao + "\n\t" + varTamString + " = " + $3.varTamString + " + " + $5.varTamString + ";\n" +
							"\t" + $$.labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +					
							"\tstrcat(" + $$.labelTemp + ", " + $3.labelTemp + ");\n" +
							"\tstrcat(" + $$.labelTemp + ", " + $5.labelTemp + ");\n" +
							"\tfree( " + $1.labelTemp + " );\n" + 
							"\t" + $1.labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +
							"\tstrcat(" + $1.labelTemp + ", " + $$.labelTemp + ");\n" + 
							"\t"+ $1.varTamString + " = " + varTamString + ";\n";									
										
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);									
					}
				}				
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}	
			}
			;

PRINT 		: TOKEN_PRINT '(' CONTEUDO_PRINT ')'
			{
				$$.traducao = $3.traducao;
			}


CONTEUDO_PRINT: TOKEN_NUM_INT MAIS_PRINT 
				{
					$$.labelTemp = geraLabelTemp("int");				
					$$.traducao = "\t" + $$.labelTemp + " = " + $1.valor + ";\n\tcout << " + $$.labelTemp + " << endl;\n" + $2.traducao;
				}
				| TOKEN_NUM_FLOAT MAIS_PRINT 
				{
					$$.labelTemp = geraLabelTemp("float");				
					$$.traducao = "\t" + $$.labelTemp + " = " + $1.valor + ";\n\tcout << " + $$.labelTemp + " << endl;\n" + $2.traducao;
				}
				| TOKEN_BOOL MAIS_PRINT 
				{
					$$.labelTemp = geraLabelTemp("bool");				
					$$.traducao = "\t" + $$.labelTemp + " = " + $1.valor + ";\n\tcout << " + $$.labelTemp + " << endl;\n" + $2.traducao;
				}
				| TOKEN_STRING MAIS_PRINT
				{
					$$.labelTemp = geraLabelTemp("string");	
					$$.varTamString = geraLabelTemp("string_tam");			

					//remover aspas 	
					string removerAspas = $1.traducao;
					string semAspas = $1.traducao.erase(0, 1);
					int lenSemAspas = semAspas.length() - 1;
					$$.valor  = semAspas.erase(lenSemAspas, 1); //valor sem aspas
					$$.tamanho = $$.valor.length() + 1;

					$$.traducao = "\n\t" + $$.varTamString + " = " + to_string($$.tamanho) + ";\n\t" + $$.labelTemp + " = (char*)malloc(" + 
					$$.varTamString + " * sizeof(char));\n\t" + "strcat(" + $$.labelTemp + ", '" + $$.valor + "')" +
					";\n\tcout << " + $$.labelTemp + " << endl;\n" + $2.traducao;
				}
				| TOKEN_CHAR MAIS_PRINT 
				{
					$$.labelTemp = geraLabelTemp("char");				
					$$.traducao = "\t" + $$.labelTemp + " = " + $1.valor + ";\n\tcout << " + $$.labelTemp + " << endl;\n" + $2.traducao;
				}
				| TOKEN_NOMEVAR MAIS_PRINT 
				{
					if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
	                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
	                	if(c.mapa[$1.nomeVariavel].valor != "null"){      
	                		$1.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;		          		                		
	                		$$.traducao = "\tcout << " + c.mapa[$1.nomeVariavel].labelTemp +" << endl;\n" + $2.traducao;
	                	}
						else {
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);	
						}            
	                }
	                else{
						indicaErro(MSG_ERRO_NDECLARADA);
						exit(1);									
					}	
				}

MAIS_PRINT:	',' CONTEUDO_PRINT
			{
				$$.traducao = $2.traducao;
			}	
			|	
			{
				$$.traducao = "";
			}
		
SCANF 		: TOKEN_SCANF '(' TOKEN_NOMEVAR ')'
			{
				if(variavelExistente($3.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($3.nomeVariavel);
                	if(c.mapa[$3.nomeVariavel].tipo == "int") {                		
                		$$.traducao = "\tscanf(\"%d\", &" + c.mapa[$3.nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[$3.nomeVariavel].tipo == "float") {
                		$$.traducao = "\tscanf(\"%f\", &" + c.mapa[$3.nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[$3.nomeVariavel].tipo == "char") {
                		$$.traducao = "\tscanf(\"%c\", &" + c.mapa[$3.nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[$3.nomeVariavel].tipo == "string") {
                		string varTamString = c.mapa[$3.nomeVariavel].varTamString;
                	
                		string var = c.mapa[$3.nomeVariavel].labelTemp;
                		string varT = geraLabelTemp("char");
                		string numVarT = geraLabelTemp("string_tam");
                		string rotI = "ROT_STR_LET_IN_" + to_string(nCL);
                		string rotF = "ROT_STR_LET_FIM_" + to_string(nCL);

                		$$.traducao = "\tif (" + varTamString + " > 0) free(" + var + ");\n" +
						"\t" + var + " = (char*) malloc(" + varTamString +" * sizeof(char));\n" +
						"\t" + numVarT + " = " + varTamString + "\n" + 
						"\t" + varTamString + " = 0;\n\t" + rotI + ":\n" + 						
						'\t' + varT + " = getchar();\n" + 
						"\tif(" + varT + " == \'\\0\' || " + varT + " == \'\\n\') goto " + rotF + ";\n" +
						'\t' + var + '[' + varTamString + "] = " + varT + ";\n" +
						'\t' + varTamString + " = " + varTamString + " + 1;\n" +
						"\tif(" + varTamString + " < " + numVarT + ") goto " + rotI + ";\n" +
						'\t' + varTamString + " = " + varTamString + " + " + numVarT + ";\n" +
						'\t' + var + " = (char*) realloc(" + var + ", " + varTamString + ");\n" + 
						"\tgoto " + rotI + ";\n" + '\t' + rotF + ":\n" +
						'\t' + varTamString + " = " + varTamString + " + 1;\n" +
						'\t' + var + '[' + varTamString + "] = \'\\0\';\n";						
                	}        
                }
                else{
					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}	
			}	


E_BASICA	: TOKEN_NUM_INT
			{
				tipoGeral = 1;
				$$.tipo = "int";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = $1.traducao;
				$$.traducao = "\t" + $$.labelTemp + " = " + $1.traducao +
				";\n";
			}
			| TOKEN_NUM_FLOAT
			{
				tipoGeral = 1;
				$$.tipo = "float";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = $1.traducao;
				$$.traducao = "\t" + $$.labelTemp + " = " + $1.traducao +
				";\n";
			}
			| TOKEN_NOMEVAR
			{

                if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
					if(c.mapa[$1.nomeVariavel].tipo == "float" || c.mapa[$1.nomeVariavel].tipo == "int"){
						if(c.mapa[$1.nomeVariavel].valor != "null"){						


							$$.nomeVariavel = $1.nomeVariavel;
							$$.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;							
							$$.valor = pilhaDeContextos.top().mapa[$$.nomeVariavel].valor;
							$$.tipo = pilhaDeContextos.top().mapa[$$.nomeVariavel].tipo;
							$$.traducao = ""; 
							switchPar = $$.labelTemp;
						}
						else{
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);									
					}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
			}
			| TOKEN_BOOLEAN_FALSE
			{
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = "0";
				$$.traducao = "\t" + $$.labelTemp + " = " + $$.valor +
				";\n";
			}
			| TOKEN_BOOLEAN_TRUE
			{
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = "1";
				$$.traducao = "\t" + $$.labelTemp + " = " + $$.valor +
				";\n";
			}
			| TOKEN_CARACTERE
			{
				tipoGeral = 2;
				$$.tipo = "char";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = $1.traducao;
				$$.traducao = "\t" + $$.labelTemp + " = " + $1.traducao +
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
