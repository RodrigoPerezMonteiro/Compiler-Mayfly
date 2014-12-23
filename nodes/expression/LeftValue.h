#ifndef __MF_NODE_EXPRESSION_LEFTVALUE_H__
#define __MF_NODE_EXPRESSION_LEFTVALUE_H__

#include <cdk/nodes/expressions/Simple.h>
#include <string>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {


      class LeftValue: public cdk::node::expression::Simple<std::string> {
	ExpressionType *_type;

      public:
        inline LeftValue(int lineno, const char*s) :
          cdk::node::expression::Simple<std::string>(lineno, s) {}
	inline LeftValue(int lineno, const std::string &s) :
          cdk::node::expression::Simple<std::string>(lineno, s) {}
	
	inline LeftValue(int lineno, const std::string *s) :
          cdk::node::expression::Simple<std::string>(lineno, *s) {}
	
	inline LeftValue(int lineno) :
          cdk::node::expression::Simple<std::string>(lineno, "") {}
       
       
	inline ExpressionType *typee() {
	  return _type;
	}

	inline void *setType(ExpressionType *type1) {
	  return _type = type1;
	}
        
        const char *name() const {
          return "LeftValue";
        }
        
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processLeftValue(this, level);
        }

      };

    } // expression
  } // node
} // mayfly
#endif