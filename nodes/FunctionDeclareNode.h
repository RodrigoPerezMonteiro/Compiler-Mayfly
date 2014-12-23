// $Id: FunctionDeclareNode.h,v 1.9 2013-05-18 21:32:11 ist173701 Exp $ -*- c++ -*-
#ifndef __MF_FUNCTIONDECLARENODE_H__
#define __MF_FUNCTIONDECLARENODE_H__

#include <cdk/nodes/Node.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing program nodes.
     */
    class FunctionDeclareNode: public cdk::node::Node {

      bool _public = false;
      bool _isVoid = false;
      ExpressionType *_tipo = NULL;
      std::string *_functionName;
      cdk::node::Sequence *_vars;
      cdk::node::expression::Expression *_literal;
      bool _isLiteral = false;
      
 
    public:
          
      inline FunctionDeclareNode(int lineno,
				bool isPublic,
				ExpressionType *tipo,
				std::string *functionName,
				cdk::node::Sequence *vars,
				cdk::node::expression::Expression *literal) :
          cdk::node::Node(lineno), _public(isPublic), _tipo(tipo), _functionName(functionName), _vars(vars), _literal(literal), _isLiteral(true) {}
          
      inline FunctionDeclareNode(int lineno, //SEM LITERAL
				bool isPublic,
				ExpressionType *tipo,
				std::string *functionName,
				cdk::node::Sequence *vars) :
          cdk::node::Node(lineno), _public(isPublic), _tipo(tipo), _functionName(functionName), _vars(vars) {}
          
      inline FunctionDeclareNode(int lineno, //VOID
				bool isPublic,
				bool isVoid,
				std::string *functionName,
				cdk::node::Sequence *vars,
				cdk::node::expression::Expression *literal) :
          cdk::node::Node(lineno), _public(isPublic), _isVoid(isVoid), _functionName(functionName), _vars(vars), _literal(literal), _isLiteral(true) {}
          
      inline FunctionDeclareNode(int lineno, //SEM LITERAL + VOID
				bool isPublic,
				bool isVoid,
				std::string *functionName,
				cdk::node::Sequence *vars) :
          cdk::node::Node(lineno), _public(isPublic), _isVoid(isVoid), _functionName(functionName), _vars(vars) {}

      const char *name() const {
        return "FunctionDeclareNode";
      }
      
      inline std::string *functionName() {
        return _functionName;
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processFunctionDeclareNode(this, level);
      }
      
      inline bool pblic() {
	return _public;
      }
      
      inline bool isLiteral() {
	return _isLiteral;
      }
      
      
      inline bool isVoid() {
	return _isVoid;
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

    };

  } // namespace node
} // namespace mayfly

#endif
