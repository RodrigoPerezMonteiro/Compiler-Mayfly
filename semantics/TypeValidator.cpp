#include <string>
#include "semantics/TypeValidator.h"
#include "nodes/all.h"  

TypeValidator::~TypeValidator() { os().flush(); }

void TypeValidator::processComposite(cdk::node::Composite *const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++)
    node->at(i)->accept(this, lvl+2);
}

void TypeValidator::processSequence(cdk::node::Sequence *const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    cdk::node::Node *n = node->node(i);
    if (n == NULL) break;
    n->accept(this, lvl+2);
  }
}

void TypeValidator::processDouble(cdk::node::expression::Double *const node, int lvl) {
	node->type(new ExpressionType(8, ExpressionType::TYPE_DOUBLE));
}

void TypeValidator::processInteger(cdk::node::expression::Integer *const node, int lvl) {
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
}

void TypeValidator::processString(cdk::node::expression::String *const node, int lvl) {
	node->type(new ExpressionType(4, ExpressionType::TYPE_STRING));
}

void TypeValidator::processIdentifier(cdk::node::expression::Identifier *const node, int lvl) {	
  const char * id = node->value().c_str();
  MFSymbol *symbol = _symtab.find(id);
  
  if(symbol!=NULL){ node->type(new ExpressionType(node->type()->size(), node->type()->name())); }
}

void TypeValidator::processNode(cdk::node::Node *const node, int lvl){
 //FIXME 
}

void TypeValidator::processNil(cdk::node::Nil *const node, int lvl){
 //FIXME 
}

void TypeValidator::processData(cdk::node::Data *const node, int lvl){
 //FIXME 
}
    
template <typename T> void TypeValidator::processSimple(cdk::node::expression::Simple<T> *const node, int lvl){
 //FIXME 
}
    
void TypeValidator::processUnaryExpression(cdk::node::expression::UnaryExpression *const node, int lvl){
 //FIXME 
}

void TypeValidator::processBinaryExpression(cdk::node::expression::BinaryExpression * const node, int lvl){
 //FIXME 
}

void TypeValidator::processNEG(cdk::node::expression::NEG *const node, int lvl) {
    node->argument()->accept(this, lvl+2);  
    try
    {
	if((node->argument()->type()->name() == ExpressionType::TYPE_INT) || (node->argument()->type()->name() == ExpressionType::TYPE_DOUBLE))
	{
	  node->type(node->argument()->type());
	}
    }
    catch(std::string s)
    {
		  throw s;
    }
}

void TypeValidator::processIntOnlyExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {
  node->left()->accept(this, lvl+2);
  if (node->left()->type()->name() != ExpressionType::TYPE_INT)
    throw std::string(" ");

  node->right()->accept(this, lvl+2);
  if (node->right()->type()->name() != ExpressionType::TYPE_INT)
    throw std::string(" ");

  node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
}

void TypeValidator::processScalarLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {
  node->left()->accept(this, lvl+2);
  if (node->left()->type()->name() != ExpressionType::TYPE_INT)
    throw std::string(" ");

  node->right()->accept(this, lvl+2);
  if (node->right()->type()->name() != ExpressionType::TYPE_INT)
    throw std::string(" ");

  node->type(new ExpressionType(4, ExpressionType::TYPE_BOOLEAN));
}

void TypeValidator::processBooleanLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {
  node->left()->accept(this, lvl+2);
  if (node->left()->type()->name() != ExpressionType::TYPE_BOOLEAN)
    throw std::string(" ");

  node->right()->accept(this, lvl+2);
  if (node->right()->type()->name() != ExpressionType::TYPE_BOOLEAN)
    throw std::string(" ");

  node->type(new ExpressionType(4, ExpressionType::TYPE_BOOLEAN));
}

void TypeValidator::processGeneralLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {
  node->left()->accept(this, lvl+2);
  node->right()->accept(this, lvl+2);
  if (node->left()->type()->name() != node->right()->type()->name())
    throw std::string(" ");
  node->type(new ExpressionType(4, ExpressionType::TYPE_BOOLEAN));
}

