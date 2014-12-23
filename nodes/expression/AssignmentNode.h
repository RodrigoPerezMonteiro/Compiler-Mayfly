// $Id: AssignmentNode.h,v 1.3 2013-05-14 22:57:56 ist172976 Exp $ -*- c++ -*-
#ifndef __MF_ASSIGNMENTNODE_H__
#define __MF_ASSIGNMENTNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>
#include "nodes/expression/LeftValue.h"

namespace mayfly {
  namespace node {
    namespace expression {

    /**
     * Class for describing assignment nodes.
     */
    class AssignmentNode: public cdk::node::expression::Expression {
      cdk::node::expression::Expression *_value;
      
      //UM DESTES 3 SERÁ UTILIZADO
      
      cdk::node::expression::Identifier *_id;
      mayfly::node::expression::Index *_index;
      
      ///////////////////////////
      
      cdk::node::expression::Expression *_rvalue;
      

    public:
      inline AssignmentNode(int lineno, cdk::node::expression::Expression *value, cdk::node::expression::Expression *rvalue) :
          cdk::node::expression::Expression(lineno), _value(value), _rvalue(rvalue) {
      }
      
      
      //cdk::node::expression::Identifier

      inline AssignmentNode(int lineno, cdk::node::expression::Identifier *id, cdk::node::expression::Expression *rvalue) :
          cdk::node::expression::Expression(lineno), _id(id), _rvalue(rvalue) {
      }
      
     
      
      //mayfly::node::expression::Index

      inline AssignmentNode(int lineno, mayfly::node::expression::Index *index, cdk::node::expression::Expression *rvalue) :
          cdk::node::expression::Expression(lineno), _index(index), _rvalue(rvalue) {
      }
      

    public:
      inline cdk::node::expression::Expression *value() {
        return _value;
      }
      inline cdk::node::expression::Expression *rvalue() {
        return _rvalue;
      }

      const char *name() const {
        return "AssignmentNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processAssignmentNode(this, level);
      }
      

    };

    } //namespace expression
  }// namespace node
} // namespace mayfly

#endif
