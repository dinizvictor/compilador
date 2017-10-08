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


#line 237 "y.tab.c" /* yacc.c:339  */

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
    TOKEN_SWITCH = 269,
    TOKEN_CASE = 270,
    TOKEN_BREAK = 271,
    TOKEN_DO = 272,
    TOKEN_FOR = 273,
    TOKEN_WHILE = 274,
    TOKEN_RETURN = 275,
    TOKEN_PRINT = 276,
    TOKEN_ERROR = 277,
    TOKEN_STRUCT = 278,
    TOKEN_NOMEVAR = 279,
    TOKEN_NUM_INT = 280,
    TOKEN_NUM_FLOAT = 281,
    TOKEN_BOOLEAN_FALSE = 282,
    TOKEN_BOOLEAN_TRUE = 283,
    TOKEN_CARACTERE = 284,
    TOKEN_MAIOR = 285,
    TOKEN_MENOR = 286,
    TOKEN_DIF = 287,
    TOKEN_IGUAL = 288,
    TOKEN_MAIORIGUAL = 289,
    TOKEN_MENORIGUAL = 290,
    TOKEN_E = 291,
    TOKEN_OU = 292,
    TOKEN_CONV_FLOAT = 293,
    TOKEN_CONV_INT = 294,
    TOKEN_ATR = 295
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
#define TOKEN_SWITCH 269
#define TOKEN_CASE 270
#define TOKEN_BREAK 271
#define TOKEN_DO 272
#define TOKEN_FOR 273
#define TOKEN_WHILE 274
#define TOKEN_RETURN 275
#define TOKEN_PRINT 276
#define TOKEN_ERROR 277
#define TOKEN_STRUCT 278
#define TOKEN_NOMEVAR 279
#define TOKEN_NUM_INT 280
#define TOKEN_NUM_FLOAT 281
#define TOKEN_BOOLEAN_FALSE 282
#define TOKEN_BOOLEAN_TRUE 283
#define TOKEN_CARACTERE 284
#define TOKEN_MAIOR 285
#define TOKEN_MENOR 286
#define TOKEN_DIF 287
#define TOKEN_IGUAL 288
#define TOKEN_MAIORIGUAL 289
#define TOKEN_MENORIGUAL 290
#define TOKEN_E 291
#define TOKEN_OU 292
#define TOKEN_CONV_FLOAT 293
#define TOKEN_CONV_INT 294
#define TOKEN_ATR 295

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

#line 368 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   198

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  124

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

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
      46,    47,    44,    42,    41,    43,     2,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   232,   232,   239,   245,   251,   256,   261,   265,   269,
     270,   273,   285,   305,   318,   338,   351,   376,   388,   418,
     430,   449,   454,   466,   479,   484,   496,   509,   514,   526,
     539,   544,   550,   556,   590,   623,   656,   689,   722,   755,
     788,   821,   827,   833,   876,   918,   960,  1001,  1009,  1017,
    1025,  1031,  1040,  1049,  1081,  1089,  1097
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_MAIN", "TOKEN_BEGIN", "TOKEN_INT",
  "TOKEN_FLOAT", "TOKEN_DOUBLE", "TOKEN_CHAR", "TOKEN_BOOL", "TOKEN_NULL",
  "TOKEN_VOID", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_SWITCH", "TOKEN_CASE",
  "TOKEN_BREAK", "TOKEN_DO", "TOKEN_FOR", "TOKEN_WHILE", "TOKEN_RETURN",
  "TOKEN_PRINT", "TOKEN_ERROR", "TOKEN_STRUCT", "TOKEN_NOMEVAR",
  "TOKEN_NUM_INT", "TOKEN_NUM_FLOAT", "TOKEN_BOOLEAN_FALSE",
  "TOKEN_BOOLEAN_TRUE", "TOKEN_CARACTERE", "TOKEN_MAIOR", "TOKEN_MENOR",
  "TOKEN_DIF", "TOKEN_IGUAL", "TOKEN_MAIORIGUAL", "TOKEN_MENORIGUAL",
  "TOKEN_E", "TOKEN_OU", "TOKEN_CONV_FLOAT", "TOKEN_CONV_INT", "TOKEN_ATR",
  "','", "'+'", "'-'", "'*'", "'/'", "'('", "')'", "'{'", "'}'", "';'",
  "$accept", "S", "BLOCO", "BLOCO_WHILE", "COMANDOS", "COMANDO", "DCL",
  "MLTVAR_INT", "MLTVAR_FLOAT", "MLTVAR_CHAR", "MLTVAR_BOOL", "WHILE",
  "ERL", "E", "E_BASICA", YY_NULLPTR
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
     295,    44,    43,    45,    42,    47,    40,    41,   123,   125,
      59
};
# endif

