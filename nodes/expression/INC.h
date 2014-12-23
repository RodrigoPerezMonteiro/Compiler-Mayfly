#ifndef __MF_NODE_EXPRESSION_INC_H__
#define __MF_NODE_EXPRESSION_INC_H__

#include <cdk/nodes/expressions/UnaryExpression.h>
#include "SemanticProcessor.h"

namespace mayfly {
namespace node {
namespace expression {

class INC: public cdk::node::expression::UnaryExpression {
    Expression *_argument;    
    public:
  
      inline INC(int lineno, Expression *arg) :
      UnaryExpression(lineno, arg), _argument(arg) {
      }

      const char *name() const {
      return "INC";
      }

      virtual void accept(SemanticProcessor *sp, int level) {
      sp->processINC(this, level);
      }
      
      inline Expression *argument(){
      return _argument;
      }

      };

    } // expression
  } // node
} // mayfly

#endif 
