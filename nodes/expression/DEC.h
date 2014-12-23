#ifndef __MF_NODE_EXPRESSION_DEC_H__
#define __MF_NODE_EXPRESSION_DEC_H__

#include <cdk/nodes/expressions/UnaryExpression.h>
#include "SemanticProcessor.h"

namespace mayfly {
namespace node {
namespace expression {

class DEC: public cdk::node::expression::UnaryExpression {
  
   Expression *_argument;
   
   public:
  
      inline DEC(int lineno, Expression *arg) :
      UnaryExpression(lineno, arg), _argument(arg) {
      }

      const char *name() const {
      return "DEC";
      }

      virtual void accept(SemanticProcessor *sp, int level) {
      sp->processDEC(this, level);
      }
      
      inline Expression *argument(){
      return _argument;
      }

      };

    } // expression
  } // node
} // mayfly

#endif 