#define YYPACT_NINF -54

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-54)))

#define YYTABLE_NINF -51

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -1,     2,     8,   -30,   -54,   -25,   -19,   124,   -54,     7,
      47,    53,    57,    76,    83,    50,   124,    77,   -54,   -28,
     -13,    22,    28,    88,    59,   -54,   -54,   -54,    82,   100,
     -54,    82,   107,   -54,    82,   148,   -54,    88,   155,   -54,
     -54,   -54,   -54,   -54,   -54,   -54,    88,   126,   -54,    82,
      82,    82,    59,   105,    -7,   102,    82,    51,   -54,    39,
     133,    49,   153,    60,   152,    63,   134,    88,    88,    88,
      88,    88,    88,    88,    88,    78,   -54,   -54,    74,    -3,
     -54,    82,    82,    82,    82,   -54,   -54,    82,   -54,   -54,
      82,   -54,   -54,    82,   -54,   -54,    88,   -54,   -54,   -54,
     -54,   -54,   -54,   -54,   -54,   119,   119,   124,   -54,   -54,
      74,    74,   -54,   -54,    51,   133,   153,   152,   131,   -54,
     -54,   -54,   -54,   -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     6,     2,     0,
       0,     0,     0,     0,     0,     0,     6,     0,    10,    21,
      24,    27,    30,     0,     0,     3,     5,     9,     0,     0,
      11,     0,     0,    13,     0,     0,    15,     0,     0,    17,
      53,    51,    52,    54,    55,    56,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    41,     0,    21,    50,    21,
      24,    24,    27,    27,    30,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,    48,    49,     0,
       8,     0,     0,     0,     0,     7,    12,     0,    19,    14,
       0,    22,    16,     0,    25,    18,     0,    28,    32,    33,
      34,    37,    38,    35,    36,    39,    40,     6,    31,    42,
      43,    44,    45,    46,    21,    24,    27,    30,     0,    20,
      23,    26,    29,     4
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -54,   -54,   -54,   -54,   -16,   -54,   -54,   -53,   -40,   -44,
     -39,   -54,   -14,   -17,   -22
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     8,   108,    15,    16,    17,    30,    33,    36,
      39,    18,    66,    79,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      26,    48,    55,     1,    86,     3,    88,    54,     4,    47,
      53,    57,    28,    29,    60,    48,     5,    62,    92,    94,
      89,    91,     6,    64,    48,    95,    97,    31,    32,     7,
      55,    19,    76,    77,    78,    81,    82,    83,    84,    81,
      82,    83,    84,    85,   109,    48,    48,    48,    48,    48,
      48,    48,    48,    99,   100,   101,   102,   103,   104,   105,
     106,   119,    34,    35,   110,   111,   112,   113,    37,    38,
     114,    20,   121,   115,    48,   120,   116,    21,   122,    87,
      29,    22,   117,    40,    41,    42,    43,    44,    45,    90,
      32,   118,    29,    81,    82,    83,    84,    49,    50,    25,
      93,    35,    51,    96,    38,    52,    40,    41,    42,    43,
      44,    45,    40,    41,    42,    43,    44,    45,    83,    84,
      49,    50,    23,    24,    59,    51,   107,    27,    56,     9,
      10,    61,    11,    12,    46,    67,    68,    69,    70,    71,
      72,    73,    74,    13,   -50,   -50,   -50,   -50,    14,    67,
      68,    69,    70,    71,    72,    80,    67,    68,    69,    70,
      71,    72,    73,    74,    67,    68,    69,    70,    71,    72,
      73,    74,    63,    75,    32,    81,    82,    83,    84,    65,
     123,    98,    67,    68,    69,    70,    71,    72,    73,    74,
       0,     0,     0,    38,    35,    81,    82,    83,    84
};

