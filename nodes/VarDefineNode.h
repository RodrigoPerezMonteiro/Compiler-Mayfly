#ifndef __MF_VARDEFINENODE_H__
#define __MF_VARDEFINENODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/semantics/ExpressionType.h>

namespace mayfly {
  namespace node {

    class VarDefineNode: public cdk::node::Node {
      
    private:

    bool _Public = false;
    bool _Constant = false;
    
    ExpressionType *_EType;
    
    std::string *_Name;
    cdk::node::expression::Expression *_Value;
    
    public:
      inline VarDefineNode(int lineno,
			   bool publicstate,
			   bool constant,
			   ExpressionType *typee,
			   std::string *name, // NAME
			   cdk::node::expression::Expression *value //Right Value
			  ) :
			  
          cdk::node::Node(lineno), _Public(publicstate), _Constant(constant), _EType(typee), _Name(name), _Value(value) {}
          
      const char *name() const {
        return "VarDefineNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processVarDefineNode(this, level);
      }
      
      inline ExpressionType *type(){
	return _EType;
      }
      
      inline cdk::node::expression::Expression *value(){
	return _Value;
      }
      
            
      inline std::string *getname(){
	return _Name;
      }

    };
  } // namespace node
} // namespace mayfly

#endif