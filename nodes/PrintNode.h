#ifndef __MF_PRINTNODE_H__
#define __MF_PRINTNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    class PrintNode: public cdk::node::Node {
      cdk::node::expression::Expression *_argument;
      bool _novalinha = false;

    public:
      inline PrintNode(int lineno, cdk::node::expression::Expression *argument) :
          cdk::node::Node(lineno), _argument(argument) {
      }
      
      inline PrintNode(int lineno, cdk::node::expression::Expression *argument, bool novalinha) :
          cdk::node::Node(lineno), _argument(argument), _novalinha(novalinha) {
      }

    public:
      inline cdk::node::expression::Expression *argument() {
        return _argument;
      }
      
      inline bool newline(){
	return _novalinha;
      }

      const char *name() const {
        return "PrintNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processPrintNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif