#ifndef __MF_REFERENCENODE_H__
#define __MF_REFERENCENODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {
    namespace expression {
    
    class ReferenceNode: public cdk::node::expression::UnaryExpression {

    public:
      inline ReferenceNode(int lineno, cdk::node::expression::Expression *value) :
          cdk::node::expression::UnaryExpression(lineno, value) {}
          

      const char *name() const {
        return "ReferenceNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processReferenceNode(this, level);
      }

    };
    
    } //namespace expression
  } // namespace node
} // namespace mayfly

#endif
 
 
 
 