void TypeValidator::processADD(cdk::node::expression::ADD *const node, int lvl) {
	try
	{
	      node->left()->accept(this,lvl);
	      node->right()->accept(this,lvl);
	
	      if(node->left()->type()->name() == ExpressionType::TYPE_STRING || node->right()->type()->name() == ExpressionType::TYPE_STRING) throw std::string("!Strings");
		else
		{
			if(node->left()->type()->name() == ExpressionType::TYPE_POINTER){}
			
			else
			{
			  if(node->left()->type()->name() != node->right()->type()->name())
			  {			 
				if((node->left()->type()->name() == ExpressionType::TYPE_INT && node->right()->type()->name() == ExpressionType::TYPE_DOUBLE) ||
				    (node->left()->type()->name() == ExpressionType::TYPE_DOUBLE && node->right()->type()->name() == ExpressionType::TYPE_INT))
				{ node->type(new ExpressionType(8, ExpressionType::TYPE_DOUBLE)); }
			  }
			  
			  else { node->type(new ExpressionType(node->left()->type()->size(), node->left()->type()->name())); }
			}
		}
	}
	catch (std::string s) { throw s; }
}

void TypeValidator::processSUB(cdk::node::expression::SUB *const node, int lvl) {
      try{
	    node->left()->accept(this,lvl);
	    node->right()->accept(this,lvl);
	      if(node->left()->type()->name() == ExpressionType::TYPE_STRING || node->right()->type()->name() == ExpressionType::TYPE_STRING)
			throw std::string("!Strings");
		else{
			if(node->left()->type()->name() == ExpressionType::TYPE_POINTER){}
			else
			{
			  if(node->left()->type()->name() != node->right()->type()->name())
			  {
			    if((node->left()->type()->name() == ExpressionType::TYPE_INT && node->right()->type()->name() == ExpressionType::TYPE_DOUBLE) ||
			       (node->left()->type()->name() == ExpressionType::TYPE_DOUBLE && node->right()->type()->name() == ExpressionType::TYPE_INT))
			    { node->type(new ExpressionType(8, ExpressionType::TYPE_DOUBLE)); }
			  }
			  else{ node->type(new ExpressionType(node->left()->type()->size(), node->left()->type()->name())); }
			}
		    }	
	}
	catch (std::string s) { throw s; }	
}

void TypeValidator::processMUL(cdk::node::expression::MUL *const node, int lvl) {
	try{
	    node->left()->accept(this, lvl+2);
	    node->right()->accept(this, lvl+2);
		/*if(node->left()->type()->name() == ExpressionType::TYPE_STRING || node->right()->type()->name() == ExpressionType::TYPE_STRING)
					throw std::string("!Strings");
			else{
				if(node->left()->type()->name() != node->right()->type()->name()){
					if((node->left()->type()->name() == ExpressionType::TYPE_INT && node->right()->type()->name() == ExpressionType::TYPE_DOUBLE) ||
							(node->left()->type()->name() == ExpressionType::TYPE_DOUBLE && node->right()->type()->name() == ExpressionType::TYPE_INT)){
					node->type(new ExpressionType(8, ExpressionType::TYPE_DOUBLE));
					}
					else{
						node->type(new ExpressionType(
								node->left()->type()->size(), node->left()->type()->name()));
					}
				}
			}*/
		node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
		}
		catch (std::string s) {
			throw s;
		}
}

void TypeValidator::processDIV(cdk::node::expression::DIV *const node, int lvl) {
  	try{
	    node->left()->accept(this, lvl+2);
	    node->right()->accept(this, lvl+2);
		/*if(node->left()->type()->name() == ExpressionType::TYPE_STRING || node->right()->type()->name() == ExpressionType::TYPE_STRING)
					throw std::string("!Strings");
			else{
				if(node->left()->type()->name() != node->right()->type()->name()){
					if((node->left()->type()->name() == ExpressionType::TYPE_INT &&
							node->right()->type()->name() == ExpressionType::TYPE_DOUBLE) ||
							(node->left()->type()->name() == ExpressionType::TYPE_DOUBLE &&
									node->right()->type()->name() == ExpressionType::TYPE_INT)){
					node->type(new ExpressionType(8, ExpressionType::TYPE_DOUBLE));
					}
					else{
						node->type(new ExpressionType(
								node->left()->type()->size(), node->left()->type()->name()));
					}
				}
			}*/
		node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
		}
		catch (std::string s) {
			throw s;
		}
}


void TypeValidator::processMOD(cdk::node::expression::MOD *const node, int lvl) { 
  	try{
	    node->left()->accept(this, lvl+2);
	    node->right()->accept(this, lvl+2);
		/*if(node->left()->type()->name() != ExpressionType::TYPE_INT ||node->right()->type()->name() != ExpressionType::TYPE_INT )
		    throw std::string(" ");
		else{
		    node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
		}*/
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
	}
	catch(std::string s){
		throw s;
	}

}

