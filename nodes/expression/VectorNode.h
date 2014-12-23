#ifndef __MF_VECTORNODE_H__
#define __MF_VECTORNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {
    namespace expression {
    
    class VectorNode: public cdk::node::expression::Expression {

      mayfly::node::expression::LeftValue *_lvalue;
      cdk::node::expression::Expression *_value;
      
    public:
      inline VectorNode(int lineno, mayfly::node::expression::LeftValue *lvalue, cdk::node::expression::Expression *value) :
          cdk::node::expression::Expression(lineno),
          _lvalue(lvalue),
          _value(value) {}
          

      const char *name() const {
        return "VectorNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processVectorNode(this, level);
      }
      
      inline mayfly::node::expression::LeftValue *lvalue() {
	return _lvalue;
      }
      
      inline cdk::node::expression::Expression *value() {
	return _value;
      }
    };
    
    } //namespace expression
  } // namespace node
} // namespace mayfly

#endif