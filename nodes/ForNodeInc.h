#ifndef __MF_FORNODEINC_H__
#define __MF_FORNODEINC_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    class ForNodeInc: public cdk::node::Node {

      mayfly::node::expression::LeftValue *_leftValue;
      
      cdk::node::expression::Expression *_init;
      cdk::node::expression::Expression *_condition;
      cdk::node::expression::Expression *_incr;
      cdk::node::Node *_block;

    public:
      
      //cdk::node::expression::Expression
      
      inline ForNodeInc(int lineno,
			mayfly::node::expression::LeftValue *leftValue,
			cdk::node::expression::Expression *init,
			cdk::node::expression::Expression *condition,
			cdk::node::expression::Expression *incr,
			cdk::node::Node *block) :
          cdk::node::Node(lineno), _leftValue(leftValue),  _init(init),  _condition(condition), _incr(incr),  _block(block) {
      }
      
      //cdk::node::expression::Expression SEM INCR
      
      inline ForNodeInc(int lineno,
			mayfly::node::expression::LeftValue *leftValue,
			cdk::node::expression::Expression *init,
			cdk::node::expression::Expression *condition,
			cdk::node::Node *block) :
          cdk::node::Node(lineno), _leftValue(leftValue),  _init(init),  _condition(condition), _block(block) {
      }
            
    public:
      
      inline mayfly::node::expression::LeftValue *lvalue() {
        return _leftValue;
      }
      
      inline cdk::node::expression::Expression *init() {
        return _init;
      }
      
      inline cdk::node::expression::Expression *condition() {
        return _condition;
      }
      
      inline cdk::node::expression::Expression *incr() {
        return _incr;
      }
      
      inline cdk::node::Node *block() {
        return _block;
      }

      const char *name() const {
        return "ForNodeInc";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processForNodeInc(this, level);
      }

    };

  }// namespace node
} // namespace mayfly
#endif 