static const yytype_int8 yycheck[] =
{
      16,    23,    24,     4,    57,     3,    59,    24,     0,    23,
      24,    28,    40,    41,    31,    37,    46,    34,    62,    63,
      60,    61,    47,    37,    46,    64,    65,    40,    41,    48,
      52,    24,    49,    50,    51,    42,    43,    44,    45,    42,
      43,    44,    45,    50,    47,    67,    68,    69,    70,    71,
      72,    73,    74,    67,    68,    69,    70,    71,    72,    73,
      74,   114,    40,    41,    81,    82,    83,    84,    40,    41,
      87,    24,   116,    90,    96,   115,    93,    24,   117,    40,
      41,    24,    96,    24,    25,    26,    27,    28,    29,    40,
      41,   107,    41,    42,    43,    44,    45,    38,    39,    49,
      40,    41,    43,    40,    41,    46,    24,    25,    26,    27,
      28,    29,    24,    25,    26,    27,    28,    29,    44,    45,
      38,    39,    46,    40,    24,    43,    48,    50,    46,     5,
       6,    24,     8,     9,    46,    30,    31,    32,    33,    34,
      35,    36,    37,    19,    42,    43,    44,    45,    24,    30,
      31,    32,    33,    34,    35,    50,    30,    31,    32,    33,
      34,    35,    36,    37,    30,    31,    32,    33,    34,    35,
      36,    37,    24,    47,    41,    42,    43,    44,    45,    24,
      49,    47,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    41,    41,    42,    43,    44,    45
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    52,     3,     0,    46,    47,    48,    53,     5,
       6,     8,     9,    19,    24,    55,    56,    57,    62,    24,
      24,    24,    24,    46,    40,    49,    55,    50,    40,    41,
      58,    40,    41,    59,    40,    41,    60,    40,    41,    61,
      24,    25,    26,    27,    28,    29,    46,    63,    65,    38,
      39,    43,    46,    63,    64,    65,    46,    64,    65,    24,
      64,    24,    64,    24,    63,    24,    63,    30,    31,    32,
      33,    34,    35,    36,    37,    47,    64,    64,    64,    64,
      50,    42,    43,    44,    45,    50,    58,    40,    58,    59,
      40,    59,    60,    40,    60,    61,    40,    61,    47,    63,
      63,    63,    63,    63,    63,    63,    63,    48,    54,    47,
      64,    64,    64,    64,    64,    64,    64,    63,    55,    58,
      59,    60,    61,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    54,    55,    55,    56,    56,    56,
      56,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    58,    59,    59,    59,    60,    60,    60,    61,    61,
      61,    62,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    65,    65,    65,    65,    65,    65
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     3,     3,     2,     0,     4,     4,     2,
       1,     3,     5,     3,     5,     3,     5,     3,     5,     3,
       5,     0,     3,     5,     0,     3,     5,     0,     3,     5,
       0,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     3,     3,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1
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
#line 233 "sintatica.y" /* yacc.c:1646  */
    {
				cout << "/*Compilador ITL*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void){\n" <<
				(yyvsp[0]).traducao << "\treturn 0;\n}" << endl; 							
			}
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 240 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = geraLabelFinal();
				(yyval).traducao = (yyval).label + (yyvsp[-1]).traducao;
			}
