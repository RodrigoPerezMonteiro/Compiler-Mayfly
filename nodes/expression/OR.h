// $Id: OR.h,v 1.3 2013-05-14 22:57:57 ist172976 Exp $
#ifndef __MF_NODE_EXPRESSION_OR_H__
#define __MF_NODE_EXPRESSION_OR_H__

#include <cdk/nodes/expressions/BinaryExpression.h>
#include <string>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      class OR: public cdk::node::expression::BinaryExpression{
	
      Expression *_right;
      Expression *_left; 
      
      public:
	
	inline OR(int lineno, Expression *left, Expression *right) :
          cdk::node::expression::BinaryExpression(lineno, left, right), _right(right), _left(left){
        }


        const char *name() const {
          return "OR";
        }

        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processOR(this, level);
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
 
