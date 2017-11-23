/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "sintatica.y" /* yacc.c:339  */

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
 


#line 491 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_MAIN = 258,
    TOKEN_BEGIN = 259,
    TOKEN_INT = 260,
    TOKEN_FLOAT = 261,
    TOKEN_DOUBLE = 262,
    TOKEN_CHAR = 263,
    TOKEN_BOOL = 264,
    TOKEN_STR = 265,
    TOKEN_NULL = 266,
    TOKEN_VOID = 267,
    TOKEN_IF = 268,
    TOKEN_ELSE = 269,
    TOKEN_ELSEIF = 270,
    TOKEN_SWITCH = 271,
    TOKEN_CASE = 272,
    TOKEN_DEFAULT = 273,
    TOKEN_IMP = 274,
    TOKEN_BREAK = 275,
    TOKEN_CONTINUE = 276,
    TOKEN_DO = 277,
    TOKEN_FOR = 278,
    TOKEN_WHILE = 279,
    TOKEN_RETURN = 280,
    TOKEN_PRINT = 281,
    TOKEN_ERROR = 282,
    TOKEN_STRUCT = 283,
    TOKEN_NOMEVAR = 284,
    TOKEN_NUM_INT = 285,
    TOKEN_NUM_FLOAT = 286,
    TOKEN_BOOLEAN_FALSE = 287,
    TOKEN_BOOLEAN_TRUE = 288,
    TOKEN_CARACTERE = 289,
    TOKEN_STRING = 290,
    TOKEN_MAIOR = 291,
    TOKEN_MENOR = 292,
    TOKEN_DIF = 293,
    TOKEN_IGUAL = 294,
    TOKEN_MAIORIGUAL = 295,
    TOKEN_MENORIGUAL = 296,
    TOKEN_E = 297,
    TOKEN_OU = 298,
    TOKEN_CONV_FLOAT = 299,
    TOKEN_CONV_INT = 300,
    TOKEN_ATR = 301,
    TOKEN_SCANF = 302,
    TOKEN_COMENT = 303,
    TOKEN_COM_INT = 304,
    TOKEN_COM_END = 305,
    TOKEN_LINECOMENT = 306
  };
#endif
/* Tokens.  */
#define TOKEN_MAIN 258
#define TOKEN_BEGIN 259
#define TOKEN_INT 260
#define TOKEN_FLOAT 261
#define TOKEN_DOUBLE 262
#define TOKEN_CHAR 263
#define TOKEN_BOOL 264
#define TOKEN_STR 265
#define TOKEN_NULL 266
#define TOKEN_VOID 267
#define TOKEN_IF 268
#define TOKEN_ELSE 269
#define TOKEN_ELSEIF 270
#define TOKEN_SWITCH 271
#define TOKEN_CASE 272
#define TOKEN_DEFAULT 273
#define TOKEN_IMP 274
#define TOKEN_BREAK 275
#define TOKEN_CONTINUE 276
#define TOKEN_DO 277
#define TOKEN_FOR 278
#define TOKEN_WHILE 279
#define TOKEN_RETURN 280
#define TOKEN_PRINT 281
#define TOKEN_ERROR 282
#define TOKEN_STRUCT 283
#define TOKEN_NOMEVAR 284
#define TOKEN_NUM_INT 285
#define TOKEN_NUM_FLOAT 286
#define TOKEN_BOOLEAN_FALSE 287
#define TOKEN_BOOLEAN_TRUE 288
#define TOKEN_CARACTERE 289
#define TOKEN_STRING 290
#define TOKEN_MAIOR 291
#define TOKEN_MENOR 292
#define TOKEN_DIF 293
#define TOKEN_IGUAL 294
#define TOKEN_MAIORIGUAL 295
#define TOKEN_MENORIGUAL 296
#define TOKEN_E 297
#define TOKEN_OU 298
#define TOKEN_CONV_FLOAT 299
#define TOKEN_CONV_INT 300
#define TOKEN_ATR 301
#define TOKEN_SCANF 302
#define TOKEN_COMENT 303
#define TOKEN_COM_INT 304
#define TOKEN_COM_END 305
#define TOKEN_LINECOMENT 306

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 644 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   396

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  253

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      57,    58,    55,    53,    52,    54,    62,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    61,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,     2,    60,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   499,   499,   509,   513,   517,   522,   526,   527,   531,
     539,   546,   553,   559,   568,   577,   582,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   597,   598,   599,
     600,   601,   603,   609,   615,   620,   625,   637,   657,   670,
     690,   703,   728,   741,   771,   783,   813,   825,   844,   849,
     861,   874,   879,   891,   904,   909,   922,   941,   947,   959,
     972,   977,   981,   987,  1002,  1017,  1034,  1046,  1062,  1076,
    1093,  1109,  1125,  1140,  1149,  1153,  1157,  1163,  1174,  1179,
    1189,  1210,  1229,  1235,  1271,  1306,  1342,  1378,  1413,  1448,
    1483,  1518,  1524,  1530,  1573,  1615,  1657,  1698,  1706,  1714,
    1722,  1728,  1734,  1740,  1758,  1794,  1847,  1853,  1858,  1863,
    1868,  1884,  1889,  1908,  1913,  1917,  1962,  1971,  1980,  2012,
    2020,  2028
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_MAIN", "TOKEN_BEGIN", "TOKEN_INT",
  "TOKEN_FLOAT", "TOKEN_DOUBLE", "TOKEN_CHAR", "TOKEN_BOOL", "TOKEN_STR",
  "TOKEN_NULL", "TOKEN_VOID", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_ELSEIF",
  "TOKEN_SWITCH", "TOKEN_CASE", "TOKEN_DEFAULT", "TOKEN_IMP",
  "TOKEN_BREAK", "TOKEN_CONTINUE", "TOKEN_DO", "TOKEN_FOR", "TOKEN_WHILE",
  "TOKEN_RETURN", "TOKEN_PRINT", "TOKEN_ERROR", "TOKEN_STRUCT",
  "TOKEN_NOMEVAR", "TOKEN_NUM_INT", "TOKEN_NUM_FLOAT",
  "TOKEN_BOOLEAN_FALSE", "TOKEN_BOOLEAN_TRUE", "TOKEN_CARACTERE",
  "TOKEN_STRING", "TOKEN_MAIOR", "TOKEN_MENOR", "TOKEN_DIF", "TOKEN_IGUAL",
  "TOKEN_MAIORIGUAL", "TOKEN_MENORIGUAL", "TOKEN_E", "TOKEN_OU",
  "TOKEN_CONV_FLOAT", "TOKEN_CONV_INT", "TOKEN_ATR", "TOKEN_SCANF",
  "TOKEN_COMENT", "TOKEN_COM_INT", "TOKEN_COM_END", "TOKEN_LINECOMENT",
  "','", "'+'", "'-'", "'*'", "'/'", "'('", "')'", "'{'", "'}'", "';'",
  "'.'", "$accept", "S", "BLOCO_GLOBAL", "EMP_GLOBAL", "BLOCO_MAIN",
  "EMP_MAIN", "BLOCO_NI", "EMP_NI", "BLOCO_LOOP", "BLOCO_SWITCH",
  "EMP_LOOP", "COMANDOS", "COMANDO", "ATR_RL", "ATR", "DCL_GLOBAL", "DCL",
  "MLTVAR_INT", "MLTVAR_FLOAT", "MLTVAR_CHAR", "MLTVAR_STRING",
  "MLTVAR_BOOL", "COMENT", "IF", "ELSE", "ELSEIF", "WHILE", "DO_WHILE",
  "FOR", "SWITCH", "CASES", "CASE", "DEFAULT", "CASE_VALUE", "BREAK",
  "CONTINUE", "ERL", "E", "ES", "CONCATENACAO", "PRINT", "CONTEUDO_PRINT",
  "MAIS_PRINT", "SCANF", "E_BASICA", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,    44,    43,    45,    42,    47,    40,    41,   123,
     125,    59,    46
};
# endif

#define YYPACT_NINF -172

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-172)))

#define YYTABLE_NINF -105

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -52,    12,    16,   135,  -172,   -24,  -172,    -9,  -172,    13,
    -172,    56,    -1,    49,    63,    65,    74,  -172,    46,   126,
     126,   126,    52,   -37,   -10,    -3,     1,     8,   135,    55,
      64,  -172,  -172,  -172,    66,     0,    67,    84,    85,    80,
     100,    93,   126,  -172,  -172,   102,  -172,  -172,  -172,  -172,
    -172,  -172,   113,   122,   125,   128,   136,    94,   138,   129,
     127,   167,  -172,   127,   185,  -172,   127,   188,  -172,     0,
     195,  -172,    26,   197,  -172,  -172,     0,   179,     0,   126,
    -172,  -172,  -172,  -172,  -172,  -172,     0,   353,  -172,    10,
     171,   193,   206,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,   127,   127,   127,   127,   114,
    -172,    25,   265,    27,   291,    28,   336,    30,  -172,  -172,
     203,    37,   299,   204,   261,     0,   313,     0,     0,     0,
       0,     0,     0,     0,     0,  -172,   207,   207,   207,   207,
     207,   207,   194,   196,   217,   273,     9,   198,   328,  -172,
     211,  -172,  -172,  -172,    35,   137,   200,   234,   127,   127,
    -172,   127,  -172,  -172,   127,  -172,  -172,   127,  -172,  -172,
       0,  -172,  -172,    26,  -172,  -172,  -172,  -172,   287,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,   201,   201,    10,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,    26,  -172,
    -172,  -172,    35,   251,    35,  -172,  -172,   114,   265,   291,
     336,   203,    71,   212,   215,   127,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,   216,  -172,  -172,   214,    97,   165,
    -172,     0,  -172,   179,   257,   219,    97,  -172,  -172,   322,
     267,  -172,   126,  -172,  -172,  -172,  -172,   126,  -172,    71,
    -172,  -172,  -172
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,    35,     4,     0,     7,     0,     8,     0,
       1,     0,     0,     0,     0,     0,     0,     3,     0,    16,
      16,    16,     0,    48,    51,    54,    60,    57,    35,     0,
       0,    80,    81,    14,     0,     0,     0,     0,     0,     0,
       0,     0,    16,    19,    18,     0,    31,    22,    24,    25,
      26,    23,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,    38,     0,     0,    40,     0,
       0,    44,     0,     0,    42,    34,     0,     0,     0,    17,
     118,   116,   117,   119,   120,   121,     0,    14,    91,     0,
       0,     0,     0,    62,     6,    15,    20,    27,    30,    21,
      29,    28,    10,    12,     9,     0,     0,     0,     0,    48,
     102,    48,    51,    51,    54,    54,    60,    60,   104,   103,
      57,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,   114,   114,   114,   114,
     114,   114,     0,   118,     0,     0,     0,     0,    91,    61,
       0,     2,    97,    98,    99,     0,     0,     0,     0,     0,
      37,     0,    46,    39,     0,    49,    41,     0,    52,    45,
       0,    58,    43,     0,    55,    11,    14,    71,     0,    82,
      83,    84,    87,    88,    85,    86,    89,    90,     0,   111,
     109,   112,   107,   108,   110,   106,    32,    33,     0,   115,
      92,   100,    93,   101,    94,    95,    96,    48,    51,    54,
      60,    57,    63,     0,     0,     0,   113,   105,    47,    50,
      53,    59,    56,    11,     0,    65,    64,     0,     0,     0,
      66,     0,    73,     0,     0,     0,    76,    75,    14,     0,
       0,    79,    16,    13,    74,    72,    11,    16,    78,    67,
      77,    69,    68
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -172,  -172,  -172,  -172,   183,  -172,  -171,  -172,   -31,  -172,
     116,   -20,   210,  -172,  -172,   262,    20,  -103,  -102,  -101,
     -95,  -100,  -172,  -172,    44,    45,  -172,  -172,  -172,  -172,
      69,  -172,  -172,  -172,  -172,  -172,   -32,    21,   -85,  -172,
    -172,   118,   229,  -172,   -39
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     4,     5,     6,     7,     8,   213,
       9,    41,    42,    43,    44,    17,    45,    62,    65,    68,
      74,    71,    46,    47,   225,   226,    48,    49,    50,    51,
     235,   236,   237,   240,    52,    53,   126,   154,   120,    54,
      55,   142,   189,    56,    88
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    58,    78,    87,   212,   147,   160,    -9,   162,    60,
     163,   165,    10,   166,   168,    61,   169,   171,   136,   137,
      11,   110,    95,    18,   110,   172,   174,   110,    23,    80,
      81,    82,    83,    84,    85,    19,    63,   116,   123,   138,
     139,   140,    64,    66,   122,   141,   124,    69,    18,    67,
      20,   148,   230,    70,    72,   118,   135,    86,   145,    22,
      73,   119,   156,   157,   158,   159,   110,   110,   110,   110,
     197,   161,    21,   164,   167,   249,   170,    61,    24,    64,
      67,   109,    70,   173,   112,   223,   224,   114,   211,    73,
     158,   159,    25,   178,    26,   180,   181,   182,   183,   184,
     185,   186,   187,    27,   218,   148,   219,    28,   220,    59,
     221,   146,    76,   217,   233,   234,   222,   110,   110,   110,
     110,    77,   110,    79,    89,   110,   152,   153,   110,   155,
      90,    12,    13,    91,    14,    15,    16,    92,   210,    29,
      12,    13,    30,    14,    15,    16,    31,    32,    33,    34,
      35,    93,    36,    94,   102,    37,    80,    81,    82,    83,
      84,    85,    38,    96,   110,   155,    61,   156,   157,   158,
     159,   105,   106,    39,    97,    40,   110,   202,   204,   205,
     206,   107,   207,    98,   108,   208,    99,   104,   209,   100,
     156,   157,   158,   159,   241,   200,   111,   101,   103,   239,
     143,    81,    82,    83,    84,    85,   119,   245,    80,    81,
      82,    83,    84,    85,   113,   105,   106,   115,   156,   157,
     158,   159,   248,   238,   117,   107,   121,   250,   144,    80,
      81,    82,    83,    84,    85,   150,   229,   127,   128,   129,
     130,   131,   132,   149,   105,   106,    80,    81,    82,    83,
      84,    85,   195,   201,   107,    73,   176,   108,  -104,   188,
     198,   105,   106,    80,    81,    82,    83,    84,    85,   199,
     227,   107,   228,   231,   144,   232,   242,   243,   105,   106,
      80,    81,    82,    83,    84,    85,   247,   151,   203,   125,
      75,   108,   214,   251,   252,   105,   106,   127,   128,   129,
     130,   131,   132,   133,   134,   244,   216,     0,   108,   127,
     128,   129,   130,   131,   132,   133,   134,    64,   156,   157,
     158,   159,   177,   127,   128,   129,   130,   131,   132,   133,
     134,     0,     0,     0,   196,   127,   128,   129,   130,   131,
     132,   133,   134,    67,   156,   157,   158,   159,   215,   127,
     128,   129,   130,   131,   132,   133,   134,   175,   127,   128,
     129,   130,   131,   132,   133,   134,   190,   191,   192,   193,
     194,   179,   127,   128,   129,   130,   131,   132,   133,   134,
     246,  -102,  -102,  -102,  -102,     0,     0,     0,    70,   127,
     128,   129,   130,   131,   132,   133,   134
};

