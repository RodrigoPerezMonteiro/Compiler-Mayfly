%{
#include <cstdlib>
#include <iostream>
#include <string>
#include "YYParser.h"
#include "nodes/all.h"

#define LINE scanner()->lineno()
#define yyparse mayfly::YYParser::yyparse

%}

%union 
{
  int                               i;
  double			    d;
  std::string                       *s;
  cdk::node::Node                   *node;
  cdk::node::Sequence               *sequence;
  cdk::node::expression::Expression *expression;
  ExpressionType		    *expressiontype;
  mayfly::node::expression::LeftValue *leftvalue;
};

%token <i> tINTEGER tNUMBER tZERO tINT tSTR
%token <d> tREAL
%token <s> tIDENTIFIER tSTRING
%token tDOWHILE tREAD tEND tTHEN tDO tFOR tIN tVOID tCONST tPUBLIC tSTEP tUPTO tDOWNTO tCONTINUE tBREAK tRETURN
%token tIF tPN

%nonassoc tIFX 
%nonassoc tELSE

%nonassoc tAUX

%right '='
%left '|'
%left '&'
%nonassoc '~'
%left tEQ tNE
%left tGE tLE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc tUMINUS tINC tDEC

%type <node> function instruction iterInstruction condInstruction var decl declvars
%type <sequence> ficheiro vars body block lista optionalargs instrList optionalfunctionargs functionargs
%type <expression> expr literal unaria
%type <expressiontype> type
%type <s> listaStrings
%type <leftvalue> leftvalue

%%
ficheiro : lista				{ _compiler->ast($1); }
	 ;
	   
lista : decl 					{ $$ = new cdk::node::Sequence(LINE, $1); }
      |	lista decl				{ $$ = new cdk::node::Sequence(LINE, $2, $1); }
      ;
      
decl : declvars					{ $$ = $1; }
     | function					{ $$ = $1; }
     ;
     
declvars : vars ';'				{ $$ = $1; }
	 ;
     
vars : var 					{ $$ = new cdk::node::Sequence(LINE, $1); }
     | vars ',' var 				{ $$ = new cdk::node::Sequence(LINE, $3, $1); }
     ;
     
var : type tIDENTIFIER				{ $$ = new mayfly::node::VarDeclareNode (LINE, false, false, $1, $2); }
    | type tIDENTIFIER '=' expr			{ $$ = new mayfly::node::VarDefineNode(LINE, false, false, $1, $2, $4); }
    | tPUBLIC type tIDENTIFIER			{ $$ = new mayfly::node::VarDeclareNode(LINE, true, false, $2, $3); }
    | tPUBLIC type tIDENTIFIER '=' expr		{ $$ = new mayfly::node::VarDefineNode(LINE, true, false, $2, $3, $5); }
    | tCONST type tIDENTIFIER			{ $$ = new mayfly::node::VarDeclareNode(LINE, false, true, $2, $3); }
    | tCONST type tIDENTIFIER '=' expr		{ $$ = new mayfly::node::VarDefineNode(LINE, false, true, $2, $3, $5); }
    | tPUBLIC tCONST type tIDENTIFIER		{ $$ = new mayfly::node::VarDeclareNode(LINE, true, true, $3, $4); }
    | tPUBLIC tCONST type tIDENTIFIER '=' expr	{ $$ = new mayfly::node::VarDefineNode(LINE, true, true, $3, $4, $6); }
    ;
    
optionalargs	: vars 				{ $$ = $1; }
		|      				{ $$ =  new cdk::node::Sequence(LINE,  new cdk::node::Nil(LINE)); }
		;
		

optionalfunctionargs	: functionargs		{ $$ = $1; }
			| 			{ $$ = new cdk::node::Sequence(LINE, new cdk::node::Nil(LINE)); }
			;
			
functionargs	: expr				{ $$ = new cdk::node::Sequence(LINE, $1); }
		| functionargs ',' expr		{ $$ = new cdk::node::Sequence(LINE, $3, $1); }
		;
	 
body :  '{' block '}'				{ $$ = $2; }
     |  '{' 	  '}'				{ $$ = new cdk::node::Sequence(LINE, new cdk::node::Nil(LINE)); }
     ;

block : block instruction			{ $$ = new cdk::node::Sequence(LINE, $2, $1); }
      | instruction 				{ $$ = new cdk::node::Sequence(LINE, $1); }
      ;   

		
