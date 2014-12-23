#include <string>
#include "semantics/StackCounter.h"
#include "nodes/all.h"


StackCounter::~StackCounter() {}

void StackCounter::processComposite(cdk::node::Composite *const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++)
    node->at(i)->accept(this, lvl+2);
}

void StackCounter::processSequence(cdk::node::Sequence *const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    cdk::node::Node *n = node->node(i);
    if (n == NULL) break;
    n->accept(this, lvl+2);
  }
}

void StackCounter::processInteger(cdk::node::expression::Integer *const node, int lvl) {
	_stack += 4;
}


void StackCounter::processDouble(cdk::node::expression::Double *const node, int lvl) {
	_stack += 8;
}


void StackCounter::processString(cdk::node::expression::String *const node, int lvl) {
	_stack += 4;
}

void StackCounter::processIdentifier(cdk::node::expression::Identifier *const node, int lvl) {}
void StackCounter::processUnaryExpression(cdk::node::expression::UnaryExpression *const node, int lvl) {}
void StackCounter::processBinaryExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {}
void StackCounter::processNEG(cdk::node::expression::NEG *const node, int lvl) {}
void StackCounter::processADD(cdk::node::expression::ADD *const node, int lvl) {}
void StackCounter::processSUB(cdk::node::expression::SUB *const node, int lvl) {}
void StackCounter::processMUL(cdk::node::expression::MUL *const node, int lvl) {}
void StackCounter::processDIV(cdk::node::expression::DIV *const node, int lvl) {}
void StackCounter::processMOD(cdk::node::expression::MOD *const node, int lvl) {}

void StackCounter::processGT(cdk::node::expression::GT  *const node, int lvl) {}
void StackCounter::processGE(cdk::node::expression::GE  *const node, int lvl) {}
void StackCounter::processLE(cdk::node::expression::LE  *const node, int lvl) {}
void StackCounter::processLT(cdk::node::expression::LT  *const node, int lvl) {}
void StackCounter::processEQ(cdk::node::expression::EQ  *const node, int lvl) {}
void StackCounter::processNE(cdk::node::expression::NE  *const node, int lvl) {}



//--------------------------------MAYFLY NODES--------------------------------------------------------

void StackCounter::processINC(mayfly::node::expression::INC * const node, int lvl){ 
  
}

void StackCounter::processDEC(mayfly::node::expression::DEC * const node, int lvl){ 
  
}

void StackCounter::processAND(mayfly::node::expression::AND * const node, int lvl){ 
  
}

void StackCounter::processOR(mayfly::node::expression::OR * const node, int lvl){
  
}

void StackCounter::processNOT(mayfly::node::expression::NOT * const node, int lvl){
  
}

void StackCounter::processMemAloc(mayfly::node::expression::MemAloc * const node, int lvl){ 
  
}

void StackCounter::processReferenceNode(mayfly::node::expression::ReferenceNode * const node, int lvl){ 
  
}

void StackCounter::processInvocation(mayfly::node::expression::Invocation * const node, int lvl){
  
}


void StackCounter::processIndex(mayfly::node::expression::Index * const node, int lvl){
  
}

void StackCounter::processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl){
  
}

void StackCounter::processLeftValueAsterisco(mayfly::node::expression::LeftValueAsterisco * const node, int lvl){
  
}

void StackCounter::processReadNode(mayfly::node::expression::ReadNode * const node, int lvl){ 
  
}

void StackCounter::processAssignmentNode(mayfly::node::expression::AssignmentNode * const node, int lvl){

}

void StackCounter::processBlockNode(mayfly::node::BlockNode *const node, int lvl){
	
	  if(node->declarations() != NULL) 
	  {
	    cdk::node::Sequence *s1 = node->declarations();
	      for(size_t a = 0; a < s1->size(); a++)
	      {
		s1->node(a)->accept(this, lvl+2);  
	      }
	  }

	  if(node->instructions() != NULL)
	  {  
	    cdk::node::Sequence *s2 = node->instructions();
	      for(size_t b = 0; b < s2->size(); b++)
	      {
		s2->node(b)->accept(this, lvl+2);  
	      }	 
	  }
		  
}

void StackCounter::processBreakNode(mayfly::node::BreakNode * const node, int lvl){}

void StackCounter::processFunctionCallNode(mayfly::node::expression::FunctionCallNode * const node, int lvl){
 //FIXME
}


void StackCounter::processVectorNode(mayfly::node::expression::VectorNode * const node, int lvl){
 //FIXME
}


void StackCounter::processFunctionDeclareNode(mayfly::node::FunctionDeclareNode * const node, int lvl){
 //FIXME
}

void StackCounter::processFunctionDefineNode(mayfly::node::FunctionDefineNode * const node, int lvl){
  //_stack += node->tipo()->size();
  //node->statements()->accept(this, lvl+2);
}


void StackCounter::processPrintNode(mayfly::node::PrintNode * const node, int lvl){}

void StackCounter::processDoWhileNode(mayfly::node::DoWhileNode * const node, int lvl){
	node->block()->accept(this, lvl+2);
}

void StackCounter::processIfNode(mayfly::node::IfNode * const node, int lvl){
	node->block()->accept(this, lvl+2);
}

void StackCounter::processIfElseNode(mayfly::node::IfElseNode * const node, int lvl){
	node->thenblock()->accept(this, lvl+2);
	node->elseblock()->accept(this, lvl+2);
}

void StackCounter::processForNodeInc(mayfly::node::ForNodeInc * const node, int lvl){
	node->block()->accept(this, lvl+2);
}

void StackCounter::processForNodeDec(mayfly::node::ForNodeDec * const node, int lvl){
	node->block()->accept(this, lvl+2);
}


void StackCounter::processContinueNode(mayfly::node::ContinueNode * const node, int lvl){}

void StackCounter::processReturnNode(mayfly::node::ReturnNode * const node, int lvl){}

void StackCounter::processQualifierNode(mayfly::node::QualifierNode * const node, int lvl){}

void StackCounter::processVarDeclareNode(mayfly::node::VarDeclareNode * const node, int lvl){
      // _stack += node->type()->size();
}

void StackCounter::processVarDefineNode(mayfly::node::VarDefineNode * const node, int lvl){
      // _stack += node->type()->size();
}