#line 1556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 246 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 252 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			}
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 256 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 1580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 262 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = verificaErros((yyvsp[-3]), (yyvsp[-1]), 1);
			}
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 266 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = verificaErros((yyvsp[-3]), (yyvsp[-1]), 2);
			}
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 274 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-1]).label].label, 'd')){
					(yyval).tipo = "int";
					(yyval).valor = "null";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;

					mapaDeVariaveis[(yyvsp[-1]).label] = (yyval);
				}
			}
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 286 "sintatica.y" /* yacc.c:1646  */
    {
				
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-3]).label].label, 'd')){
					(yyval).tipo = "int";
					(yyval).valor = (yyvsp[-1]).valor;			

					if((yyvsp[-1]).tipo != (yyval).tipo ){																
						std::cout <<MSG_ERRO_TIPO<< std::endl;
						exit(1);		
					}				

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).valor = (yyvsp[-1]).traducao;
					(yyval).traducao = (yyvsp[-1]).traducao +  "\t" + (yyval).label + " = " + (yyvsp[-1]).label + ";\n" + (yyvsp[0]).traducao; 

					mapaDeVariaveis[(yyvsp[-3]).label] = (yyval);
				}

			}
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 306 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-1]).label].label, 'd')){
					
					(yyval).tipo = "float";
					(yyval).valor = "null";		

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;

					mapaDeVariaveis[(yyvsp[-1]).label] = (yyval);
				}	
			}
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 319 "sintatica.y" /* yacc.c:1646  */
    {

				if(variavelExistente(mapaDeVariaveis[(yyvsp[-3]).label].label, 'd')){

					(yyval).tipo = "float";
					(yyval).valor = (yyvsp[-1]).valor;

					if((yyvsp[-1]).tipo != (yyval).tipo ){																
						std::cout <<MSG_ERRO_TIPO<< std::endl;
						exit(1);		
					}

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-1]).traducao +  "\t" + (yyval).label + " = " + (yyvsp[-1]).label + ";\n" + (yyvsp[0]).traducao; 

					mapaDeVariaveis[(yyvsp[-3]).label] = (yyval);
				}

			}
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 339 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-1]).label].label, 'd')){
					(yyval).tipo = "char";
					(yyval).valor = "null";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;

					mapaDeVariaveis[(yyvsp[-1]).label] = (yyval);
				}

			}
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 352 "sintatica.y" /* yacc.c:1646  */
    {

				if(variavelExistente(mapaDeVariaveis[(yyvsp[-3]).label].label, 'd')){
					if(tipoGeral == 2){
						(yyval).tipo = "char";
						(yyval).valor = (yyvsp[-1]).valor;

						if((yyvsp[-1]).tipo != (yyval).tipo ){																
							std::cout <<MSG_ERRO_TIPO<< std::endl;
							exit(1);		
						}
						
						(yyval).label = geraVarTemp((yyval).tipo);
						(yyval).traducao = (yyvsp[-1]).traducao +  "\t" + (yyval).label + " = " + (yyvsp[-1]).label + ";\n" + (yyvsp[0]).traducao; 

						mapaDeVariaveis[(yyvsp[-3]).label] = (yyval);
					}else{
						std::cout <<MSG_ERRO_TIPO<< std::endl;
						exit(1);
					}

				}

			}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 377 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-1]).label].label, 'd')){
					(yyval).tipo = "bool";
					(yyval).valor = "null";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;

					mapaDeVariaveis[(yyvsp[-1]).label] = (yyval);
				}
			}
