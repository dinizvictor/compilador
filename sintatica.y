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


typedef std::stack<Contexto> PilhaContexto;


static PilhaContexto pilhaDeContextos;

void empilhaMapa(){

	Contexto c;
	pilhaDeContextos.push(c);

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
string MSG_ERRO_CONTEXTONAOINTERROMPIVEL = "\nErrore:\nerrore de contesto\n";

void yyerror(string);

static int ctdDInt = 0, ctdDFloat = 0, ctdDChar = 0, ctdDBool = 0;
static int fazCasting;
static int tipoGeral;
static int ctdLinhas = 1;
static string switchPar;
static int ctdIf = 0, ctdEIf = 0, ctdIfE = 0, ctdElse = 0, ctdWhile = 0,ctdFor = 0; ; 

void indicaErro(string MSG){

	std::cout<<MSG<<"Linea "<<ctdLinhas<<std::endl;

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

void setarContexto(bool interrompivel, string labelI, string labelF){

	if(!pilhaDeContextos.empty()){
		cout<<pilhaDeContextos.size()<<endl;
		cout<<"Inte: "<<interrompivel<<endl;
		cout<<"labelI: "<<labelI<<endl;
		cout<<"labelF: "<<labelF<<endl;
		pilhaDeContextos.top().interrompivel = interrompivel;
		pilhaDeContextos.top().labelInicio = labelI;
		pilhaDeContextos.top().labelFim = labelF;
	}

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

%token TOKEN_NULL
%token TOKEN_VOID
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_ELSEIF
%token TOKEN_SWITCH
%token TOKEN_CASE
%token TOKEN_DEFAULT
  
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

S		    : TOKEN_BEGIN TOKEN_MAIN '(' ')' '{' BLOCO 
            {
            	setarContexto(0, "", "");
            	$$.labelTemp = geraLabelFinal();
				cout << "/*Compilador ITL*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void){\n" <<
				$$.labelTemp << $6.traducao << "\treturn 0;\n}" << endl; 							
				
			}
BLOCO		:  COMANDOS '}'
			{
				$$.traducao = $1.traducao;
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
			| DO_WHILE
			| FOR
			| SWITCH
			| BREAK ';'
     	 	| CONTINUE ';'
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
IF 		: TOKEN_IF '(' ERL ')' '{' BLOCO
			{		
				string sFimIF = "FIM_IF_" + to_string(ctdIf);
					
				setarContexto(0, "", sFimIF);
				cout<<"Trad:"<<pilhaDeContextos.top().labelFim<<endl;
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//IF COMEÇA\n" + $3.traducao +
				"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
				"\tif(!" + $$.labelTemp + ") goto "+ sFimIF +";\n" + $6.traducao +
				"\n\t"+ sFimIF +":\n\t//IF TERMINA\n\n";
				ctdIf += 1;
				desempilhaMapa();
			}
			| 
  			TOKEN_IF '(' ERL ')' '{' BLOCO ELSEIF
			{		
        		string sFimIF = "FIM_IF_" + to_string(ctdIf);
				string sElseIF = "ELSE_IF_" + to_string(ctdEIf);
				
				setarContexto(0, "", sFimIF);
				cout<<pilhaDeContextos.top().labelFim<<endl; 
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//IF COMEÇA\n"+$3.traducao +
				"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
				"\tif(!" + $$.labelTemp + ") goto " + sElseIF +"\n" +
				$6.traducao + "\tgoto "+ sFimIF +";\n" + $7.traducao;        	
        		ctdIf += 1;
        		ctdEIf += 1;
        		desempilhaMapa();

			}
			| TOKEN_IF '(' ERL ')' '{' BLOCO ELSE
			{		
        		string sFimIF = "FIM_IF_" + to_string(ctdIf);        	
        		string sElse = "ELSE_" + to_string(ctdElse) ;
        
				setarContexto(0, "", sFimIF);
				cout<<pilhaDeContextos.top().labelFim<<endl;

				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//IF COMEÇA\n"+$3.traducao +
				"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
				"\tif(!" + $$.labelTemp + ") goto "+  sElse + ";\n" +
				$6.traducao + $7.traducao; 
				desempilhaMapa();
       		 	
			}
			;

ELSE: TOKEN_ELSE '{' BLOCO 
			{
  				string sFimIF = "FIM_IF_" + to_string(ctdIf);        	        
  				string sElse = "ELSE_" + to_string(ctdElse) ;

  				setarContexto(0, "", sElse);
  				cout<<pilhaDeContextos.top().labelFim<<endl;

  				$$.traducao = "\n\tgoto " + sFimIF + ";\n"+
				"\n\t//ELSE COMEÇA\n\t"+ sElse + ":\n" + $3.traducao+"\t"+ sFimIF +":\n\t//ELSE TERMINA\n\t"+
				"//IF TERMINA\n\n";
  				ctdElse += 1;
  				desempilhaMapa();
			}
			;
ELSEIF  	: TOKEN_ELSEIF '(' ERL ')' '{' BLOCO
			{		
				string sFimIF = "FIM_IF_" + to_string(ctdIf);
				string sElseIF = "ELSE_IF_" + to_string(ctdEIf);  				

      			setarContexto(0, "", sFimIF);
      			cout<<pilhaDeContextos.top().labelFim<<endl;
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//ELSEIF COMEÇA\n\t" + sElseIF + ":\n"+$3.traducao +
				"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
				"\tif(!" + $$.labelTemp + ") goto " + sFimIF + ";\n" +
				$6.traducao + 
				"\n\t" + sFimIF + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				ctdEIf += 1;
				desempilhaMapa();				
			}
			| TOKEN_ELSEIF '(' ERL ')' '{' BLOCO ELSEIF
			{		
				string sFimIF = "FIM_IF_" + to_string(ctdIf);
				string sElseIF = "ELSE_IF_" + to_string(ctdEIf);  				

        		setarContexto(0, "", sFimIF);
        		cout<<pilhaDeContextos.top().labelFim<<endl;
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//ELSEIF COMEÇA\n\t" + sElseIF + ":\n"+$3.traducao +
				"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
				"\tif(!" + $$.labelTemp + ") goto " + sFimIF + ";\n" +
				$6.traducao + 
				"\n\t" + sFimIF + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				ctdEIf += 1;
				desempilhaMapa();			
			}
			| TOKEN_ELSEIF '(' ERL ')' '{' BLOCO ELSE
			{
        		string sFimIF = "FIM_IF_" + to_string(ctdIf);
				string sElse = "ELSE_" + to_string(ctdElse) ;
				string sElseIF = "ELSE_IF_" + to_string(ctdEIf);  				

				setarContexto(0, "", sFimIF);
				cout<<pilhaDeContextos.top().labelFim<<endl;

				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//" + sElseIF +" COMEÇA\n\tELSEIF:\n"+ $3.traducao +
				"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
				"\tif(!" + $$.labelTemp + ") goto " + sElse +";\n" +
				$6.traducao + $7.traducao;
				desempilhaMapa();
			}
			;

WHILE 		: TOKEN_WHILE '(' ERL ')' '{' BLOCO
			{	
  				string sWhile = "WHILE_" + to_string(ctdWhile);
  				string sFWhile = "FIM_WHILE_" + to_string(ctdWhile);

				setarContexto(1, sWhile, sFWhile);
				cout<<pilhaDeContextos.top().labelFim<<endl;

				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//WHILE COMEÇA\n"+ $3.traducao +
				"\t" + $$.labelTemp + " = " + $3.labelTemp + ";\n" +
				"\t" + "if("+$$.labelTemp+"){\n\t"+ sWhile +":\n"+$6.traducao+"\t}if("+$$.labelTemp+") goto "+ sWhile +";\n\t"+ sFWhile + ":\n\t//WHILE TERMINA\n";
  				ctdWhile += 1;
  				desempilhaMapa();
			}
			;

DO_WHILE	: TOKEN_DO '{' BLOCO TOKEN_WHILE '(' ERL ')' ';'
			{
				string sDWhile = "DO_WHILE_" + to_string(ctdWhile);
  				string sFDWhile = "FIM_DO_WHILE_" + to_string(ctdWhile);
				
				setarContexto(1, sDWhile, sFDWhile);				
				cout<<pilhaDeContextos.top().labelFim<<endl;

				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//DO WHILE COMEÇA\n"+ $6.traducao +
				"\t" + $$.labelTemp + " = !" + $6.labelTemp + ";\n" +
				"\t" + "\n\t"+ sDWhile +":\n"+$3.traducao+"\tif("+$$.labelTemp+") goto "+ sDWhile +";\n\t"+ sFDWhile + ":\n\t//DO WHILE TERMINA\n";
  				ctdWhile += 1;
  				desempilhaMapa();
			}
			;

FOR			: TOKEN_FOR '('COMANDO ERL ';' FOR_INC ')' '{' BLOCO		
			{
				string sFor = "FOR_" + to_string(ctdFor);
  				string sFFor = "FIM_DO_FOR_" + to_string(ctdFor);

				setarContexto(1, sFor, sFFor);
				cout<<pilhaDeContextos.top().labelFim<<endl;

				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//FOR COMEÇA\n"+ $3.traducao + $4.traducao +
				"\t" + $$.labelTemp + " = !" + $4.labelTemp + ";\n" +
				"\t" + "if("+$$.labelTemp+")goto "+ sFFor +"\n\t"+ sFor +":\n"+$9.traducao + $6.traducao +"\tif("+$$.labelTemp+") goto "+ sFor +";\n\t"+ sFFor + ":\n\t//FOR TERMINA\n";
  				ctdFor += 1;
  				desempilhaMapa();
			}
						;
FOR_INC     : E_BASICA '+''+'
			{	
				$$.tipo = "int";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t"+ $$.labelTemp + " = " + $1.labelTemp + " + 1;\n"
							  +"\t" + $1.labelTemp + " = " + $$.labelTemp+ ";\n"; 
			}
			| E_BASICA '-''-'
			{	
				$$.tipo = "int";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t"+ $$.labelTemp + " = " + $1.labelTemp + " - 1;\n"
							  +"\t" + $1.labelTemp + " = " + $$.labelTemp+ ";\n"; 
			}
			;

SWITCH 		: TOKEN_SWITCH '(' E_BASICA ')' '{' CASES '}'
			{
				switchPar = $3.traducao;
				$$.traducao = "\t"+ $3.traducao + $6.traducao + "\n";
			}
			;

CASES 		: CASE CASES 
			{
				$$.traducao = $1.traducao + $2.traducao;
			}	
			| DEFAULT
      		{
        		$$.traducao = $1.traducao;
      		}
      		| CASE
			{
				$$.traducao = $1.traducao;
			}
			;
			
CASE 		: TOKEN_CASE  CASE_VALUE  ':' COMANDOS
			{
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t" + $2.traducao + "if( "+$2.labelTemp+ " == "+switchPar+")"+ $4.traducao ;
			}
			;

CASE_VALUE	: E_BASICA
			{
				$$.tipo = $1.tipo;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t" + $$.labelTemp + " = " + $1.labelTemp + ";\n";
			}

DEFAULT 	: TOKEN_DEFAULT ':' COMANDOS
			{
				$$.traducao = $3.traducao;
			}
			;


BREAK       : TOKEN_BREAK
			{
       			
				cout<<"TAMANHO DA PILHA: "<<pilhaDeContextos.size()<<endl;
        		PilhaContexto pilhaAux;
        		while(!pilhaDeContextos.empty()){
        			if(pilhaDeContextos.top().interrompivel){
        				$$.traducao = "\n\t//BREAK\n\tgoto " + pilhaDeContextos.top().labelFim + ";\n";
        				break;
        			}
        			else if(pilhaDeContextos.size() == 1){
        				indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
						exit(1);
        			}
        			else{
        				pilhaAux.push(pilhaDeContextos.top());
        				pilhaDeContextos.pop();
        			}
        		}
        		while(!pilhaAux.empty()){

        			pilhaDeContextos.push(pilhaAux.top());
        			pilhaAux.pop();
        			
        		}

      		}

CONTINUE 	: TOKEN_CONTINUE
			{
				PilhaContexto pilhaAux;
        		while(!pilhaDeContextos.empty()){
        			if(pilhaDeContextos.top().interrompivel){
        				$$.traducao = "\n\t//CONTINUE\n\tgoto " + pilhaDeContextos.top().labelInicio + ";\n";
        				break;
        			}
        			else if(pilhaDeContextos.size() == 1){
        				indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
						exit(1);
        			}
        			else{
        				pilhaAux.push(pilhaDeContextos.top());
        				pilhaDeContextos.pop();
        			}
        		}
        		while(!pilhaAux.empty()){

        			pilhaDeContextos.push(pilhaAux.top());
        			pilhaAux.pop();
        			
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