void TypeValidator::processGT(cdk::node::expression::GT  *const node, int lvl) { 
  	try{
	    node->left()->accept(this, lvl+2);
	    node->right()->accept(this, lvl+2);
		/*if(node->left()->type()->name() == ExpressionType::TYPE_STRING || node->left()->type()->name() == ExpressionType::TYPE_STRING)
			throw std::string(" ");
		  if ((node->left()->type()->name() & ExpressionType::TYPE_POINTER) ||
		     (node->right()->type()->name() & ExpressionType::TYPE_POINTER)){
		     throw std::string(" ");
		  }
		else{
			node->type(new ExpressionType(4,ExpressionType::TYPE_INT));
		}*/
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
	}
	catch(std::string s){
		throw s;
	}
}

void TypeValidator::processGE(cdk::node::expression::GE  *const node, int lvl) {
  	try{
	    node->left()->accept(this, lvl+2);
	    node->right()->accept(this, lvl+2);
		/*if(node->left()->type()->name() == ExpressionType::TYPE_STRING || node->left()->type()->name() == ExpressionType::TYPE_STRING)
			throw std::string(" ");
		  if ((node->left()->type()->name() & ExpressionType::TYPE_POINTER) ||
		     (node->right()->type()->name() & ExpressionType::TYPE_POINTER)){
		     throw std::string(" ");
		  }
		else{
			node->type(new ExpressionType(4,ExpressionType::TYPE_INT));
		}*/
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
	}
	catch(std::string s){
		throw s;
	}
}

void TypeValidator::processLE(cdk::node::expression::LE  *const node, int lvl) { 
  	try{
	    node->left()->accept(this, lvl+2);
	    node->right()->accept(this, lvl+2);
		/*if(node->left()->type()->name() == ExpressionType::TYPE_STRING || node->left()->type()->name() == ExpressionType::TYPE_STRING)
			throw std::string(" ");
		  if ((node->left()->type()->name() & ExpressionType::TYPE_POINTER) ||
		     (node->right()->type()->name() & ExpressionType::TYPE_POINTER)){
		     throw std::string(" ");
		  }
		else{
			node->type(new ExpressionType(4,ExpressionType::TYPE_INT));
		}*/
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
	}
	catch(std::string s){
		throw s;
	}

}

void TypeValidator::processLT(cdk::node::expression::LT  *const node, int lvl) { 
  	try{
	    node->left()->accept(this, lvl+2);
	    node->right()->accept(this, lvl+2);
		/*if(node->left()->type()->name() == ExpressionType::TYPE_STRING || node->left()->type()->name() == ExpressionType::TYPE_STRING)
			throw std::string(" ");
		if ((node->left()->type()->name() & ExpressionType::TYPE_POINTER) ||
		    (node->right()->type()->name() & ExpressionType::TYPE_POINTER)){
		    throw std::string(" ");
		  }
		else{
			node->type(new ExpressionType(4,ExpressionType::TYPE_INT));
		}*/
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
	}
	catch(std::string s){
		throw s;
	}
	
}

void TypeValidator::processEQ(cdk::node::expression::EQ  *const node, int lvl) {
  	try{
	    node->left()->accept(this, lvl+2);
	    node->right()->accept(this, lvl+2);
		/*if(node->left()->type()->name() == ExpressionType::TYPE_STRING || node->left()->type()->name() == ExpressionType::TYPE_STRING)
			throw std::string(" ");
		  if ((node->left()->type()->name() & ExpressionType::TYPE_POINTER) ||
		    (node->right()->type()->name() & ExpressionType::TYPE_POINTER)){
		    throw std::string(" ");
		  }
		else{
			node->type(new ExpressionType(4,ExpressionType::TYPE_INT));
		}*/
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
	}
	catch(std::string s){
		throw s;
	}	
}

void TypeValidator::processNE(cdk::node::expression::NE  *const node, int lvl) { 
  	try{
	    node->left()->accept(this, lvl+2);
	    node->right()->accept(this, lvl+2);
		/*if(node->left()->type()->name() == ExpressionType::TYPE_STRING || node->left()->type()->name() == ExpressionType::TYPE_STRING)
			throw std::string(" ");
		  if ((node->left()->type()->name() & ExpressionType::TYPE_POINTER) ||
		     (node->right()->type()->name() & ExpressionType::TYPE_POINTER)){
		     throw std::string(" ");
		  }
		else{
			node->type(new ExpressionType(4,ExpressionType::TYPE_INT));
		}*/
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));	
	}
	catch(std::string s){
		throw s;
	}	
}