static const yytype_int16 yycheck[] =
{
      20,    21,    33,    35,   175,    90,   109,    59,   111,    46,
     112,   113,     0,   114,   115,    52,   116,   117,     8,     9,
       4,    60,    42,     3,    63,   120,   121,    66,    29,    29,
      30,    31,    32,    33,    34,    59,    46,    69,    77,    29,
      30,    31,    52,    46,    76,    35,    78,    46,    28,    52,
      59,    90,   223,    52,    46,    29,    87,    57,    90,     3,
      52,    35,    53,    54,    55,    56,   105,   106,   107,   108,
      61,    46,    59,    46,    46,   246,    46,    52,    29,    52,
      52,    60,    52,    46,    63,    14,    15,    66,   173,    52,
      55,    56,    29,   125,    29,   127,   128,   129,   130,   131,
     132,   133,   134,    29,   207,   144,   208,    61,   209,    57,
     210,    90,    57,   198,    17,    18,   211,   156,   157,   158,
     159,    57,   161,    57,    57,   164,   105,   106,   167,   108,
      46,     5,     6,    48,     8,     9,    10,    57,   170,    13,
       5,     6,    16,     8,     9,    10,    20,    21,    22,    23,
      24,    51,    26,    60,    60,    29,    29,    30,    31,    32,
      33,    34,    36,    61,   203,   144,    52,    53,    54,    55,
      56,    44,    45,    47,    61,    49,   215,   156,   157,   158,
     159,    54,   161,    61,    57,   164,    61,    58,   167,    61,
      53,    54,    55,    56,   233,    58,    29,    61,    60,   231,
      29,    30,    31,    32,    33,    34,    35,   238,    29,    30,
      31,    32,    33,    34,    29,    44,    45,    29,    53,    54,
      55,    56,   242,    58,    29,    54,    29,   247,    57,    29,
      30,    31,    32,    33,    34,    29,   215,    36,    37,    38,
      39,    40,    41,    50,    44,    45,    29,    30,    31,    32,
      33,    34,    58,    53,    54,    52,    52,    57,    62,    52,
      62,    44,    45,    29,    30,    31,    32,    33,    34,    58,
      58,    54,    57,    57,    57,    61,    19,    58,    44,    45,
      29,    30,    31,    32,    33,    34,    19,   104,    54,    79,
      28,    57,   176,   249,   249,    44,    45,    36,    37,    38,
      39,    40,    41,    42,    43,   236,   188,    -1,    57,    36,
      37,    38,    39,    40,    41,    42,    43,    52,    53,    54,
      55,    56,    61,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    61,    36,    37,    38,    39,    40,
      41,    42,    43,    52,    53,    54,    55,    56,    61,    36,
      37,    38,    39,    40,    41,    42,    43,    58,    36,    37,
      38,    39,    40,    41,    42,    43,   137,   138,   139,   140,
     141,    58,    36,    37,    38,    39,    40,    41,    42,    43,
      58,    53,    54,    55,    56,    -1,    -1,    -1,    52,    36,
      37,    38,    39,    40,    41,    42,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    64,    65,    66,    67,    68,    69,    70,    71,    73,
       0,     4,     5,     6,     8,     9,    10,    78,    79,    59,
      59,    59,     3,    29,    29,    29,    29,    29,    61,    13,
      16,    20,    21,    22,    23,    24,    26,    29,    36,    47,
      49,    74,    75,    76,    77,    79,    85,    86,    89,    90,
      91,    92,    97,    98,   102,   103,   106,    74,    74,    57,
      46,    52,    80,    46,    52,    81,    46,    52,    82,    46,
      52,    84,    46,    52,    83,    78,    57,    57,    71,    57,
      29,    30,    31,    32,    33,    34,    57,    99,   107,    57,
      46,    48,    57,    51,    60,    74,    61,    61,    61,    61,
      61,    61,    60,    60,    58,    44,    45,    54,    57,   100,
     107,    29,   100,    29,   100,    29,    99,    29,    29,    35,
     101,    29,    99,   107,    99,    75,    99,    36,    37,    38,
      39,    40,    41,    42,    43,    71,     8,     9,    29,    30,
      31,    35,   104,    29,    57,    99,   100,   101,   107,    50,
      29,    67,   100,   100,   100,   100,    53,    54,    55,    56,
      80,    46,    80,    81,    46,    81,    82,    46,    82,    84,
      46,    84,    83,    46,    83,    58,    52,    61,    99,    58,
      99,    99,    99,    99,    99,    99,    99,    99,    52,   105,
     105,   105,   105,   105,   105,    58,    61,    61,    62,    58,
      58,    53,   100,    54,   100,   100,   100,   100,   100,   100,
      99,   101,    69,    72,    73,    61,   104,   101,    80,    81,
      82,    84,    83,    14,    15,    87,    88,    58,    57,   100,
      69,    57,    61,    17,    18,    93,    94,    95,    58,    99,
      96,   107,    19,    58,    93,    71,    58,    19,    74,    69,
      74,    87,    88
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    65,    65,    66,    67,    67,    67,    68,
      69,    70,    71,    72,    73,    74,    74,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    76,    77,    78,    78,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    80,    80,    80,    81,
      81,    81,    82,    82,    82,    83,    83,    83,    84,    84,
      84,    85,    85,    86,    86,    86,    87,    88,    88,    88,
      89,    90,    91,    92,    93,    93,    93,    94,    95,    96,
      97,    98,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   101,   101,   102,   103,   104,   104,   104,
     104,   104,   104,   105,   105,   106,   107,   107,   107,   107,
     107,   107
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     2,     1,     0,     4,     1,     1,     0,
       4,     0,     4,     4,     0,     2,     0,     0,     1,     1,
       2,     2,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     1,     4,     4,     3,     0,     3,     5,     3,     5,
       3,     5,     3,     5,     3,     5,     3,     5,     0,     3,
       5,     0,     3,     5,     0,     3,     5,     0,     3,     5,
       0,     3,     2,     5,     6,     6,     2,     5,     6,     6,
       3,     4,     8,     7,     2,     1,     1,     4,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     3,     3,     2,     2,     2,
       3,     3,     1,     1,     1,     5,     4,     2,     2,     2,
       2,     2,     2,     2,     0,     4,     1,     1,     1,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 500 "sintatica.y" /* yacc.c:1646  */
    {
            	
            	(yyval).labelTemp = geraLabelFinal();
				cout << "/*Compilador ITL*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\nint main(void){\n" <<
				(yyval).labelTemp << (yyvsp[-5]).traducao +(yyvsp[0]).traducao << "\treturn 0;\n}" << endl; 							
				
			}
#line 1942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 510 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 517 "sintatica.y" /* yacc.c:1646  */
    {	
				//Empilha o Escopo Global
				empilhaMapa(0,"","");
			}
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 523 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 1967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 531 "sintatica.y" /* yacc.c:1646  */
    {

				//Empilha o Main
				empilhaMapa(0,"","");
				

			}
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 540 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 1987 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 546 "sintatica.y" /* yacc.c:1646  */
    {
				//Empilha o Bloco não interrompível
				empilhaMapa(0,"","");
				

			}
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 554 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 560 "sintatica.y" /* yacc.c:1646  */
    {
				

				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2016 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 568 "sintatica.y" /* yacc.c:1646  */
    {
				//Empilha o Bloco interrompível
				empilhaMapa(1,geraRotulo(),geraRotulo());
				

			}
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 578 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			}
#line 2035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 582 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 604 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = verificaErros((yyvsp[-3]), (yyvsp[-1]), 2);
			}
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 610 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = verificaErros((yyvsp[-3]), (yyvsp[-1]), 1);
			}
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 616 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
			}
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 620 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2075 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 626 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "int";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;
					adicionaVariavelContexto((yyval));
										
				}
			}
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 638 "sintatica.y" /* yacc.c:1646  */
    {
				
				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					(yyval).tipo = "int";
					(yyval).valor = (yyvsp[-1]).valor;			

					if((yyvsp[-1]).tipo != (yyval).tipo ){																
						indicaErro(MSG_ERRO_TIPO);
						exit(1);		
					}				
					(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).valor = (yyvsp[-1]).traducao;
					(yyval).traducao = (yyvsp[-1]).traducao + "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" + (yyvsp[0]).traducao; 

					adicionaVariavelContexto((yyval));
				}

			}
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 658 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					
					(yyval).tipo = "float";
					(yyval).valor = "null";		
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;

					adicionaVariavelContexto((yyval));
				}	
			}