#line 1739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 389 "sintatica.y" /* yacc.c:1646  */
    {

				if(variavelExistente(mapaDeVariaveis[(yyvsp[-3]).label].label, 'd')){
					if ((yyvsp[-1]).valor == "0" || (yyvsp[-1]).valor == "1"){
						(yyval).tipo = "bool";
						(yyval).valor = (yyvsp[-1]).valor;				

						
						if((yyvsp[-1]).tipo != (yyval).tipo ){																
							std::cout <<MSG_ERRO_TIPO<< std::endl;
							exit(1);		
						}

						(yyval).label = geraVarTemp((yyval).tipo);
						(yyval).traducao = (yyvsp[-1]).traducao +  "\t" + (yyval).label + " = " + (yyvsp[-1]).label + ";\n" + (yyvsp[0]).traducao; 

						mapaDeVariaveis[(yyvsp[-3]).label] = (yyval);	
					}
					else {
						std::cout << MSG_ERRO_TIPO<< std::endl;
						std::cout <<(yyvsp[-1]).valor<< std::endl;			
						exit(1);
					}
					
				}

			}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 419 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-1]).label].label, 'd')){
					(yyval).tipo = "int";
					(yyval).valor = "null";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = "";
					
					mapaDeVariaveis[(yyvsp[-1]).label] = (yyval);
				}
			}
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 431 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-3]).label].label, 'd')){
					(yyval).tipo = "int";
					(yyval).valor = (yyvsp[-1]).valor;

					if((yyvsp[-1]).tipo != (yyval).tipo ){																
						std::cout << MSG_ERRO_TIPO<< std::endl;
						exit(1);		
					}				
								

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao + (yyvsp[-1]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-1]).label + ";\n" ;

					mapaDeVariaveis[(yyvsp[-3]).label] = (yyval);
				}
			}
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 449 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 455 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-1]).label].label, 'd')){
					(yyval).tipo = "float";
					(yyval).valor = "null";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = "";

					mapaDeVariaveis[(yyvsp[-1]).label] = (yyval);
				}
			}
#line 1833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 467 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-3]).label].label, 'd')){
					(yyval).tipo = "float";
					(yyval).valor = (yyvsp[-1]).valor;

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao + (yyvsp[-1]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-1]).label + ";\n" ;
					
					mapaDeVariaveis[(yyvsp[-3]).label] = (yyval);
				}
			}
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 479 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 1857 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 485 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-1]).label].label, 'd')){
					(yyval).tipo = "char";
					(yyval).valor = "null";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = "";

					mapaDeVariaveis[(yyvsp[-1]).label] = (yyval);
				}
			}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 497 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-3]).label].label, 'd')){
					(yyval).tipo = "char";
					(yyval).valor = (yyvsp[-1]).valor;
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao + (yyvsp[-1]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-1]).label + ";\n" ;
					
					mapaDeVariaveis[(yyvsp[-3]).label] = (yyval);
				}
			}
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 509 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 515 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-1]).label].label, 'd')){
					(yyval).tipo = "bool";
					(yyval).valor = "null";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = "";

					mapaDeVariaveis[(yyvsp[-1]).label] = (yyval);
				}
			}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 527 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente(mapaDeVariaveis[(yyvsp[-3]).label].label, 'd')){
					(yyval).tipo = "bool";
					(yyval).valor = (yyvsp[-1]).valor;

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao + (yyvsp[-1]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-1]).label + ";\n" ;
					
					mapaDeVariaveis[(yyvsp[-3]).label] = (yyval);
				}
			}
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 539 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 545 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "\n\tWHILE:\n\tif("+(yyvsp[-2]).label+"){\n"+(yyvsp[0]).traducao+"\tif("+(yyvsp[-2]).label+") goto WHILE;\n\t}\n";
			}
#line 1945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 551 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).label = (yyvsp[-1]).label;
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 557 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " > " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " > " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " > " + (yyvsp[0]).label +
					";\n";
				}

			}
#line 1993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 591 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " < " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " < " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " < " + (yyvsp[0]).label +
					";\n";
				}
			}
#line 2030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 624 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " >= " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " >= " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " >= " + (yyvsp[0]).label +
					";\n";
				}
			}
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 657 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " <= " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " <= " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " <= " + (yyvsp[0]).label +
					";\n";
				}
			}
