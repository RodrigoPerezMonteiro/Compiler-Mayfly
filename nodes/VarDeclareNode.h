#ifndef __MF_VARDECLARENODE_H__
#define __MF_VARDECLARENODE_H__

#include <cdk/nodes/expressions/Simple.h>
#include <cdk/nodes/expressions/Expression.h>
#include <cdk/semantics/ExpressionType.h>
#include <cdk/nodes/Node.h>

namespace mayfly {
  namespace node {

    class VarDeclareNode: public cdk::node::Node {
    
    private:
      
    bool _Public = false;
    bool _Constant = false;
    ExpressionType *_EType;
    std::string *_Name;
    
    public:
      inline VarDeclareNode(int lineno, bool publicstate, bool constant, ExpressionType *type, std::string *name) :
			  
          cdk::node::Node(lineno),
          _Public(publicstate),
          _Constant(constant),
          _EType(type),
          _Name(name) {}
          
          
      const char *name() const {
        return "VarDeclareNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processVarDeclareNode(this, level);
      }
      
      
      inline ExpressionType *type(){
	return _EType;
      }
      
      inline std::string *getname(){
	return _Name;
      }
    };
  } // namespace node
} // namespace mayfly

#endif 