function : tPUBLIC type tIDENTIFIER '(' optionalargs ')' literal body		{ $$ = new mayfly::node::FunctionDefineNode(LINE, true, $2, $3, $5, $7, $8); }
	 | tPUBLIC type tIDENTIFIER '(' optionalargs ')' literal		{ $$ = new mayfly::node::FunctionDeclareNode(LINE, true, $2, $3, $5, $7); }
	 | tPUBLIC type tIDENTIFIER '(' optionalargs ')' body			{ $$ = new mayfly::node::FunctionDefineNode(LINE, true, $2, $3, $5, $7); }
	 | tPUBLIC type tIDENTIFIER '(' optionalargs ')'			{ $$ = new mayfly::node::FunctionDeclareNode(LINE, true, $2, $3, $5); }
	 | tPUBLIC tVOID tIDENTIFIER '(' optionalargs ')' body 			{ $$ = new mayfly::node::FunctionDefineNode(LINE, true, true, $3, $5, $7); }
	 | tPUBLIC tVOID tIDENTIFIER '(' optionalargs ')'			{ $$ = new mayfly::node::FunctionDeclareNode(LINE, true, true, $3, $5); }
	 | type tIDENTIFIER '(' optionalargs ')' literal body 			{ $$ = new mayfly::node::FunctionDefineNode(LINE, false, $1, $2, $4, $6, $7); }
	 | type tIDENTIFIER '(' optionalargs ')' literal			{ $$ = new mayfly::node::FunctionDeclareNode(LINE, false, $1, $2, $4, $6); }
	 | type tIDENTIFIER '(' optionalargs ')' body	 			{ $$ = new mayfly::node::FunctionDefineNode(LINE, false, $1, $2, $4, $6); }
	 | type tIDENTIFIER '(' optionalargs ')'				{ $$ = new mayfly::node::FunctionDeclareNode(LINE, false, $1, $2, $4); }
	 | tVOID tIDENTIFIER '(' optionalargs ')' body 				{ $$ = new mayfly::node::FunctionDefineNode(LINE, false, true, $2, $4, $6); }
	 | tVOID tIDENTIFIER '(' optionalargs ')'				{ $$ = new mayfly::node::FunctionDeclareNode(LINE, false, true, $2, $4); }
	;

leftvalue : tIDENTIFIER				{ $$ = new mayfly::node::expression::LeftValue(LINE, $1); }
	  | '*' expr				{ $$ = new mayfly::node::expression::LeftValueAsterisco(LINE, $2); }
	  ;
	  
listaStrings : tSTRING 				{ $$ = $1; }
	     | listaStrings tSTRING		{ *$$ = *$1 + *$2; }
	     ;

	    
instrList : instrList instruction		{ $$ = new cdk::node::Sequence(LINE, $2, $1); }
	  | instruction 			{ $$ = new cdk::node::Sequence(LINE, $1); }
	  ; 	     
	     
instruction : expr tPN 				{ $$ = new mayfly::node::PrintNode(LINE, $1, true); }
	    | expr '!'				{ $$ = new mayfly::node::PrintNode(LINE, $1, false); }
	    | expr ';'				{ $$ = $1; }
	    | tBREAK ';'			{ $$ = new mayfly::node::BreakNode(LINE); }
	    | tBREAK tINTEGER ';'		{ $$ = new mayfly::node::BreakNode(LINE, $2); }
	    | tBREAK tIDENTIFIER ';'		{ $$ = new mayfly::node::BreakNode(LINE, new cdk::node::expression::Identifier(LINE, $2)); }
	    | tCONTINUE ';'			{ $$ = new mayfly::node::ContinueNode(LINE); }
	    | tCONTINUE tINTEGER ';'		{ $$ = new mayfly::node::ContinueNode(LINE, $2); }
	    | tRETURN				{ $$ = new mayfly::node::ReturnNode(LINE); }
	    | condInstruction			{ $$ = $1; }
	    | iterInstruction			{ $$ = $1; }
	    | '{' instrList '}'			{ $$ = $2; }
	    | declvars				{ $$ = $1; }
	    ;
      
condInstruction : tIF expr tTHEN instruction %prec tIFX						{ $$ = new mayfly::node::IfNode(LINE, $2, $4); }
		| tIF expr tTHEN instruction tELSE instruction					{ $$ = new mayfly::node::IfElseNode(LINE, $2, $4, $6); }
	        ;
      
iterInstruction : tFOR leftvalue tIN expr tUPTO expr tDO instruction				{ $$ = new mayfly::node::ForNodeInc(LINE, $2, $4, $6, $8); }
		| tFOR leftvalue tIN expr tDOWNTO expr tDO instruction				{ $$ = new mayfly::node::ForNodeDec(LINE, $2, $4, $6, $8); }
		| tFOR leftvalue tIN expr tUPTO  expr tSTEP expr tDO instruction		{ $$ = new mayfly::node::ForNodeInc(LINE, $2, $4, $6, $8, $10); }
		| tFOR leftvalue tIN expr tDOWNTO expr tSTEP expr tDO instruction		{ $$ = new mayfly::node::ForNodeDec(LINE, $2, $4, $6, $8, $10); }
		| tDO instruction tDOWHILE expr	';'						{ $$ = new mayfly::node::DoWhileNode(LINE,$2, $4); }
		;
		
literal : '=' tINTEGER	     			{ $$ = new cdk::node::expression::Integer(LINE, $2); }
	| '=' tREAL	     			{ $$ = new cdk::node::expression::Double(LINE, $2); }
	| '=' listaStrings	     		{ $$ = new cdk::node::expression::String(LINE, $2); }
	;
	
type : tINT 	     				{ $$ = new ExpressionType(4, ExpressionType::TYPE_INT); }
     | tNUMBER		     			{ $$ = new ExpressionType(8, ExpressionType::TYPE_DOUBLE); }
     | tSTR		     			{ $$ = new ExpressionType(4, ExpressionType::TYPE_STRING); }
     | type '*'					{ $$ = new ExpressionType(4, ExpressionType::TYPE_POINTER); }
     ;

expr : tINTEGER                	 		{ $$ = new cdk::node::expression::Integer(LINE, $1); }
     | tREAL					{ $$ = new cdk::node::expression::Double(LINE, $1); }
     | tIDENTIFIER '(' optionalfunctionargs ')'	{ $$ = new mayfly::node::expression::FunctionCallNode(LINE, $1, $3); }
     | listaStrings				{ $$ = new cdk::node::expression::String(LINE, $1); }
     | '-' expr %prec tUMINUS    		{ $$ = new cdk::node::expression::NEG(LINE, $2); }
     | '+' expr			  		{ $$ = $2; }
     | expr '+' expr	         		{ $$ = new cdk::node::expression::ADD(LINE, $1, $3); }
     | expr '-' expr	         		{ $$ = new cdk::node::expression::SUB(LINE, $1, $3); }
     | expr '*' expr 		  		{ $$ = new cdk::node::expression::MUL(LINE, $1, $3); }
     | expr '/' expr	         		{ $$ = new cdk::node::expression::DIV(LINE, $1, $3); }
     | expr '%' expr	         		{ $$ = new cdk::node::expression::MOD(LINE, $1, $3); }
     | expr '<' expr	         		{ $$ = new cdk::node::expression::LT(LINE, $1, $3); }
     | expr '>' expr	         		{ $$ = new cdk::node::expression::GT(LINE, $1, $3); }
     | expr '|' expr				{ $$ = new mayfly::node::expression::OR(LINE, $1, $3); }
     | expr '&' expr	 			{ $$ = new mayfly::node::expression::AND(LINE, $1, $3); }
     | expr tGE expr	         		{ $$ = new cdk::node::expression::GE(LINE, $1, $3); }
     | expr tLE expr             		{ $$ = new cdk::node::expression::LE(LINE, $1, $3); }
     | expr tNE expr	         		{ $$ = new cdk::node::expression::NE(LINE, $1, $3); }
     | expr tEQ expr	         		{ $$ = new cdk::node::expression::EQ(LINE, $1, $3); }
     | '&' expr					{ $$ = new mayfly::node::expression::ReferenceNode(LINE, $2); }
     | '@' 					{ $$ = new mayfly::node::expression::ReadNode(LINE); }
     | '(' expr ')'              		{ $$ = $2; }
     | unaria              			{ $$ = $1; }
     | leftvalue '=' expr 			{ $$ = new mayfly::node::expression::AssignmentNode(LINE, $1, $3); }
     | leftvalue %prec tAUX			{ $$ = $1; }
     | tIDENTIFIER '[' expr ']'  	{ $$ = new mayfly::node::expression::Index(LINE, new cdk::node::expression::Identifier(LINE, $1), $3); }
     | '(' expr ')' '[' expr ']'  	{ $$ = new mayfly::node::expression::Index(LINE, $2, $5); }
     ;
     
unaria	: expr tINC				{ $$ = new mayfly::node::expression::INC(LINE, $1); }
	| expr tDEC				{ $$ = new mayfly::node::expression::DEC(LINE, $1); }
	| tINC expr				{ $$ = new mayfly::node::expression::INC(LINE, $2); }
	| tDEC expr				{ $$ = new mayfly::node::expression::DEC(LINE, $2); }
	| '~' expr				{ $$ = new mayfly::node::expression::NOT(LINE, $2); }
	| '#' expr %prec tAUX			{ $$ = new mayfly::node::expression::MemAloc(LINE, $2); }
	;
%%
//FINAL