%option c++ yyclass="MFScanner" outfile="MFScanner.cpp"
%option stack noyywrap yylineno 8bit
%{ 
#include <string>
#include <list>
#include <iostream>
#include <cdk/nodes/Node.h>
#include <cdk/nodes/Sequence.h>
#include <cdk/nodes/expressions/Expression.h>
#include "MFScanner.h"
#include "MFParser.tab.h"

#define yyerror LexerError

std::string str;
%}

TAB			[ \t]
ENDLINE			[\n]
SPACES			[ \t\n\r]+


%x X_COMMENT X_STRING X_STRING_AUX

%%
		//{ set_debug(1); }		
">="		return tGE; 
"<="		return tLE; 
"=="    	return tEQ; 
"<>"    	return tNE; 
"while" 	return tDOWHILE; 
"if"    	return tIF; 
"then"		return tTHEN;
"else"  	return tELSE; 
"read"  	return tREAD; 
"end"   	return tEND;
"void"		return tVOID;
"integer" 	return tINT;
"number" 	return tNUMBER;
"string" 	return tSTR;
"public" 	return tPUBLIC;
"const"		return tCONST;
"do"		return tDO;
"for"		return tFOR;
"in" 		return tIN;
"step"		return tSTEP;
"upto"		return tUPTO;
"downto" 	return tDOWNTO;
"continue"	return tCONTINUE;
"break"		return tBREAK;
"return"	return tRETURN;
"++"		return tINC;
"--"		return tDEC;
"!!"		return tPN;

[A-Za-z_][A-Za-z0-9_]*  {
			    yylval.s = new std::string(yytext); 
			    return tIDENTIFIER; 
			} 

0		        { yylval.i = strtol(yytext, nullptr, 10); return tINTEGER; }   		       
		        
[1-9][0-9]*             { 
			  errno = 0;
			  yylval.i = strtol(yytext, nullptr, 10);
			  if (errno == ERANGE)
			  { yyerror("Decimal Overflow"); }
			  return tINTEGER; 
		        }
		        
0[0-7]*                 { 
			  errno = 0;
			  yylval.i = strtol(yytext, nullptr, 8);
			  if (errno == ERANGE)
			  { yyerror("Octal Overflow"); }
			  return tINTEGER; 
		        }

"0x"[0-9A-Fa-f]+ 	{
			  errno = 0;
			  yylval.i = strtol(yytext, nullptr, 16);
			  if (errno == ERANGE)
			  { yyerror("Hexadecimal Overflow"); }
			  return tINTEGER; 
		        }


(([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*)|([0-9]+))([eE][-]?[0-9]+)?		{
									   std::string s = std::string(yytext);
									   yylval.d = strtod(s.c_str(), NULL);
									   return tREAL;
									}


[-=|&~<>+*/%()#@{},;!\[\].]		return *yytext;

\"					{ yy_push_state(X_STRING); str.clear(); }

<X_STRING>\"[ \t\n\r]*\"		;
<X_STRING>\"				{ yylval.s = new std::string(str); yy_pop_state(); return tSTRING; }
<X_STRING>\\				yy_push_state(X_STRING_AUX);
<X_STRING>.				str += yytext;

<X_STRING_AUX>n				{ str += '\n'; yy_pop_state(); }
<X_STRING_AUX>r				{ str += '\r'; yy_pop_state(); }
<X_STRING_AUX>t				{ str += '\t'; yy_pop_state(); }
<X_STRING_AUX>\"			{ str += '\"'; yy_pop_state(); }
<X_STRING_AUX>\\			{ str += '\\'; yy_pop_state(); }
<X_STRING_AUX>[0-9a-fA-F][0-9a-fA-F]?	{ str += strtol(yytext, nullptr, 16); yy_pop_state(); }


">>".*\n 		; //COMENTARIO DE 1 LINHA
"=<" 			yy_push_state(X_COMMENT);

<X_COMMENT>"=>"		yy_pop_state();
<X_COMMENT>"=<"		yy_push_state(X_COMMENT);
<X_COMMENT>.		;
<X_COMMENT>{ENDLINE}	yyerror("Error: newline in comment");

{SPACES}  		;
.   			yyerror("Unknown character");
%%
int MFScanner::yywrap() 
{ return 1; }