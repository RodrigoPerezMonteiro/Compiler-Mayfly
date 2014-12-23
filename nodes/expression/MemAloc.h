
#ifndef __MF_NODE_EXPRESSION_MEMALOC_H__
#define __MF_NODE_EXPRESSION_MEMALOC_H__

#include <cdk/nodes/expressions/UnaryExpression.h>
#include <cdk/nodes/expressions/Expression.h>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing syntactic tree leaves for holding lvalues.
       */
      class MemAloc: public cdk::node::expression::UnaryExpression{
      
	cdk::node::expression::Expression *_arg;
	
      public:
	
        inline MemAloc(int lineno, Expression *arg) :
          UnaryExpression(lineno, arg) {
	    
	    _arg = arg;
	    
        }


        const char *name() const {
          return "MemAloc";
        }
        
        inline cdk::node::expression::Expression *argument(){
	 return _arg; 
	}

        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processMemAloc(this, level);
        }

      };

    } // expression
  } // node
} // mayfly

#endif 