#line 2132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 671 "sintatica.y" /* yacc.c:1646  */
    {

				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){

					(yyval).tipo = "float";
					(yyval).valor = (yyvsp[-1]).valor;

					if((yyvsp[-1]).tipo != (yyval).tipo ){																
						indicaErro(MSG_ERRO_TIPO);
						exit(1);		
					}
					(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-1]).traducao +  "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" + (yyvsp[0]).traducao; 

					adicionaVariavelContexto((yyval));
				}

			}
#line 2156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 691 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "char";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;

					adicionaVariavelContexto((yyval));
				}

			}
#line 2173 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 704 "sintatica.y" /* yacc.c:1646  */
    {

				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					if(tipoGeral == 2){
						(yyval).tipo = "char";
						(yyval).valor = (yyvsp[-1]).valor;

						if((yyvsp[-1]).tipo != (yyval).tipo ){																
							indicaErro(MSG_ERRO_TIPO);
							exit(1);		
						}
						(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
						(yyval).labelTemp = geraLabelTemp((yyval).tipo);
						(yyval).traducao = (yyvsp[-1]).traducao +  "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" + (yyvsp[0]).traducao; 

						adicionaVariavelContexto((yyval));
					}else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}

				}

			}
#line 2202 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 729 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "string";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).varTamString = geraLabelTemp("string_tam");
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;
					adicionaVariavelContexto((yyval));
				}

			}
#line 2219 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 742 "sintatica.y" /* yacc.c:1646  */
    {

				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					if(tipoGeral == 2){
						(yyval).tipo = "string";
						(yyval).valor = (yyvsp[-1]).valor;						

						if((yyvsp[-1]).tipo != (yyval).tipo ){																
							indicaErro(MSG_ERRO_TIPO);
							exit(1);		
						}

						(yyval).tamanho = (yyvsp[-1]).tamanho;
						(yyval).varTamString = (yyvsp[-1]).varTamString;
						(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;						
						(yyval).labelTemp = (yyvsp[-1]).labelTemp;
						(yyval).varTamString	= (yyvsp[-1]).varTamString;

						(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao; 

						adicionaVariavelContexto((yyval));
					}else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}

				}

			}
#line 2253 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 772 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "bool";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;

					adicionaVariavelContexto((yyval));
				}
			}
#line 2269 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 784 "sintatica.y" /* yacc.c:1646  */
    {

				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					if ((yyvsp[-1]).valor == "0" || (yyvsp[-1]).valor == "1"){
						(yyval).tipo = "bool";
						(yyval).valor = (yyvsp[-1]).valor;				

						
						if((yyvsp[-1]).tipo != (yyval).tipo ){																
							indicaErro(MSG_ERRO_TIPO);
							exit(1);		
						}
						(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
						(yyval).labelTemp = geraLabelTemp((yyval).tipo);
						(yyval).traducao = (yyvsp[-1]).traducao +  "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" + (yyvsp[0]).traducao; 

						adicionaVariavelContexto((yyval));	
					}
					else {
						indicaErro(MSG_ERRO_TIPO);
						std::cout <<(yyvsp[-1]).valor<< std::endl;			
						exit(1);
					}
					
				}

			}
#line 2301 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 814 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "int";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = "";
					
					adicionaVariavelContexto((yyval));
				}
			}
#line 2317 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 826 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					(yyval).tipo = "int";
					(yyval).valor = (yyvsp[-1]).valor;

					if((yyvsp[-1]).tipo != (yyval).tipo ){																
						indicaErro(MSG_ERRO_TIPO);
						exit(1);		
					}				
								
					(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao + (yyvsp[-1]).traducao + "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" ;

					adicionaVariavelContexto((yyval));
				}
			}
#line 2339 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 844 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2347 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 850 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "float";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = "";

					adicionaVariavelContexto((yyval));
				}
			}
#line 2363 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 862 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					(yyval).tipo = "float";
					(yyval).valor = (yyvsp[-1]).valor;
					(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao + (yyvsp[-1]).traducao + "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" ;
					
					adicionaVariavelContexto((yyval));
				}
			}
#line 2379 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 874 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 880 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "char";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = "";

					adicionaVariavelContexto((yyval));
				}
			}
#line 2403 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 892 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					(yyval).tipo = "char";
					(yyval).valor = (yyvsp[-1]).valor;
					(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao + (yyvsp[-1]).traducao + "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" ;
					
					adicionaVariavelContexto((yyval));
				}
			}
#line 2419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 904 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2427 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 910 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "string";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).varTamString = geraLabelTemp("string_tam");
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = "";

					adicionaVariavelContexto((yyval));
				}
			}
#line 2444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 923 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					(yyval).tipo = "string";
					
					(yyval).valor = (yyvsp[-1]).valor;
					(yyval).tamanho = (yyvsp[-1]).tamanho;
					(yyval).varTamString = (yyvsp[-1]).varTamString;
					(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;						
					(yyval).labelTemp = (yyvsp[-1]).labelTemp;
					(yyval).varTamString	= (yyvsp[-1]).varTamString;


					(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao ;
					
					adicionaVariavelContexto((yyval));
				}
			}
#line 2466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 941 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 948 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "bool";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = "";

					adicionaVariavelContexto((yyval));
				}
			}
#line 2490 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 960 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					(yyval).tipo = "bool";
					(yyval).valor = (yyvsp[-1]).valor;
					(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao + (yyvsp[-1]).traducao + "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" ;
					
					adicionaVariavelContexto((yyval));
				}
			}
#line 2506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 972 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 978 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "\n\t/*" + (yyvsp[-1]).traducao + "*/\n\n";
			}
#line 2522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 982 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "\n\t/" + (yyvsp[0]).traducao + "\n";
			}
#line 2530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 988 "sintatica.y" /* yacc.c:1646  */
    {	

				string sFimIF = geraRotulo();

					
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//IF COMEÇA\n" + (yyvsp[-2]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-2]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto "+ sFimIF +";\n" + (yyvsp[0]).traducao +
				"\n\t"+ sFimIF +":\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();
			}
#line 2549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1003 "sintatica.y" /* yacc.c:1646  */
    {		

				string sElseIF = geraRotulo(); 
				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//IF COMEÇA\n"+(yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-3]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto " + sElseIF +";\n" +
				(yyvsp[-1]).traducao + "\tgoto "+ sFimIFs +";\n\n\t" + sElseIF +":\n" + (yyvsp[0]).traducao;        	
        		
        		desempilhaMapa();

			}
#line 2568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1018 "sintatica.y" /* yacc.c:1646  */
    {		
        		string sFimIF = geraRotulo();       	
        		string sElse = geraRotulo();
				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//IF COMEÇA\n"+(yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-3]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto "+  sElse + ";\n" +
				(yyvsp[-1]).traducao +"\t"+ sElse +":\n" + (yyvsp[0]).traducao;

				desempilhaMapa();
       		 	
			}
#line 2587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1035 "sintatica.y" /* yacc.c:1646  */
    {
  				sFimIFs = geraRotulo();      	        
  				string sElse = geraRotulo();  			
  				
  				(yyval).traducao = "\t//ELSE COMEÇA\n" + (yyvsp[0]).traducao+"\t" + 
				sFimIFs +":\n\t//ELSE TERMINA\n\t"+
				"//IF TERMINA\n\n";
  				
  				desempilhaMapa();
			}
#line 2602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1047 "sintatica.y" /* yacc.c:1646  */
    {		
        		sFimIFs = geraRotulo();
				
				string sElseIF = geraRotulo();      			
      							
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t//ELSEIF COMEÇA\n"+(yyvsp[-2]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-2]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto " + sFimIFs + ";\n" +
				(yyvsp[0]).traducao + 
				"\n\t" + sFimIFs + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();				
			}
#line 2622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1063 "sintatica.y" /* yacc.c:1646  */
    {		
				string sFimIF = geraRotulo();
				string sElseIF = geraRotulo(); 				
        						
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//ELSEIF COMEÇA\n\t" + sElseIF + ":\n"+(yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-3]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto " + sFimIF + ";\n" +
				(yyvsp[-1]).traducao + "\n\t" + sFimIF + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();			
			}
#line 2640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1077 "sintatica.y" /* yacc.c:1646  */
    {
        		string sFimIF = geraRotulo();
				string sElse = geraRotulo();
				string sElseIF = geraRotulo();  				

				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t//ELSEIF COMEÇA\n"+ (yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-3]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto " + sElse +";\n" +
				(yyvsp[-1]).traducao + "\tgoto "+ sFimIFs +";\n\n\t" +sElse+":\n"+ (yyvsp[0]).traducao;
				desempilhaMapa();
			}
#line 2659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1094 "sintatica.y" /* yacc.c:1646  */
    {	
  				string sWhile = pilhaDeContextos.top().rotuloInicio;
  				string sFWhile = pilhaDeContextos.top().rotuloFim;				
				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t" + sWhile +":\n\t" + "//WHILE COMEÇA\n"+ (yyvsp[-1]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-1]).labelTemp + ";\n" +
				 "\tif("+(yyval).labelTemp+")goto "+sFWhile+"\n"+(yyvsp[0]).traducao+"\tgoto " + 
				sWhile +";\n\t"+ sFWhile + ":\n\t//WHILE TERMINA\n";
  				
  				desempilhaMapa();
			}
#line 2677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1110 "sintatica.y" /* yacc.c:1646  */
    {	
  				string sDWhile = pilhaDeContextos.top().rotuloInicio;
  				string sFDWhile = pilhaDeContextos.top().rotuloFim;				
				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t" + sDWhile +":\n"+ "\t//DO_WHILE COMEÇA\n"+ (yyvsp[-1]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-1]).labelTemp + ";\n" +
				(yyvsp[-2]).traducao+"\tif("+(yyval).labelTemp+") goto "+sFDWhile+";\n\tgoto " + 
				sDWhile +";\n\t"+ sFDWhile + ":\n\t//DO_WHILE TERMINA\n";
  				
  				desempilhaMapa();
			}
#line 2695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1126 "sintatica.y" /* yacc.c:1646  */
    {
				string sFor = pilhaDeContextos.top().rotuloInicio;
  				string sFFor = pilhaDeContextos.top().rotuloFim;	

				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t" + sFor +":\n"+"\t//FOR COMEÇA\n"+ (yyvsp[-5]).traducao + (yyvsp[-4]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-4]).labelTemp + ";\n" +
				 "\t" + "if("+(yyval).labelTemp+") goto "+ sFFor +";\n"+(yyvsp[0]).traducao + (yyvsp[-2]).traducao + "\tgoto "+sFor+";\n\t"+ sFFor + ":\n\t//FOR TERMINA\n";
  				
  				desempilhaMapa();
			}
#line 2712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1141 "sintatica.y" /* yacc.c:1646  */
    {

				(yyval).traducao = "\n\t//SWITCH COMEÇA\n" + (yyvsp[-2]).traducao + "\t" + sFSwitch +":\n\t//SWITCH TERMINA\n";

				desempilhaMapa();
			}
#line 2723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1150 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			}
#line 2731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1154 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;	
			}
#line 2739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1158 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1164 "sintatica.y" /* yacc.c:1646  */
    {

				string sFimIF = geraRotulo();
  				sFSwitch = pilhaDeContextos.top().rotuloFim;

				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[-2]).traducao + "\t"+ (yyval).labelTemp + " = !"+ (yyvsp[-2]).labelTemp + "\n\tif( "+(yyval).labelTemp+") goto " +sFimIF + ";\n"+ (yyvsp[0]).traducao + "\n\t" + sFimIF +":\n";
			}
#line 2761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1175 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao + "\n";
			}
#line 2769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1180 "sintatica.y" /* yacc.c:1646  */
    {

				(yyval).tipo = "bool";
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).labelTemp = geraLabelTemp("bool");				
				(yyval).traducao = (yyval).valor + "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).labelTemp + " == " + switchPar +";\n";
			}
#line 2781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1190 "sintatica.y" /* yacc.c:1646  */
    {
       			
				PilhaContexto copiaPilha = pilhaDeContextos;
        		while(!copiaPilha.empty()){
        			if(copiaPilha.top().interrompivel == 1){
        				(yyval).traducao = "\t//BREAK\n\tgoto " + copiaPilha.top().rotuloFim + ";\n";
        				
        				break;
        			}
        			if(copiaPilha.size() == 1){
        				indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
						exit(1);
        			}
        			
        			copiaPilha.pop();
        			
        		}
        		
      		}
#line 2805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1211 "sintatica.y" /* yacc.c:1646  */
    {
				PilhaContexto copiaPilha = pilhaDeContextos;
        		while(!copiaPilha.empty()){
        			if(copiaPilha.top().interrompivel == 1){
        				(yyval).traducao = "\t//CONTINUE\n\tgoto " + copiaPilha.top().rotuloInicio + ";\n";
        				
        				break;
        			}
        			if(copiaPilha.size() == 1){
        				indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
						exit(1);
        			}
        			
        			copiaPilha.pop();
        			
        		}
			}
#line 2827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1230 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).labelTemp = (yyvsp[-1]).labelTemp;
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1236 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " > " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " > " + labelCasting +
					";\n";
					cout<< (yyvsp[-2]).labelTemp;
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " > " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1272 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " < " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " < " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " < " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1307 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " >= " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " >= " + labelCasting +
					";\n";
					
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " >= " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1343 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " <= " + (yyvsp[0]).labelTemp +
					";\n";


				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " <= " + labelCasting +
					";\n";
				}
				else{		EL:
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " <= " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1379 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " != " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " != " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " != " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1414 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " == " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " == " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " == " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1449 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " && " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " && " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " && " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3113 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1484 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " || " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " || " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " || " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1519 "sintatica.y" /* yacc.c:1646  */
    { 
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 3160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1525 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).labelTemp = (yyvsp[-1]).labelTemp;
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 3170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1531 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " + " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " + " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " + " + (yyvsp[0]).labelTemp +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " + " + (yyvsp[0]).labelTemp +
					";\n";
				}

				
			}
#line 3217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1574 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " - " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " - " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " - " + (yyvsp[0]).labelTemp +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " - " + (yyvsp[0]).labelTemp +
					";\n";
				}
				
			}
#line 3263 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1616 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " * " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " * " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " * " + (yyvsp[0]).labelTemp +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " * " + (yyvsp[0]).labelTemp +
					";\n";
				}
				
			}
#line 3309 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1658 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " / " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " / " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " / " + (yyvsp[0]).labelTemp +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " / " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1699 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "float";
				
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).nomeVariavel + " = (float) " + (yyvsp[0]).nomeVariavel +
				";\n";
			}
#line 3366 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1707 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "int";
				
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).nomeVariavel + " = (int) " + (yyvsp[0]).nomeVariavel +
				";\n";
			}
#line 3378 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1715 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[0]).tipo;

				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).nomeVariavel + " = -" + (yyvsp[0]).nomeVariavel +
				";\n";			
			}
#line 3390 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1723 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[-2]).tipo;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[-2]).traducao + "\t" + (yyvsp[-2]).labelTemp + " = " + (yyvsp[-2]).labelTemp + " + 1 ;\n";
			}
#line 3400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1729 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[-2]).tipo;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[-2]).traducao + "\t" + (yyvsp[-2]).labelTemp + " = -" + (yyvsp[-2]).labelTemp + " - 1 ;\n";
			}
#line 3410 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1735 "sintatica.y" /* yacc.c:1646  */
    { 
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 3418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1741 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 2;
				(yyval).tipo = "string";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				
				//remover aspas 	
				string removerAspas = (yyvsp[0]).traducao;
				string semAspas = (yyvsp[0]).traducao.erase(0, 1);
				int lenSemAspas = semAspas.length() - 1;
				(yyval).valor  = semAspas.erase(lenSemAspas, 1); //valor sem aspas
				(yyval).tamanho = (yyval).valor.length() + 1;					

				(yyval).varTamString	= geraLabelTemp("string_tam");
				(yyval).traducao = "\t" + (yyval).varTamString + " = " + to_string((yyval).tamanho) + ";\n\t" + (yyval).labelTemp + " = (char*)malloc(" + 
				(yyval).varTamString + " * sizeof(char));\n\t" + "strcat(" + (yyval).labelTemp + ", '" + (yyval).valor + "')" +
				";\n";
			}
