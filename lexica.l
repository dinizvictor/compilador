%{
	#include <string>
%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]
CARACTERES [A-Za-z]
CARACTER "'"({CARACTERES}|{DIGITO}+)"'"

DELIMITADOR {ESPACO}+
NUM {DIGITO}+
REAL {NUM}+("."{NUM}+)?
NOMEVAR {LETRA}({LETRA}|{NUM})*
BOOL [true]|[false]

%%

"\n"				{}
{DELIMITADOR}		{}
"principale"		{return TOKEN_MAIN;}
"iniziare"			{return TOKEN_BEGIN;}

"tutto"				{return TOKEN_INT;}
"reale"				{return TOKEN_FLOAT;}
"doppio"			{return TOKEN_DOUBLE;}
"carat"				{return TOKEN_CHAR;}
"boole"             {return TOKEN_BOOL;}

"nullo" 			{return TOKEN_NULL;}
"vuoto" 			{return TOKEN_VOID;}

"strut"				{return TOKEN_STRUCT;}

"se"				{return TOKEN_IF;}
"altri"				{return TOKEN_ELSE;}
"scelta"			{return TOKEN_SWITCH;}
"caso"				{return TOKEN_CASE;}

"rompere" 			{return TOKEN_BREAK;}
"fare" 				{return TOKEN_DO;}
"per" 				{return TOKEN_FOR;}

"ritorno"			{return TOKEN_RETURN; }
"stampare"			{return TOKEN_PRINT; }

">"					{return TOKEN_MAIOR; }	
"<"					{return TOKEN_MENOR; }	
">="				{return TOKEN_MAIORIGUAL; }	
"<="				{return TOKEN_MENORIGUAL; }	
"=="				{return TOKEN_IGUAL; }	
"!!"				{return TOKEN_DIF; }	


"="					{return TOKEN_ATR; }



"&&"				{return TOKEN_E; }
"||"				{return TOKEN_OU; }

"(reale)"           {return TOKEN_CONV_FLOAT; }
"(tutto)"			{return TOKEN_CONV_INT; }

"false"				{yylval.traducao = yytext; return TOKEN_BOOLEAN_FALSE; }
"true"				{yylval.traducao = yytext; return TOKEN_BOOLEAN_TRUE; }


[(){}[\];,]			{ return *yytext; }	
[+\-*/]				{ return *yytext; }
{NUM}			    { yylval.traducao = yytext; return TOKEN_NUM_INT; }
{REAL}				{ yylval.traducao = yytext; return TOKEN_NUM_FLOAT; }
{CARACTER}			{ yylval.traducao = yytext; return TOKEN_CARACTERE; }
{NOMEVAR}			{ yylval.label = yytext; return TOKEN_NOMEVAR; }
.					{ *yytext; }

%%