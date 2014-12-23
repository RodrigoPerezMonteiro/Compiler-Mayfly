#ifndef __MF_BLOCKNODE_H__
#define __MF_BLOCKNODE_H__

#include <cdk/nodes/Node.h>

namespace mayfly {
  namespace node {

    class BlockNode: public cdk::node::Node {
    cdk::node::Sequence *_declaration;
    cdk::node::Sequence *_instruction;
      
      
    public:
      inline BlockNode(int lineno, cdk::node::Sequence *declaration, cdk::node::Sequence *instruction) :
          cdk::node::Node(lineno),
          _declaration(declaration),
          _instruction(instruction)
          {}
          

      const char *name() const {
        return "BlockNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processBlockNode(this, level);
      }
      
      cdk::node::Sequence *declarations(){
    
	return _declaration;
      }
      
      cdk::node::Sequence *instructions(){
      
	return _instruction;
	
      }

    };

  } // namespace node
} // namespace mayfly

#endif
 
 
 
