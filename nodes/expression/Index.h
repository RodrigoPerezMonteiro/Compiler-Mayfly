
#ifndef __MF_NODE_EXPRESSION_INDEX_H__
#define __MF_NODE_EXPRESSION_INDEX_H__

#include <cdk/nodes/expressions/UnaryExpression.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing syntactic tree leaves for holding lvalues.
       */
      class Index: public cdk::node::expression::Expression{
      
	cdk::node::expression::Expression *_arg;
	cdk::node::expression::Expression *_arg2;
	
	
      public:
          
        inline Index(int lineno, Expression *arg, Expression *arg2) :
          Expression(lineno), _arg(arg), _arg2(arg2) {}
          
         


        const char *name() const {
          return "Index";
        }

        void accept(SemanticProcessor *sp, int level) {
          sp->processIndex(this, level);
        }
	
	const cdk::node::expression::Expression *arg(){
	  return _arg;
	}
	
	const cdk::node::expression::Expression *arg2(){
	  return _arg2;
	}

      };

    } // expression
  } // node
} // mayfly

#endif 
