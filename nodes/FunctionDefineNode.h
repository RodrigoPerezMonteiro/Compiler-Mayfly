// $Id: FunctionDefineNode.h,v 1.10 2013-05-20 18:48:08 ist173701 Exp $ -*- c++ -*-
#ifndef __MF_FUNCTIONDEFINENODE_H__
#define __MF_FUNCTIONDEFINENODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/semantics/ExpressionType.h>

namespace mayfly {
  namespace node {

    class FunctionDefineNode: public cdk::node::Node {
      
      bool _public = false;
      ExpressionType *_tipo = NULL;
      bool _isVoid = false;
      std::string *_functionName;
      cdk::node::Sequence *_vars;
      cdk::node::expression::Expression *_literal = NULL;
      cdk::node::Sequence *_statements;
      bool _isLiteral = false;
      

    public:
          
      inline FunctionDefineNode(int lineno,
				bool isPublic,
				ExpressionType *tipo,
				std::string *functionName,
				cdk::node::Sequence *vars,
				cdk::node::expression::Expression *literal,
				cdk::node::Sequence *statements
				) :
          cdk::node::Node(lineno), _public(isPublic), _tipo(tipo), _functionName(functionName), _vars(vars), _literal(literal), _statements(statements), _isLiteral(true) {}
          
      inline FunctionDefineNode(int lineno, //SEM LITERAL
				bool isPublic,
				ExpressionType *tipo,
				std::string *functionName,
				cdk::node::Sequence *vars,
				cdk::node::Sequence *statements
				) :
          cdk::node::Node(lineno), _public(isPublic), _tipo(tipo), _functionName(functionName), _vars(vars), _statements(statements) {}
          
      inline FunctionDefineNode(int lineno, //VOID
				bool isPublic,
				bool isVoid,
				std::string *functionName,
				cdk::node::Sequence *vars,
				cdk::node::expression::Expression *literal,
				cdk::node::Sequence *statements
				) :
          cdk::node::Node(lineno), _public(isPublic), _isVoid(isVoid), _functionName(functionName), _vars(vars), _literal(literal), _statements(statements), _isLiteral(true) {}
          
      inline FunctionDefineNode(int lineno, //SEM LITERAL + VOID
				bool isPublic,
				bool isVoid,
				std::string *functionName,
				cdk::node::Sequence *vars,
				cdk::node::Sequence *statements
				) :
          cdk::node::Node(lineno), _public(isPublic), _isVoid(isVoid), _functionName(functionName), _vars(vars), _statements(statements) {}

      const char *name() const {
        return "FunctionDefineNode";
      }
      
      inline std::string *functionName() {
        return _functionName;
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processFunctionDefineNode(this, level);
      }
      
      inline bool isVoid() {
	return _isVoid;
      }
      
      inline bool pblic() {
	return _public;
      }
      
      inline bool isLiteral() {
	return _isLiteral;
      }
      
      inline ExpressionType  *tipo() {
	return _tipo;
      }
      
      inline cdk::node::expression::Expression  *literal() {
	return _literal;
      }
      
      inline cdk::node::Sequence *vars() {
	return _vars;
      }
      
      inline cdk::node::Sequence *statements() {
	return _statements;
      }
      

    };

  } // namespace node
} // namespace mayfly

#endif
