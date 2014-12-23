 // $Id: LeftValueAsterisco.h,v 1.2 2013-05-20 23:01:18 ist173701 Exp $
#ifndef __MF_NODE_EXPRESSION_LEFTVALUEASTERISCO_H__
#define __MF_NODE_EXPRESSION_LEFTVALUEASTERISCO_H__

#include <cdk/nodes/expressions/Simple.h>
#include <cdk/nodes/expressions/Expression.h>
#include <string>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing syntactic tree leaves for holding lvalues.
       */
      class LeftValueAsterisco: public mayfly::node::expression::LeftValue {
      public:
	
	cdk::node::expression::Expression *_s;

        inline LeftValueAsterisco(int lineno, cdk::node::expression::Expression *s) :
          mayfly::node::expression::LeftValue(lineno), _s(s)
          {}
        

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "LeftValueAsterisco";
        }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processLeftValueAsterisco(this, level);
        }
        
        cdk::node::expression::Expression *value(){
	  return _s;
	}

      };

    } // expression
  } // node
} // mayfly
#endif