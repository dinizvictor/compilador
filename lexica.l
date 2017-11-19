%{
	#include <string>
%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]
CARACTERES [A-Za-z]
CARACTER "'"({CARACTERES}|{DIGITO}+)"'"
STRING  "'"({CARACTERES}|{ESPACO}|{DIGITO}+)*"'"

DELIMITADOR {ESPACO}+
NUM {DIGITO}+
REAL {NUM}+("."{NUM}+)?
NOMEVAR {LETRA}({LETRA}|{NUM})*
BOOL [true]|[false]
LINECOMENT "/"([^\"\n]|\\\")*
COMENT ("//"((([^\"\n]|\\\")|\n)*)"|")


%%

"\n"				{contaLinha();}
{DELIMITADOR}		{}
"principale"		{return TOKEN_MAIN;}
"iniziare"			{return TOKEN_BEGIN;}

"tutto"				{return TOKEN_INT;}
"reale"				{return TOKEN_FLOAT;}
"doppio"			{return TOKEN_DOUBLE;}
"carat"				{return TOKEN_CHAR;}
"boole"             {return TOKEN_BOOL;}
"corda"				{return TOKEN_STR;}

"nullo" 			{return TOKEN_NULL;}
"vuoto" 			{return TOKEN_VOID;}

"strut"				{return TOKEN_STRUCT;}

"se"				{return TOKEN_IF;}
"altri"				{return TOKEN_ELSE;}
"altrise"			{return TOKEN_ELSEIF;}
"scelta"			{return TOKEN_SWITCH;}
"caso"				{return TOKEN_CASE;}
"predefinito"		{return TOKEN_DEFAULT;}

"rompere" 			{return TOKEN_BREAK;}
"continuare"		{return TOKEN_CONTINUE;}

"fare" 				{return TOKEN_DO;}
"per" 				{return TOKEN_FOR;}
"mentre"			{return TOKEN_WHILE;}

"ritorno"			{return TOKEN_RETURN; }
"stampare"			{return TOKEN_PRINT; }
"leggere"			{return TOKEN_SCANF; }

">"					{return TOKEN_MAIOR; }	
"<"					{return TOKEN_MENOR; }	
">="				{return TOKEN_MAIORIGUAL; }	
"<="				{return TOKEN_MENORIGUAL; }	
"=="				{return TOKEN_IGUAL; }	
"!!"				{return TOKEN_DIF; }	
"->"				{return TOKEN_IMP; }	

"="					{return TOKEN_ATR; }

"&&"				{return TOKEN_E; }
"||"				{return TOKEN_OU; }

"(reale)"           {return TOKEN_CONV_FLOAT; }
"(tutto)"			{return TOKEN_CONV_INT; }

"false"				{yylval.traducao = yytext; return TOKEN_BOOLEAN_FALSE; }
"true"				{yylval.traducao = yytext; return TOKEN_BOOLEAN_TRUE; }

"</"				{return TOKEN_COM_INT;}
"\\<"				{return TOKEN_COM_END;}

{COMENT}			{ yylval.traducao = yytext; return TOKEN_COMENT; }
{LINECOMENT}		{ yylval.traducao = yytext; return TOKEN_LINECOMENT; }
[()[\];:,{}]		{ return *yytext; }	
[+\-*/]				{ return *yytext; }
{NUM}			    { yylval.traducao = yytext; return TOKEN_NUM_INT; }
{REAL}				{ yylval.traducao = yytext; return TOKEN_NUM_FLOAT; }
{CARACTER}			{ yylval.traducao = yytext; return TOKEN_CARACTERE; }
{STRING}			{ yylval.traducao = yytext; return TOKEN_STRING; }
{NOMEVAR}			{ yylval.nomeVariavel = yytext; return TOKEN_NOMEVAR; }
.					{ return *yytext; }


%%