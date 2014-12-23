#ifndef __MF_RETURNNODE_H__
#define __MF_RETURNNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing if-then nodes.
     */
    class ReturnNode: public cdk::node::Node {

    public:
      inline ReturnNode(int lineno) :
          cdk::node::Node(lineno) {}
          

      const char *name() const {
        return "ReturnNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processReturnNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif
 
 
 
