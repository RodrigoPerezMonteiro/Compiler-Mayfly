#ifndef __MF_FUNCTIONCALLNODE_H__
#define __MF_FUNCTIONCALLNODE_H__

#include <cdk/nodes/Node.h>

namespace mayfly {
  namespace node {
    namespace expression {

    class FunctionCallNode: public cdk::node::expression::Expression {
      
      std::string *_functionName;
      cdk::node::Sequence *_literals;
      

    public:
      
     inline FunctionCallNode(int lineno, std::string *functionName, cdk::node::Sequence *literals) :
          cdk::node::expression::Expression(lineno),
          _functionName(functionName),
          _literals(literals)
      {}
      
     inline FunctionCallNode(int lineno, std::string *functionName) :
          cdk::node::expression::Expression(lineno),
          _functionName(functionName)
      {}


      const char *name() const {
        return "FunctionCallNode";
      }
      
      inline std::string *functionName() {
        return _functionName;
      }

      inline cdk::node::Sequence *literals() {
	return _literals;
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processFunctionCallNode(this, level);
      }

    };
    
      
    } //namespace expression
  } // namespace node
} // namespace mayfly

#endif
