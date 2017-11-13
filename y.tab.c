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
static int ctdIf = 0, ctdEIf = 0, ctdIfE = 0, ctdElse = 0, ctdWhile = 0, ctdFor = 0; 

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
	printf("%d\n",pilhaDeContextos.size());
	if(!pilhaDeContextos.empty()){
		
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
 


#line 461 "y.tab.c" /* yacc.c:339  */

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
    TOKEN_NULL = 265,
    TOKEN_VOID = 266,
    TOKEN_IF = 267,
    TOKEN_ELSE = 268,
    TOKEN_ELSEIF = 269,
    TOKEN_SWITCH = 270,
    TOKEN_CASE = 271,
    TOKEN_DEFAULT = 272,
    TOKEN_BREAK = 273,
    TOKEN_CONTINUE = 274,
    TOKEN_DO = 275,
    TOKEN_FOR = 276,
    TOKEN_WHILE = 277,
    TOKEN_RETURN = 278,
    TOKEN_PRINT = 279,
    TOKEN_ERROR = 280,
    TOKEN_STRUCT = 281,
    TOKEN_NOMEVAR = 282,
    TOKEN_NUM_INT = 283,
    TOKEN_NUM_FLOAT = 284,
    TOKEN_BOOLEAN_FALSE = 285,
    TOKEN_BOOLEAN_TRUE = 286,
    TOKEN_CARACTERE = 287,
    TOKEN_MAIOR = 288,
    TOKEN_MENOR = 289,
    TOKEN_DIF = 290,
    TOKEN_IGUAL = 291,
    TOKEN_MAIORIGUAL = 292,
    TOKEN_MENORIGUAL = 293,
    TOKEN_E = 294,
    TOKEN_OU = 295,
    TOKEN_CONV_FLOAT = 296,
    TOKEN_CONV_INT = 297,
    TOKEN_ATR = 298
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
#define TOKEN_NULL 265
#define TOKEN_VOID 266
#define TOKEN_IF 267
#define TOKEN_ELSE 268
#define TOKEN_ELSEIF 269
#define TOKEN_SWITCH 270
#define TOKEN_CASE 271
#define TOKEN_DEFAULT 272
#define TOKEN_BREAK 273
#define TOKEN_CONTINUE 274
#define TOKEN_DO 275
#define TOKEN_FOR 276
#define TOKEN_WHILE 277
#define TOKEN_RETURN 278
#define TOKEN_PRINT 279
#define TOKEN_ERROR 280
#define TOKEN_STRUCT 281
#define TOKEN_NOMEVAR 282
#define TOKEN_NUM_INT 283
#define TOKEN_NUM_FLOAT 284
#define TOKEN_BOOLEAN_FALSE 285
#define TOKEN_BOOLEAN_TRUE 286
#define TOKEN_CARACTERE 287
#define TOKEN_MAIOR 288
#define TOKEN_MENOR 289
#define TOKEN_DIF 290
#define TOKEN_IGUAL 291
#define TOKEN_MAIORIGUAL 292
#define TOKEN_MENORIGUAL 293
#define TOKEN_E 294
#define TOKEN_OU 295
#define TOKEN_CONV_FLOAT 296
#define TOKEN_CONV_INT 297
#define TOKEN_ATR 298

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

#line 598 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   296

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

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
      49,    50,    47,    45,    44,    46,     2,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    54,    53,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   461,   461,   468,   475,   480,   485,   492,   499,   500,
     504,   508,   512,   516,   520,   546,   575,   587,   607,   620,
     640,   653,   678,   690,   720,   732,   751,   756,   768,   781,
     786,   798,   811,   816,   828,   841,   845,   859,   873,   889,
     900,   916,   932,   949,   963,   977,   990,   999,  1006,  1010,
    1014,  1020,  1028,  1035,  1041,  1047,  1081,  1114,  1147,  1180,
    1213,  1246,  1279,  1312,  1318,  1324,  1367,  1409,  1451,  1492,
    1500,  1508,  1516,  1522,  1531,  1540,  1575,  1583,  1591
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_MAIN", "TOKEN_BEGIN", "TOKEN_INT",
  "TOKEN_FLOAT", "TOKEN_DOUBLE", "TOKEN_CHAR", "TOKEN_BOOL", "TOKEN_NULL",
  "TOKEN_VOID", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_ELSEIF", "TOKEN_SWITCH",
  "TOKEN_CASE", "TOKEN_DEFAULT", "TOKEN_BREAK", "TOKEN_CONTINUE",
  "TOKEN_DO", "TOKEN_FOR", "TOKEN_WHILE", "TOKEN_RETURN", "TOKEN_PRINT",
  "TOKEN_ERROR", "TOKEN_STRUCT", "TOKEN_NOMEVAR", "TOKEN_NUM_INT",
  "TOKEN_NUM_FLOAT", "TOKEN_BOOLEAN_FALSE", "TOKEN_BOOLEAN_TRUE",
  "TOKEN_CARACTERE", "TOKEN_MAIOR", "TOKEN_MENOR", "TOKEN_DIF",
  "TOKEN_IGUAL", "TOKEN_MAIORIGUAL", "TOKEN_MENORIGUAL", "TOKEN_E",
  "TOKEN_OU", "TOKEN_CONV_FLOAT", "TOKEN_CONV_INT", "TOKEN_ATR", "','",
  "'+'", "'-'", "'*'", "'/'", "'('", "')'", "'{'", "'}'", "';'", "':'",
  "$accept", "S", "BLOCO", "COMANDOS", "COMANDO", "DCL", "MLTVAR_INT",
  "MLTVAR_FLOAT", "MLTVAR_CHAR", "MLTVAR_BOOL", "IF", "ELSE", "ELSEIF",
  "WHILE", "DO_WHILE", "FOR", "FOR_INC", "SWITCH", "CASES", "CASE",
  "CASE_VALUE", "DEFAULT", "ERL", "E", "E_BASICA", YY_NULLPTR
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
     295,   296,   297,   298,    44,    43,    45,    42,    47,    40,
      41,   123,   125,    59,    58
};
# endif

#define YYPACT_NINF -79

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-79)))

#define YYTABLE_NINF -73

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,    18,    38,   -26,   -79,    29,    -2,   140,    59,    61,
      67,    76,    66,    69,    54,    68,    85,    70,    88,    95,
     -79,    87,   140,    91,   -79,   -79,   -79,   -79,   -79,   -32,
     -28,     1,     8,    -1,   214,   -79,   -79,   140,   140,    -1,
     141,   -79,   -79,   -79,   147,   123,   -79,   147,   126,   -79,
     147,   127,   -79,    -1,   129,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,    -1,   172,   -79,   107,   142,    -1,   190,   147,
     147,   147,   141,    89,    45,    23,   147,    86,   -79,    11,
     243,    21,   248,    39,   242,    53,   198,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,   114,   117,   164,   130,
     -79,   -79,    58,   -13,   -79,   147,   147,   147,   147,   -79,
     -79,   147,   -79,   -79,   147,   -79,   -79,   147,   -79,   -79,
      -1,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   234,
     234,   140,    84,    -1,   214,   140,   -79,    58,    58,   -79,
     -79,    86,   243,   248,   242,    99,   214,   131,   128,    84,
     -79,   216,   134,   146,   -79,   -79,   -79,   -79,   -79,   135,
     143,   -79,   -79,   159,   -79,   140,   -79,   -79,   161,   144,
     149,   140,    -1,   140,   -79,   -79,   140,   -79,   -79,   224,
     -79,   -79,   165,   140,    99,   -79,   -79
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     0,     5,     0,     9,    11,    12,    13,    10,    26,
      29,    32,    35,     0,     0,    14,    15,     5,     0,     0,
       0,     3,     4,     8,     0,     0,    16,     0,     0,    18,
       0,     0,    20,     0,     0,    22,    75,    73,    74,    76,
      77,    78,     0,     0,    63,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    63,     0,    26,    72,    26,
      29,    29,    32,    32,    35,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      69,    70,    71,     0,     7,     0,     0,     0,     0,     6,
      17,     0,    24,    19,     0,    27,    21,     0,    30,    23,
       0,    33,    54,    55,    56,    59,    60,    57,    58,    61,
      62,     5,     0,     0,     0,     5,    64,    65,    66,    67,
      68,    26,    29,    32,    35,    36,     0,     0,     0,    49,
      50,     0,     0,     0,    43,    25,    28,    31,    34,     0,
       0,    38,    37,     0,    52,     5,    47,    48,     0,     0,
       0,     5,     0,     5,    53,    44,     5,    46,    39,     0,
      51,    45,     0,     5,    40,    42,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -79,   -79,   -36,   -22,   177,   -79,   -74,   -62,   -58,   -78,
     -79,    34,    35,   -79,   -79,   -79,   -79,   -79,    71,   -79,
     -79,   -79,   -31,     3,   -30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    20,    21,    22,    23,    46,    49,    52,    55,
      24,   161,   162,    25,    26,    27,   152,    28,   148,   149,
     163,   150,    86,   103,    64
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    66,    63,   110,    65,   112,   119,   121,    68,    73,
      75,    44,    45,     1,    78,    47,    48,    78,   113,   115,
      78,     3,    84,     5,   116,   118,    56,    57,    58,    59,
      60,    61,   105,   106,   107,   108,    98,   136,     4,    78,
      78,    78,    75,    74,    50,    51,    78,    77,    62,     7,
      80,    53,    54,    82,   111,    45,   123,   124,   125,   126,
     127,   128,   129,   130,   114,    48,   158,   155,   -72,   -72,
     -72,   -72,   100,   101,   102,    78,    78,    78,    78,     6,
     156,    78,   117,    51,    78,   157,    29,    78,    30,   144,
     105,   106,   107,   108,    31,   145,   120,    54,   109,   154,
     146,   147,   151,    32,   153,   107,   108,    35,   137,   138,
     139,   140,   159,   160,   141,    33,   164,   142,    34,    38,
     143,    36,    87,    88,    89,    90,    91,    92,    93,    94,
      45,   105,   106,   107,   108,   178,    37,    39,    40,    41,
     181,   179,   104,   174,    43,     8,     9,   184,    10,    11,
      79,   180,    12,    81,    83,    13,    85,    96,    14,    15,
      16,    17,    18,   131,    97,   132,   133,    19,    56,    57,
      58,    59,    60,    61,    56,    57,    58,    59,    60,    61,
     166,   135,    69,    70,   169,   165,   171,    71,    69,    70,
      72,   170,   172,    71,   177,   176,    76,    87,    88,    89,
      90,    91,    92,    93,    94,    87,    88,    89,    90,    91,
      92,    93,    94,   173,   175,    67,   183,   134,   185,   186,
     167,     0,    95,    87,    88,    89,    90,    91,    92,    93,
      94,    87,    88,    89,    90,    91,    92,    93,    94,     0,
      99,    56,    57,    58,    59,    60,    61,     0,   122,    87,
      88,    89,    90,    91,    92,    93,    94,    87,    88,    89,
      90,    91,    92,    93,    94,     0,   168,    87,    88,    89,
      90,    91,    92,     0,   182,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,     0,    54,    48,   105,   106,
     107,   108,    51,   105,   106,   107,   108
};

static const yytype_int16 yycheck[] =
{
      22,    37,    33,    77,    34,    79,    84,    85,    39,    40,
      40,    43,    44,     4,    44,    43,    44,    47,    80,    81,
      50,     3,    53,    49,    82,    83,    27,    28,    29,    30,
      31,    32,    45,    46,    47,    48,    67,    50,     0,    69,
      70,    71,    72,    40,    43,    44,    76,    44,    49,    51,
      47,    43,    44,    50,    43,    44,    87,    88,    89,    90,
      91,    92,    93,    94,    43,    44,   144,   141,    45,    46,
      47,    48,    69,    70,    71,   105,   106,   107,   108,    50,
     142,   111,    43,    44,   114,   143,    27,   117,    27,   120,
      45,    46,    47,    48,    27,   131,    43,    44,    53,   135,
      16,    17,   133,    27,   134,    47,    48,    53,   105,   106,
     107,   108,    13,    14,   111,    49,   146,   114,    49,    49,
     117,    53,    33,    34,    35,    36,    37,    38,    39,    40,
      44,    45,    46,    47,    48,   171,    51,    49,    43,    52,
     176,   172,    53,   165,    53,     5,     6,   183,     8,     9,
      27,   173,    12,    27,    27,    15,    27,    50,    18,    19,
      20,    21,    22,    51,    22,    51,    49,    27,    27,    28,
      29,    30,    31,    32,    27,    28,    29,    30,    31,    32,
      52,    51,    41,    42,    50,    54,    51,    46,    41,    42,
      49,    45,    49,    46,    45,    51,    49,    33,    34,    35,
      36,    37,    38,    39,    40,    33,    34,    35,    36,    37,
      38,    39,    40,    54,    53,    38,    51,    53,   184,   184,
     149,    -1,    50,    33,    34,    35,    36,    37,    38,    39,
      40,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      50,    27,    28,    29,    30,    31,    32,    -1,    50,    33,
      34,    35,    36,    37,    38,    39,    40,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    50,    33,    34,    35,
      36,    37,    38,    -1,    50,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    44,    44,    45,    46,
      47,    48,    44,    45,    46,    47,    48
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    56,     3,     0,    49,    50,    51,     5,     6,
       8,     9,    12,    15,    18,    19,    20,    21,    22,    27,
      57,    58,    59,    60,    65,    68,    69,    70,    72,    27,
      27,    27,    27,    49,    49,    53,    53,    51,    49,    49,
      43,    52,    58,    53,    43,    44,    61,    43,    44,    62,
      43,    44,    63,    43,    44,    64,    27,    28,    29,    30,
      31,    32,    49,    77,    79,    79,    57,    59,    77,    41,
      42,    46,    49,    77,    78,    79,    49,    78,    79,    27,
      78,    27,    78,    27,    77,    27,    77,    33,    34,    35,
      36,    37,    38,    39,    40,    50,    50,    22,    77,    50,
      78,    78,    78,    78,    53,    45,    46,    47,    48,    53,
      61,    43,    61,    62,    43,    62,    63,    43,    63,    64,
      43,    64,    50,    77,    77,    77,    77,    77,    77,    77,
      77,    51,    51,    49,    53,    51,    50,    78,    78,    78,
      78,    78,    78,    78,    77,    57,    16,    17,    73,    74,
      76,    77,    71,    79,    57,    61,    62,    63,    64,    13,
      14,    66,    67,    75,    79,    54,    52,    73,    50,    50,
      45,    51,    49,    54,    58,    53,    51,    45,    57,    77,
      58,    57,    50,    51,    57,    66,    67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    58,    58,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    60,    60,    60,    60,
      60,    60,    60,    60,    61,    61,    61,    62,    62,    62,
      63,    63,    63,    64,    64,    64,    65,    65,    65,    66,
      67,    67,    67,    68,    69,    70,    71,    72,    73,    73,
      73,    74,    75,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    79,    79,    79,    79,    79,    79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     2,     2,     0,     4,     4,     2,     1,
       1,     1,     1,     1,     2,     2,     3,     5,     3,     5,
       3,     5,     3,     5,     3,     5,     0,     3,     5,     0,
       3,     5,     0,     3,     5,     0,     6,     7,     7,     3,
       6,     7,     7,     6,     8,     9,     3,     7,     2,     1,
       1,     4,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     3,     3,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1
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
#line 462 "sintatica.y" /* yacc.c:1646  */
    {
            	(yyval).labelTemp = geraLabelFinal();
				cout << "/*Compilador ITL*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void){\n" <<
				(yyval).labelTemp << (yyvsp[0]).traducao << "\treturn 0;\n}" << endl; 							
				setarContexto(0, "", "");
			}
#line 1827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 469 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 1835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 476 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 480 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 1851 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 486 "sintatica.y" /* yacc.c:1646  */
    {

				(yyval).traducao = verificaErros((yyvsp[-3]), (yyvsp[-1]), 1);


			}
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 493 "sintatica.y" /* yacc.c:1646  */
    {

				(yyval).traducao = verificaErros((yyvsp[-3]), (yyvsp[-1]), 2);
		
			
			}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 501 "sintatica.y" /* yacc.c:1646  */
    {
				setarContexto(0,"","");
			}
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 505 "sintatica.y" /* yacc.c:1646  */
    {
				setarContexto(0,"","");
			}
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 509 "sintatica.y" /* yacc.c:1646  */
    {
				setarContexto(1,"","");
			}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 513 "sintatica.y" /* yacc.c:1646  */
    {
				setarContexto(1,"","");	
			}
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 517 "sintatica.y" /* yacc.c:1646  */
    {
				setarContexto(1,"","");	
			}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 521 "sintatica.y" /* yacc.c:1646  */
    {
       			
        		PilhaContexto pilhaAux;
        		while(!pilhaDeContextos.empty()){
        			if(pilhaDeContextos.top().interrompivel){
        				(yyval).traducao = "\n\t//BREAK\n\tgoto " + pilhaDeContextos.top().labelFim + ";\n";
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
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 547 "sintatica.y" /* yacc.c:1646  */
    {
      			
      			PilhaContexto pilhaAux;
        		while(!pilhaDeContextos.empty()){
        			if(pilhaDeContextos.top().interrompivel){
        				(yyval).traducao = "\n\t//CONTINUE\n\tgoto " + pilhaDeContextos.top().labelInicio + ";\n";
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
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 576 "sintatica.y" /* yacc.c:1646  */
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
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 588 "sintatica.y" /* yacc.c:1646  */
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
#line 2014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 608 "sintatica.y" /* yacc.c:1646  */
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
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 621 "sintatica.y" /* yacc.c:1646  */
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
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 641 "sintatica.y" /* yacc.c:1646  */
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
#line 2072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 654 "sintatica.y" /* yacc.c:1646  */
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
#line 2101 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 679 "sintatica.y" /* yacc.c:1646  */
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
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 691 "sintatica.y" /* yacc.c:1646  */
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
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 721 "sintatica.y" /* yacc.c:1646  */
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
#line 2165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 733 "sintatica.y" /* yacc.c:1646  */
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
#line 2187 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 751 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2195 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 757 "sintatica.y" /* yacc.c:1646  */
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
#line 2211 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 769 "sintatica.y" /* yacc.c:1646  */
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
#line 2227 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 781 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2235 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 787 "sintatica.y" /* yacc.c:1646  */
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
#line 2251 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 799 "sintatica.y" /* yacc.c:1646  */
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
#line 2267 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 811 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2275 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 817 "sintatica.y" /* yacc.c:1646  */
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
#line 2291 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 829 "sintatica.y" /* yacc.c:1646  */
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
#line 2307 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 841 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2315 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 846 "sintatica.y" /* yacc.c:1646  */
    {		
				string sFimIF = "FIM_IF_" + to_string(ctdIf);
					
				setarContexto(0, "", sFimIF); 
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//IF COMEÇA\n" + (yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = " + (yyvsp[-3]).labelTemp + ";\n" +
				"\tif(!" + (yyval).labelTemp + ") goto "+ sFimIF +";\n" + (yyvsp[0]).traducao +
				"\n\t"+ sFimIF +":\n\t//IF TERMINA\n\n";
				ctdIf += 1;
			}
#line 2332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 860 "sintatica.y" /* yacc.c:1646  */
    {		
        		string sFimIF = "FIM_IF_" + to_string(ctdIf);
				string sElseIF = "ELSE_IF_" + to_string(ctdEIf);
				setarContexto(0, "", sFimIF); 
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//IF COMEÇA\n"+(yyvsp[-4]).traducao +
				"\t" + (yyval).labelTemp + " = " + (yyvsp[-4]).labelTemp + ";\n" +
				"\tif(!" + (yyval).labelTemp + ") goto " + sElseIF +"\n" +
				(yyvsp[-1]).traducao + "\tgoto "+ sFimIF +";\n" + (yyvsp[0]).traducao;        	
        		ctdIf += 1;
        		ctdEIf += 1;
			}
#line 2350 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 874 "sintatica.y" /* yacc.c:1646  */
    {		
        		string sFimIF = "FIM_IF_" + to_string(ctdIf);        	
        		string sElse = "ELSE_" + to_string(ctdElse) ;
        
				setarContexto(0, "", sFimIF);
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//IF COMEÇA\n"+(yyvsp[-4]).traducao +
				"\t" + (yyval).labelTemp + " = " + (yyvsp[-4]).labelTemp + ";\n" +
				"\tif(!" + (yyval).labelTemp + ") goto "+  sElse + ";\n" +
				(yyvsp[-1]).traducao + (yyvsp[0]).traducao; 
       		 	
			}
#line 2368 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 890 "sintatica.y" /* yacc.c:1646  */
    {
  				string sFimIF = "FIM_IF_" + to_string(ctdIf);        	        
  				string sElse = "ELSE_" + to_string(ctdElse) ;
  				setarContexto(0, "", sElse);
  				(yyval).traducao = "\n\tgoto " + sFimIF + ";\n"+
				"\n\t//ELSE COMEÇA\n\t"+ sElse + ":\n" + (yyvsp[0]).traducao+"\t"+ sFimIF +":\n\t//ELSE TERMINA\n\t"+
				"//IF TERMINA\n\n";
  				ctdElse += 1;
			}
#line 2382 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 901 "sintatica.y" /* yacc.c:1646  */
    {		
				string sFimIF = "FIM_IF_" + to_string(ctdIf);
				string sElseIF = "ELSE_IF_" + to_string(ctdEIf);  				

      			setarContexto(0, "", sFimIF);
				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//ELSEIF COMEÇA\n\t" + sElseIF + ":\n"+(yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = " + (yyvsp[-3]).labelTemp + ";\n" +
				"\tif(!" + (yyval).labelTemp + ") goto " + sFimIF + ";\n" +
				(yyvsp[0]).traducao + 
				"\n\t" + sFimIF + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				ctdEIf += 1;				
			}
#line 2402 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 917 "sintatica.y" /* yacc.c:1646  */
    {		
				string sFimIF = "FIM_IF_" + to_string(ctdIf);
				string sElseIF = "ELSE_IF_" + to_string(ctdEIf);  				

        		setarContexto(0, "", sFimIF);
				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//ELSEIF COMEÇA\n\t" + sElseIF + ":\n"+(yyvsp[-4]).traducao +
				"\t" + (yyval).labelTemp + " = " + (yyvsp[-4]).labelTemp + ";\n" +
				"\tif(!" + (yyval).labelTemp + ") goto " + sFimIF + ";\n" +
				(yyvsp[-2]).traducao + 
				"\n\t" + sFimIF + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				ctdEIf += 1;				
			}
#line 2422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 933 "sintatica.y" /* yacc.c:1646  */
    {
        		string sFimIF = "FIM_IF_" + to_string(ctdIf);
				string sElse = "ELSE_" + to_string(ctdElse) ;
				string sElseIF = "ELSE_IF_" + to_string(ctdEIf);  				

				setarContexto(0, "", sFimIF);

				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//" + sElseIF +" COMEÇA\n\tELSEIF:\n"+ (yyvsp[-4]).traducao +
				"\t" + (yyval).labelTemp + " = " + (yyvsp[-4]).labelTemp + ";\n" +
				"\tif(!" + (yyval).labelTemp + ") goto " + sElse +";\n" +
				(yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			}
#line 2441 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 950 "sintatica.y" /* yacc.c:1646  */
    {	
  				string sWhile = "WHILE_" + to_string(ctdWhile);
  				string sFWhile = "FIM_WHILE_" + to_string(ctdWhile);
				setarContexto(1, sWhile, sFWhile);
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//WHILE COMEÇA\n"+ (yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-3]).labelTemp + ";\n" +
				"\t" + "if("+(yyval).labelTemp+"){\n\t"+ sWhile +":\n"+(yyvsp[0]).traducao+"\t}if("+(yyval).labelTemp+") goto "+ sWhile +";\n\t"+ sFWhile + ":\n\t//WHILE TERMINA\n";
  				ctdWhile += 1;
			}
#line 2457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 964 "sintatica.y" /* yacc.c:1646  */
    {
				string sDWhile = "DO_WHILE_" + to_string(ctdWhile);
  				string sFDWhile = "FIM_DO_WHILE_" + to_string(ctdWhile);
				setarContexto(1, sDWhile, sFDWhile);
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//DO WHILE COMEÇA\n"+ (yyvsp[-2]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-2]).labelTemp + ";\n" +
				"\t" + "\n\t"+ sDWhile +":\n"+(yyvsp[-5]).traducao+"\tif("+(yyval).labelTemp+") goto "+ sDWhile +";\n\t"+ sFDWhile + ":\n\t//DO WHILE TERMINA\n";
  				ctdWhile += 1;
			}
#line 2473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 978 "sintatica.y" /* yacc.c:1646  */
    {
				string sFor = "FOR_" + to_string(ctdFor);
  				string sFFor = "FIM_DO_FOR_" + to_string(ctdFor);
				setarContexto(1, sFor, sFFor);
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//FOR COMEÇA\n"+ (yyvsp[-6]).traducao + (yyvsp[-5]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-5]).labelTemp + ";\n" +
				"\t" + "if("+(yyval).labelTemp+")goto "+ sFFor +"\n\t"+ sFor +":\n"+(yyvsp[0]).traducao + (yyvsp[-3]).traducao +"\tif("+(yyval).labelTemp+") goto "+ sFor +";\n\t"+ sFFor + ":\n\t//FOR TERMINA\n";
  				ctdFor += 1;
			}
#line 2489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 991 "sintatica.y" /* yacc.c:1646  */
    {	
				(yyval).tipo = "int";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t"+ (yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " + 1;\n"
							  +"\t" + (yyvsp[-2]).labelTemp + " = " + (yyval).labelTemp+ ";\n"; 
			}
#line 2500 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1000 "sintatica.y" /* yacc.c:1646  */
    {
				
				(yyval).traducao = "\n\tswitch(" + (yyvsp[-4]).traducao +"){"+ (yyvsp[-1]).traducao+ "}\n";
			}
#line 2509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1007 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			}
#line 2517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1011 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1015 "sintatica.y" /* yacc.c:1646  */
    {
        		(yyval).traducao = (yyvsp[0]).traducao;
      		}
#line 2533 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1021 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t" + (yyvsp[-2]).traducao + "if( "+(yyvsp[-2]).labelTemp+ "==)"+ (yyvsp[0]).traducao ;
			}
#line 2543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1029 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[0]).tipo;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).labelTemp + ";\n";
			}
#line 2553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1036 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1042 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).labelTemp = (yyvsp[-1]).labelTemp;
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1048 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " > " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " > " + labelCasting +
					";\n";
				}
				else{		

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " > " + (yyvsp[0]).labelTemp +
					";\n";
				}

			}
#line 2609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1082 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " < " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " < " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " < " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1115 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " >= " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " >= " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " >= " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1148 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " <= " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " <= " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " <= " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1181 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " != " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " != " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " != " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1214 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " == " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " == " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " == " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1247 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " && " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " && " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " && " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1280 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " || " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " || " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " || " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 2868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1313 "sintatica.y" /* yacc.c:1646  */
    { 
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1319 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).labelTemp = (yyvsp[-1]).labelTemp;
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1325 "sintatica.y" /* yacc.c:1646  */
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
#line 2933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1368 "sintatica.y" /* yacc.c:1646  */
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
#line 2979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1410 "sintatica.y" /* yacc.c:1646  */
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
#line 3025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1452 "sintatica.y" /* yacc.c:1646  */
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
#line 3070 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1493 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "float";
				
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).nomeVariavel + " = (float) " + (yyvsp[0]).nomeVariavel +
				";\n";
			}
#line 3082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1501 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "int";
				
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).nomeVariavel + " = (int) " + (yyvsp[0]).nomeVariavel +
				";\n";
			}
#line 3094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1509 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[0]).tipo;

				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).nomeVariavel + " = -" + (yyvsp[0]).nomeVariavel +
				";\n";			
			}
#line 3106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1517 "sintatica.y" /* yacc.c:1646  */
    { 
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 3114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1523 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 1;
				(yyval).tipo = "int";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 3127 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1532 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 1;
				(yyval).tipo = "float";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 3140 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1541 "sintatica.y" /* yacc.c:1646  */
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
#line 3179 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1576 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = "0";
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyval).valor +
				";\n";
			}
#line 3191 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1584 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = "1";
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyval).valor +
				";\n";
			}
#line 3203 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1592 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 2;
				(yyval).tipo = "char";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 3216 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3220 "y.tab.c" /* yacc.c:1646  */
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
#line 1603 "sintatica.y" /* yacc.c:1906  */


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