//********************************************MF EXPRESSIONS***************************************************************************
//********************************************MF EXPRESSIONS***************************************************************************
//********************************************MF EXPRESSIONS***************************************************************************
//********************************************MF EXPRESSIONS***************************************************************************
//********************************************MF EXPRESSIONS***************************************************************************


void TypeValidator::processINC(mayfly::node::expression::INC * const node, int lvl) {
	node->argument()->accept(this, lvl+2);
	if (node->argument()->type()->name() != ExpressionType::TYPE_INT)
	  throw std::string(" ");
	
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
}

void TypeValidator::processDEC(mayfly::node::expression::DEC * const node, int lvl) {
	node->argument()->accept(this, lvl+2);
	if (node->argument()->type()->name() != ExpressionType::TYPE_INT)
	  throw std::string(" ");
	
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
}

void TypeValidator::processAND(mayfly::node::expression::AND * const node, int lvl) {
	node->left()->accept(this, lvl+2);

	if (node->left()->type()->name() != ExpressionType::TYPE_INT)
		throw std::string(" ");
	
	node->right()->accept(this, lvl+2);
	if (node->right()->type()->name() != ExpressionType::TYPE_INT)
	  throw std::string(" ");
	
	node->type(new ExpressionType(4, ExpressionType::TYPE_BOOLEAN));
}

void TypeValidator::processMemAloc(mayfly::node::expression::MemAloc * const node, int lvl) {
	node->type(new ExpressionType(4, ExpressionType::TYPE_POINTER));
}

void TypeValidator::processOR(mayfly::node::expression::OR * const node, int lvl) {
	node->left()->accept(this, lvl+2);

	if (node->left()->type()->name() != ExpressionType::TYPE_INT)
		throw std::string(" ");
	
	node->right()->accept(this, lvl+2);
	if (node->right()->type()->name() != ExpressionType::TYPE_INT)
	  throw std::string(" ");
	
	node->type(new ExpressionType(4, ExpressionType::TYPE_BOOLEAN));
}


void TypeValidator::processReferenceNode(mayfly::node::expression::ReferenceNode * const node, int lvl) {
    node->type(new ExpressionType(4, ExpressionType::TYPE_POINTER));
}


void TypeValidator::processInvocation(mayfly::node::expression::Invocation * const node, int lvl) {
    MFSymbol *symbol = _symtab.find(node->name());
    
    if(symbol != NULL)
    node->type(symbol->type());
    
    else throw std::string("unknown function");
}

void TypeValidator::processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl) {
  MFSymbol * symbol = _symtab.find(node->value().c_str());

  if(symbol != NULL) { node->type(symbol->type()); }

  else throw std::string ("unknown leftvalue");
}

void TypeValidator::processLeftValueAsterisco(mayfly::node::expression::LeftValueAsterisco * const node, int lvl) {
//FIXME
}


void TypeValidator::processIndex(mayfly::node::expression::Index * const node, int lvl) {
//FIXME
}

void TypeValidator::processNOT(mayfly::node::expression::NOT * const node, int lvl) {
    try{
	node->accept(this, lvl+2);
	if(node->argument()->type()->name() != ExpressionType::TYPE_INT)
		  throw std::string(" ");
	    else{ node->type(new ExpressionType(4, ExpressionType::TYPE_INT)); }
       }
    catch(std::string s){ throw s; }
}

void TypeValidator::processFunctionCallNode(mayfly::node::expression::FunctionCallNode * const node, int lvl) {
	MFSymbol *symbol = _symtab.find(node->name());
	
	if (!symbol) throw std::string(node->name()) + " undeclared";
	
	if (!symbol->isVariable()) 
	throw std::string(node->name()) + " function undeclared. " + std::string(node->name()) + " is variable.";
	
	node->type(symbol->type());
	node->literals()->accept(this, lvl+2);
}

void TypeValidator::processFunctionDefineNode(mayfly::node::FunctionDefineNode * const node, int lvl) {
	node->vars()->accept(this, lvl+2);
	node->statements()->accept(this, lvl+2);
}

void TypeValidator::processFunctionDeclareNode(mayfly::node::FunctionDeclareNode * const node, int lvl) {
	node->vars()->accept(this, lvl+2);
}

void TypeValidator::processPrintNode(mayfly::node::PrintNode * const node, int lvl) {
	try{
	    node->argument()->accept(this, lvl);
	  
	    if(node->argument()->type()->name() == ExpressionType::TYPE_POINTER)
	    { throw std::string(" "); }
	   }
	catch (std::string s) { throw s; }
}