#line 2104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 690 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " != " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " != " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " != " + (yyvsp[0]).label +
					";\n";
				}
			}
#line 2141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 723 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " == " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " == " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " == " + (yyvsp[0]).label +
					";\n";
				}
			}
#line 2178 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 756 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " && " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " && " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " && " + (yyvsp[0]).label +
					";\n";
				}
			}
#line 2215 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 789 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){					
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " || " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraVarTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " || " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " || " + (yyvsp[0]).label +
					";\n";
				}
			}
#line 2252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 822 "sintatica.y" /* yacc.c:1646  */
    { 
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2260 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 828 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).label = (yyvsp[-1]).label;
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2270 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 834 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraVarTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " + " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraVarTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " + " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " + " + (yyvsp[0]).label +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " + " + (yyvsp[0]).label +
					";\n";
				}

				
			}
#line 2317 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 877 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraVarTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " - " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraVarTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " - " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " - " + (yyvsp[0]).label +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " - " + (yyvsp[0]).label +
					";\n";
				}
				
			}
#line 2363 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 919 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraVarTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " * " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraVarTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " * " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " * " + (yyvsp[0]).label +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " * " + (yyvsp[0]).label +
					";\n";
				}
				
			}
#line 2409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 961 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraVarTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).label + ";\n";

					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + labelCasting + " / " + (yyvsp[0]).label +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraVarTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).label + ";\n";
					
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " / " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " / " + (yyvsp[0]).label +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).label = geraVarTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).label + " = " + (yyvsp[-2]).label + " / " + (yyvsp[0]).label +
					";\n";
				}
			}
#line 2454 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1002 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "float";
				
				(yyval).label = geraVarTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " = (float) " + (yyvsp[0]).label +
				";\n";
			}
#line 2466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1010 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "int";
				
				(yyval).label = geraVarTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " = (int) " + (yyvsp[0]).label +
				";\n";
			}
#line 2478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1018 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[0]).tipo;

				(yyval).label = geraVarTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " = -" + (yyvsp[0]).label +
				";\n";			
			}
#line 2490 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1026 "sintatica.y" /* yacc.c:1646  */
    { 
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1032 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 1;
				(yyval).tipo = "int";
				(yyval).label = geraVarTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 2511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1041 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 1;
				(yyval).tipo = "float";
				(yyval).label = geraVarTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 2524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1050 "sintatica.y" /* yacc.c:1646  */
    {

                if(mapaDeVariaveis.find((yyvsp[0]).label) != mapaDeVariaveis.end()){
					if(mapaDeVariaveis[(yyvsp[0]).label].tipo == "float" || mapaDeVariaveis[(yyvsp[0]).label].tipo == "int"){

						if(mapaDeVariaveis[(yyvsp[0]).label].valor != "null"){						

							(yyval).label = mapaDeVariaveis[(yyvsp[0]).label].label;
							(yyval).valor = mapaDeVariaveis[(yyvsp[0]).label].valor;
							(yyval).tipo = mapaDeVariaveis[(yyvsp[0]).label].tipo;
							(yyval).traducao = ""; 

						}
						else{
							std::cout <<mapaDeVariaveis[(yyvsp[0]).label].label<<MSG_ERRO_INICIALIZADA << std::endl;
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
#line 2560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1082 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				(yyval).label = geraVarTemp((yyval).tipo);
				(yyval).valor = "0";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyval).valor +
				";\n";
			}
#line 2572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1090 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				(yyval).label = geraVarTemp((yyval).tipo);
				(yyval).valor = "1";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyval).valor +
				";\n";
			}
#line 2584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1098 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 2;
				(yyval).tipo = "char";
				(yyval).label = geraVarTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 2597 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2601 "y.tab.c" /* yacc.c:1646  */
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
#line 1109 "sintatica.y" /* yacc.c:1906  */


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
