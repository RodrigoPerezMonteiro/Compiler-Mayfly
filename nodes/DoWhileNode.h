#ifndef __MF_DOWHILENODE_H__
#define __MF_DOWHILENODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing while-cycle nodes.
     */
    class DoWhileNode: public cdk::node::Node {
      cdk::node::Node *_block;
      cdk::node::expression::Expression *_condition;

    public:
      inline DoWhileNode(int lineno, cdk::node::Node *block, cdk::node::expression::Expression *condition) :
          cdk::node::Node(lineno),
          _block(block),
          _condition(condition)	   
      {}

    public:
      inline cdk::node::Node *block() {
        return _block;
      }
      
      inline cdk::node::expression::Expression *condition() {
        return _condition;
      }

      const char *name() const {
        return "DoWhileNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processDoWhileNode(this, level);
      }

    };

  }// namespace node
} // namespace mayfly

#endif 
