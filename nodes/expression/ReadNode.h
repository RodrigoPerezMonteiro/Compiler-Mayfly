#ifndef __MF_READNODE_H__
#define __MF_READNODE_H__

#include <cdk/nodes/Node.h>
#include "nodes/expression/LeftValue.h"

namespace mayfly {
  namespace node {
    namespace expression {

    /**
     * Class for describing read nodes.
     */
    class ReadNode: public cdk::node::expression::Expression {
      cdk::node::expression::Expression *_argument;

    public:
      inline ReadNode(int lineno, cdk::node::expression::Identifier *argument) :
          cdk::node::expression::Expression (lineno), _argument(argument) {
      }
     
    inline ReadNode(int lineno) :
          cdk::node::expression::Expression (lineno)
	  {}

    public:
      inline cdk::node::expression::Expression *argument() {
        return _argument;
      }

      const char *name() const {
        return "ReadNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processReadNode(this, level);
      }

    };
    
    } //namespace expression
  } // namespace node
} // namespace mayfly

#endif