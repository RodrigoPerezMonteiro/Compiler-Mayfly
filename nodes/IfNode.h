// $Id: IfNode.h,v 1.2 2013-03-22 01:32:58 ist173701 Exp $ -*- c++ -*-
#ifndef __MF_IFNODE_H__
#define __MF_IFNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing if-then nodes.
     */
    class IfNode: public cdk::node::Node {
      cdk::node::expression::Expression *_condition;
      cdk::node::Node *_block;

    public:
      inline IfNode(int lineno, cdk::node::expression::Expression *condition, cdk::node::Node *block) :
          cdk::node::Node(lineno), _condition(condition), _block(block) {
      }

    public:
      inline cdk::node::expression::Expression *condition() {
        return _condition;
      }
      inline cdk::node::Node *block() {
        return _block;
      }

      const char *name() const {
        return "IfNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processIfNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif
