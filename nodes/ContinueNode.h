// $Id: ContinueNode.h,v 1.2 2013-05-17 14:20:18 ist173701 Exp $ -*- c++ -*-
#ifndef __MF_CONTINUENODE_H__
#define __MF_CONTINUENODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing if-then nodes.
     */
    class ContinueNode: public cdk::node::Node {
      
      cdk::node::expression::Integer *_value;
      cdk::node::expression::Identifier *_id;
      int _val;

    public:
      inline ContinueNode(int lineno) :
      cdk::node::Node(lineno) {}
          
      inline ContinueNode(int lineno, cdk::node::expression::Integer *value) :
      cdk::node::Node(lineno), _value(value) {}
      
      inline ContinueNode(int lineno, int val) :
      cdk::node::Node(lineno), _val(val) {}
      
      inline ContinueNode(int lineno, cdk::node::expression::Identifier *id) :
      cdk::node::Node(lineno), _id(id) {}

      const char *name() const {
        return "ContinueNode";
      }
      
      inline cdk::node::expression::Integer *value() {
        return _value;
      }
      
      inline int val() {
        return _val;
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processContinueNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif
 
 
