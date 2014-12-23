
#ifndef __MF_NODE_EXPRESSION_INVOCATION_H__
#define __MF_NODE_EXPRESSION_INVOCATION__

#include <cdk/nodes/expressions/Identifier.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing syntactic tree leaves for holding lvalues.
       */
      class Invocation: public cdk::node::expression::Expression{
      
	cdk::node::expression::Identifier *_id;
	
      public:
	
        inline Invocation(int lineno, cdk::node::expression::Identifier *id) :
          Expression(lineno), _id(id) {}


        const char *name() const {
          return "Invocation";
        }
	
	
	void accept(SemanticProcessor *sp, int level) {
          sp->processInvocation(this, level);
        }
        
        const cdk::node::expression::Identifier *id(){
	  return _id; 
	}

      };

    } // expression
  } // node
} // mayfly

#endif 
