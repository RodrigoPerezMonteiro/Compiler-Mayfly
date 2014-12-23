// $Id: AND.h,v 1.2 2013-05-14 22:08:39 ist173701 Exp $
#ifndef __MF_NODE_EXPRESSION_AND_H__
#define __MF_NODE_EXPRESSION_AND_H__

#include <cdk/nodes/expressions/BinaryExpression.h>
#include <string>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

class AND: public cdk::node::expression::BinaryExpression{
      
      Expression *_right;
      Expression *_left; 
      
      public:
	
        inline AND(int lineno, Expression *left, Expression *right) :
          cdk::node::expression::BinaryExpression(lineno, left, right), _right(right), _left(left){
        }


        const char *name() const {
          return "AND";
        }

        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processAND(this, level);
        }
        
      inline Expression *right(){
      return _right;
      }
      
      inline Expression *left(){
      return _left;
      }

      };

    } // expression
  } // node
} // mayfly

#endif 
