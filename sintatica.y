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
};

typedef	std::map<string,Atributos> MapaDeVariaveis;

struct Contexto{
	MapaDeVariaveis mapa;
	bool interrompivel;
	string labelInicio;
	string labelFim;
};

struct Erro{
	string mensagem;
	int linha;
};

typedef std::stack<Contexto> PilhaContexto;


static PilhaContexto pilhaDeContextos;

void empilhaMapa(){

	Contexto c;
	pilhaDeContextos.push(c);
	printf("{\n");

}

void desempilhaMapa(){

	pilhaDeContextos.pop();
	
}

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
static int ctdLinhas = 1;

void indicaErro(string MSG){

	std::cout<<MSG<<std::endl<<"Linea "<<ctdLinhas<<std::endl;

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

void criarContexto(bool interrompivel, string labelI, string labelF){

	pilhaDeContextos.top().interrompivel = interrompivel;
	pilhaDeContextos.top().labelInicio = labelI;
	pilhaDeContextos.top().labelFim = labelF;

}

string geraLabelTemp(string tipo){

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

void atualizarPilhaContextos(Atributos a){
	
	bool achou = 0;
	PilhaContexto pilhaAux;
	string variavel = pilhaDeContextos.top().mapa[a.nomeVariavel].labelTemp;
	if(variavel != ""){
		pilhaDeContextos.top().mapa[a.nomeVariavel] = a;
	}
	else if(pilhaDeContextos.size() > 1){
		pilhaAux.push(pilhaDeContextos.top());
		
		pilhaDeContextos.pop();

		do{

			variavel = pilhaDeContextos.top().mapa[a.nomeVariavel].labelTemp;
			cout<<variavel<<endl;
			if(variavel != ""){
				
				pilhaDeContextos.top().mapa[a.nomeVariavel] = a;
				achou = 1;

			}
			

			pilhaAux.push(pilhaDeContextos.top());
			pilhaDeContextos.pop();
			

		}while(pilhaDeContextos.size() > 0 || !achou);
		
		//Retornando os contextos para a pilhaDeContextos...

		while(!pilhaAux.empty()){
			
			pilhaDeContextos.push(pilhaAux.top());
			pilhaAux.pop();
			printf("%d\n", pilhaDeContextos.size());

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

		}while(copiaPilha.size() > 1);

	}

	return c;

}

//'e' de encontrar - PARA SABER SE A VARIAVEL JA FOI DECLARADA 
//'d' de declarar - PARA SABER SE PODE DECLARAR 

bool verificaNosContextosAnteriores(string nomeVariavel, char opcao){
	string variavel;
	cout<<nomeVariavel<<endl;
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
		
		}while(copiaPilha.size() > 1);

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

		}while(copiaPilha.size() > 1);

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

%token TOKEN_NULL
%token TOKEN_VOID
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_ELSEIF
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
            	$$.labelTemp = geraLabelFinal();
				cout << "/*Compilador ITL*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void){\n" <<
				$$.labelTemp << $5.traducao << "\treturn 0;\n}" << endl; 							
			}
			;

BLOCO		: '{' COMANDOS '}'
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
			| IF
			| WHILE
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
					std::cout <<"label de a: "<<pilhaDeContextos.top().mapa["a"].labelTemp<< std::endl;
					
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
IF 			: TOKEN_IF '(' ERL ')' BLOCO
			{		
					//criarContexto(0, "", "FIM_IF"); O ERRO ESTAVA AQUI!
					$$.tipo = "bool";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "\n\t//IF COMEÇA\n" + $3.traducao +
					"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
					"\tif(!" + $$.labelTemp + ") goto FIM_IF;\n" + $5.traducao +
					"\n\tFIM_IF:\n\t//IF TERMINA\n\n";
					
			}
			| TOKEN_IF '(' ERL ')' BLOCO ELSEIF
			{
					//criarContexto(0, "ELSEIF", "");
					$$.tipo = "bool";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "\n\t//IF COMEÇA\n"+$3.traducao +
					"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
					"\tif(!" + $$.labelTemp + ") goto ELSEIF:;\n" +
					$5.traducao + $6.traducao;
			}
			| TOKEN_IF '(' ERL ')' BLOCO TOKEN_ELSE BLOCO
			{
					//criarContexto(0, "ELSE", "FIM_ELSE");
					$$.tipo = "bool";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "\n\t//IF COMEÇA\n"+$3.traducao +
					"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
					"\tif(!" + $$.labelTemp + ") goto ELSE;\n" +
					$5.traducao +"\tgoto FIM_ELSE;\n"+
					"\n\t//ELSE COMEÇA\n\tELSE:\n" + $7.traducao+"\tFIM_ELSE:\n\t//ELSE TERMINA\n\t"+
					"//IF TERMINA\n\n";
			}
			;

ELSEIF  	: TOKEN_ELSEIF '(' ERL ')' BLOCO
			{		
					//criarContexto(0, "ELSEIF", "FIM_ELSEIF");
					$$.tipo = "bool";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "\n\t//ELSEIF COMEÇA\n\tELSEIF:\n"+$3.traducao +
					"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
					"\tif(!" + $$.labelTemp + ") goto FIM_ELSEIF;\n" +
					$5.traducao + 
					"\n\tFIM_ELSEIF:\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";

			}
			| TOKEN_ELSEIF '(' ERL ')' BLOCO TOKEN_ELSE BLOCO
			{
					//criarContexto(0, "ELSEIF", "FIM_ELSE");
					$$.tipo = "bool";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "\n\t//ELSEIF COMEÇA\n\tELSEIF:\n"+$3.traducao +
					"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
					"\tif(!" + $$.labelTemp + ") goto ELSE;\n" +
					$5.traducao + "\tgoto FIM_ELSE;\n"+
					"\n\t//ELSE COMEÇA\n\tELSE:\n" + $7.traducao+"\tFIM_ELSE:\n\t//ELSE TERMINA\n\t"+
					"//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
			}
			;

WHILE 		: TOKEN_WHILE '(' ERL ')' BLOCO
			{	
				//criarContexto(1, "WHILE", "");
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//WHILE COMEÇA\n"+ $3.traducao +
					"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
					"\t" + "if("+$3.labelTemp+"){\n\tWHILE:\n"+$5.traducao+"\t}if("+$3.labelTemp+") goto WHILE;\n\t//WHILE TERMINA\n";
			}
			;

ERL         : '(' ERL ')'
			{
				$$.tipo = $2.tipo;
				$$.labelTemp = $2.labelTemp;
				$$.traducao = $2.traducao;
			}
 			| ERL TOKEN_MAIOR ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " > " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " > " + labelCasting +
					";\n";
				}
				else{		

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " > " + $3.labelTemp +
					";\n";
				}

			}
			| ERL TOKEN_MENOR ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " < " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " < " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " < " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_MAIORIGUAL ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " >= " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " >= " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " >= " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_MENORIGUAL ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " <= " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " <= " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " <= " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_DIF ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " != " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " != " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " != " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_IGUAL ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " == " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " == " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " == " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_E ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " && " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " && " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " && " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_OU ERL
			{
				$$.tipo = "bool";
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " || " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " || " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " || " + $3.labelTemp +
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
			| E_BASICA
			{ 
				$$.traducao = $1.traducao;
			}
			;

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
