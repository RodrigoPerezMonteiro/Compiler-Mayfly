#ifndef __MF_NODE_EXPRESSION_NOT_H__
#define __MF_NODE_EXPRESSION_NOT_H__

#include <cdk/nodes/expressions/UnaryExpression.h>
#include "SemanticProcessor.h"

namespace mayfly {
namespace node {
namespace expression {

class NOT: public cdk::node::expression::UnaryExpression {
    
    Expression * _argument;
  
      public:
  
      inline NOT(int lineno, Expression *arg) :
      UnaryExpression(lineno, arg), _argument(arg) {
      }

      const char *name() const {
      return "NOT";
      }

      virtual void accept(SemanticProcessor *sp, int level) {
      sp->processNOT(this, level);
      }
      
      inline Expression *argument(){
      return _argument;
      }

      };

    } // expression
  } // node
} // mayfly

#endif 
 