#line 3440 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1759 "sintatica.y" /* yacc.c:1646  */
    {

                if(variavelExistente((yyvsp[0]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[0]).nomeVariavel);
					if(c.mapa[(yyvsp[0]).nomeVariavel].tipo == "string"){
						if(c.mapa[(yyvsp[0]).nomeVariavel].valor != "null"){						

							(yyval).nomeVariavel = (yyvsp[0]).nomeVariavel;
							(yyval).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;							
							(yyval).valor = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].valor;
							(yyval).tipo = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tipo;
							(yyval).tamanho =pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tamanho;
							(yyval).varTamString = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].varTamString;
							(yyval).traducao = ""; 

						}
						else{
							std::cout <<c.mapa[(yyvsp[0]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
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
#line 3477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1795 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente((yyvsp[-4]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[-4]).nomeVariavel);

                	if(c.mapa[(yyvsp[-4]).nomeVariavel].tipo == "string") {
						if(c.mapa[(yyvsp[-4]).nomeVariavel].valor != "null"){						

							(yyvsp[-4]).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;														
							(yyvsp[-4]).tamanho = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tamanho;							
							(yyvsp[-4]).varTamString = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].varTamString;
							(yyvsp[-4]).tipo = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tipo;

						}
						else{
							(yyvsp[-4]).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;														
							(yyvsp[-4]).tamanho = 0;							
							(yyvsp[-4]).varTamString = geraLabelTemp("string_tam");
							(yyvsp[-4]).tipo = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tipo;
						}
						
							(yyval).labelTemp = geraLabelTemp((yyvsp[-4]).tipo);	
							string varTamString = geraLabelTemp("string_tam");
							string concat = "";
							concat = concat + (yyvsp[-2]).valor + (yyvsp[0]).valor;
							(yyvsp[-4]).valor = 	concat;				
							(yyvsp[-4]).tamanho = (yyvsp[-4]).valor.length() - 1;

							

							(yyval).traducao = "\n\t//concatenacao\n" + (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\n\t" + varTamString + " = " + (yyvsp[-2]).varTamString + " + " + (yyvsp[0]).varTamString + ";\n" +
							"\t" + (yyval).labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +					
							"\tstrcat(" + (yyval).labelTemp + ", " + (yyvsp[-2]).labelTemp + ");\n" +
							"\tstrcat(" + (yyval).labelTemp + ", " + (yyvsp[0]).labelTemp + ");\n" +
							"\tfree( " + (yyvsp[-4]).labelTemp + " );\n" + 
							"\t" + (yyvsp[-4]).labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +
							"\tstrcat(" + (yyvsp[-4]).labelTemp + ", " + (yyval).labelTemp + ");\n" + 
							"\t"+ (yyvsp[-4]).varTamString + " = " + varTamString + ";\n";									
										
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
#line 3532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1848 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 3540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1854 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).labelTemp = geraLabelTemp("int");				
					(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).valor + ";\n\tcout << " + (yyval).labelTemp + " << endl;\n" + (yyvsp[0]).traducao;
				}
#line 3549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1859 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).labelTemp = geraLabelTemp("float");				
					(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).valor + ";\n\tcout << " + (yyval).labelTemp + " << endl;\n" + (yyvsp[0]).traducao;
				}
#line 3558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1864 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).labelTemp = geraLabelTemp("bool");				
					(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).valor + ";\n\tcout << " + (yyval).labelTemp + " << endl;\n" + (yyvsp[0]).traducao;
				}
#line 3567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1869 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).labelTemp = geraLabelTemp("string");	
					(yyval).varTamString = geraLabelTemp("string_tam");			

					//remover aspas 	
					string removerAspas = (yyvsp[-1]).traducao;
					string semAspas = (yyvsp[-1]).traducao.erase(0, 1);
					int lenSemAspas = semAspas.length() - 1;
					(yyval).valor  = semAspas.erase(lenSemAspas, 1); //valor sem aspas
					(yyval).tamanho = (yyval).valor.length() + 1;

					(yyval).traducao = "\n\t" + (yyval).varTamString + " = " + to_string((yyval).tamanho) + ";\n\t" + (yyval).labelTemp + " = (char*)malloc(" + 
					(yyval).varTamString + " * sizeof(char));\n\t" + "strcat(" + (yyval).labelTemp + ", '" + (yyval).valor + "')" +
					";\n\tcout << " + (yyval).labelTemp + " << endl;\n" + (yyvsp[0]).traducao;
				}
#line 3587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1885 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).labelTemp = geraLabelTemp("char");				
					(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).valor + ";\n\tcout << " + (yyval).labelTemp + " << endl;\n" + (yyvsp[0]).traducao;
				}
#line 3596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1890 "sintatica.y" /* yacc.c:1646  */
    {
					if(variavelExistente((yyvsp[-1]).nomeVariavel, 'e')){ //Se a variável existir...
	                	Contexto c = retornarContextoDaVariavel((yyvsp[-1]).nomeVariavel);
	                	if(c.mapa[(yyvsp[-1]).nomeVariavel].valor != "null"){      
	                		(yyvsp[-1]).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;		          		                		
	                		(yyval).traducao = "\tcout << " + c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp +" << endl;\n" + (yyvsp[0]).traducao;
	                	}
						else {
							std::cout <<c.mapa[(yyvsp[-1]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);	
						}            
	                }
	                else{
						indicaErro(MSG_ERRO_NDECLARADA);
						exit(1);									
					}	
				}
#line 3618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1909 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 3626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1913 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 3634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1918 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[-1]).nomeVariavel);
                	if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == "int") {                		
                		(yyval).traducao = "\tscanf(\"%d\", &" + c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == "float") {
                		(yyval).traducao = "\tscanf(\"%f\", &" + c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == "char") {
                		(yyval).traducao = "\tscanf(\"%c\", &" + c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == "string") {
                		string varTamString = c.mapa[(yyvsp[-1]).nomeVariavel].varTamString;
                	
                		string var = c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp;
                		string varT = geraLabelTemp("char");
                		string numVarT = geraLabelTemp("string_tam");
                		string rotI = "ROT_STR_LET_IN_" + to_string(nCL);
                		string rotF = "ROT_STR_LET_FIM_" + to_string(nCL);

                		(yyval).traducao = "\tif (" + varTamString + " > 0) free(" + var + ");\n" +
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
#line 3681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1963 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 1;
				(yyval).tipo = "int";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 3694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1972 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 1;
				(yyval).tipo = "float";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 3707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1981 "sintatica.y" /* yacc.c:1646  */
    {

                if(variavelExistente((yyvsp[0]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[0]).nomeVariavel);
					if(c.mapa[(yyvsp[0]).nomeVariavel].tipo == "float" || c.mapa[(yyvsp[0]).nomeVariavel].tipo == "int"){
						if(c.mapa[(yyvsp[0]).nomeVariavel].valor != "null"){						


							(yyval).nomeVariavel = (yyvsp[0]).nomeVariavel;
							(yyval).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;							
							(yyval).valor = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].valor;
							(yyval).tipo = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tipo;
							(yyval).traducao = ""; 
							switchPar = (yyval).labelTemp;
						}
						else{
							std::cout <<c.mapa[(yyvsp[0]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
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
#line 3743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 2013 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = "0";
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyval).valor +
				";\n";
			}
#line 3755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 2021 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = "1";
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyval).valor +
				";\n";
			}
#line 3767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 2029 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 2;
				(yyval).tipo = "char";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 3780 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3784 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2040 "sintatica.y" /* yacc.c:1906  */


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