void TypeValidator::processReadNode(mayfly::node::expression::ReadNode * const node, int lvl) {
	node->argument()->accept(this, lvl+2);
	if (node->argument()->type()->name() != ExpressionType::TYPE_INT)
	  node->type(new ExpressionType(4, ExpressionType::TYPE_INT)); 
	else 
	  if(node->argument()->type()->name() != ExpressionType::TYPE_DOUBLE)
	  node->type(new ExpressionType(4, ExpressionType::TYPE_DOUBLE));
	else
	  throw std::string(" ");
}

void TypeValidator::processVectorNode(mayfly::node::expression::VectorNode * const node, int lvl) {
//FIXME
}

void TypeValidator::processAssignmentNode(mayfly::node::expression::AssignmentNode * const node, int lvl) {
	try{
	    node->value()->accept(this, lvl+2);
	    node->rvalue()->accept(this, lvl+2);
	      if(node->value()->type()->name() != node->rvalue()->type()->name())
	      {
		      if((node->value()->type()->name() == ExpressionType::TYPE_INT && node->rvalue()->type()->name() == ExpressionType::TYPE_DOUBLE)
				      ||(node->value()->type()->name() == ExpressionType::TYPE_DOUBLE && node->rvalue()->type()->name() ==ExpressionType::TYPE_INT ) )
		      { node->type(new ExpressionType(node->value()->type()->size(), node->value()->type()->name())); }
		      else{ throw std::string(" "); }
	      }
	      else{ node->type(node->value()->type()); }
	   }
	catch(std::string s){ throw s; }
}

//********************************************MF NODES***************************************************************************
//********************************************MF NODES***************************************************************************
//********************************************MF NODES***************************************************************************
//********************************************MF NODES***************************************************************************
//********************************************MF NODES***************************************************************************


void TypeValidator::processIfNode(mayfly::node::IfNode * const node, int lvl) {
  try
  {
    node->condition()->accept(this, lvl+2);
    if (node->condition()->type()->name() != ExpressionType::TYPE_INT) throw std::string(" ");
  }
  catch (std::string s) { throw s; }
}


void TypeValidator::processReturnNode(mayfly::node::ReturnNode * const node, int lvl) {
//FIXME
}


void TypeValidator::processIfElseNode(mayfly::node::IfElseNode * const node, int lvl) {
  try 
  {
    node->condition()->accept(this, lvl+2);
    if (node->condition()->type()->name() != ExpressionType::TYPE_INT) throw std::string(" ");
  }
  catch (std::string s) { throw s; }
}


void TypeValidator::processBreakNode(mayfly::node::BreakNode * const node, int lvl) {
      try {
	    node->value()->accept(this, lvl+2);
	    if (node->value()->type()->name() != ExpressionType::TYPE_INT)
	      throw std::string(" ");
	  }
	  
	  catch (std::string s) { throw s; }
}


void TypeValidator::processContinueNode(mayfly::node::ContinueNode * const node, int lvl) {
      try {
	    node->value()->accept(this, lvl+2);
	    if (node->value()->type()->name() != ExpressionType::TYPE_INT)
	      throw std::string(" ");
	  }
	  
	  catch (std::string s) { throw s; }
}


void TypeValidator::processForNodeInc(mayfly::node::ForNodeInc * const node, int lvl) {
//FIXME  
}


void TypeValidator::processForNodeDec(mayfly::node::ForNodeDec * const node, int lvl) {
//FIXME  
}


void TypeValidator::processDoWhileNode(mayfly::node::DoWhileNode * const node, int lvl) {
  try 
  {
    node->condition()->accept(this, lvl+2);
    if (node->condition()->type()->name() != ExpressionType::TYPE_BOOLEAN)
    throw std::string(" ");
  }
  catch (std::string s) { throw s; }
}

void TypeValidator::processArithmeticExpression(cdk::node::expression::BinaryExpression *const node, int lvl){
 //FIXME 
}

void TypeValidator::processBlockNode(mayfly::node::BlockNode * const node, int lvl) {
  try {
	node->declarations()->accept(this, lvl+2);
  }
	    
  catch (std::string s) {
	throw s;
  }	
}


void TypeValidator::processVarDeclareNode(mayfly::node::VarDeclareNode * const node, int lvl) {
//FIXME
}


void TypeValidator::processVarDefineNode(mayfly::node::VarDefineNode * const node, int lvl) {
	node->value()->accept(this,lvl);
	if(node->type()->name() != node->value()->type()->name())
	throw std::string("Types Don't Match");
}

void TypeValidator::processQualifierNode(mayfly::node::QualifierNode * const node, int lvl) {
//FIXME  
}