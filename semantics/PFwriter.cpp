#include <string>
#include <sstream>
#include "semantics/PFwriter.h"
#include "semantics/TypeValidator.h"
#include "semantics/StackCounter.h"
#include "nodes/all.h"

namespace cpt = mayfly;

void cpt::semantics::PFwriter::processSequence(cdk::node::Sequence * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

void cpt::semantics::PFwriter::processInteger(cdk::node::expression::Integer * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  if(!_isGlobal)
  _pf.INT(node->value()); // push an integer
  else
  _pf.CONST(node->value());
}

void cpt::semantics::PFwriter::processDouble(cdk::node::expression::Double * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  _pf.DOUBLE(node->value());
}
void cpt::semantics::PFwriter::processString(cdk::node::expression::String * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }  
  
  int newLabel;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(generatepflabel(newLabel = ++_pflabel)); // give the string a name
  _pf.STR(node->value()); // output string characters

  // Strings in Mayfly are always written:

  /* make the call */
  _pf.TEXT(); // return to the TEXT segment
  _pf.ADDR(generatepflabel(newLabel)); // the string to be printed
  _pf.CALL("prints"); // call the print rotine
  _pf.TRASH(4); // remove the string label
  _pf.CALL("println"); // print a newline
}

void cpt::semantics::PFwriter::processIdentifier(cdk::node::expression::Identifier * const node, int lvl) {
  const std::string &id = node->value();
  if (_symtab.find(id)) {
    _pf.ADDR(id);
    _pf.LOAD();
  }
}

void cpt::semantics::PFwriter::processNEG(cdk::node::expression::NEG * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

void cpt::semantics::PFwriter::processADD(cdk::node::expression::ADD * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);

  if(node->type()->name() == ExpressionType::TYPE_INT) _pf.ADD(); 
  else if(node->type()->name() == ExpressionType::TYPE_POINTER) { /* FIXME */ }
  else _pf.DADD();
  
}
void cpt::semantics::PFwriter::processSUB(cdk::node::expression::SUB * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);

  if(node->type()->name() == ExpressionType::TYPE_INT) _pf.SUB(); 
  else if(node->type()->name() == ExpressionType::TYPE_POINTER) { /* FIXME */ }
  else _pf.DSUB();
}
void cpt::semantics::PFwriter::processMUL(cdk::node::expression::MUL * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  
  if(node->type()->name() == ExpressionType::TYPE_INT) _pf.MUL(); 
  else if(node->type()->name() == ExpressionType::TYPE_POINTER) { /* FIXME */ }
  else _pf.DMUL();
}
void cpt::semantics::PFwriter::processDIV(cdk::node::expression::DIV * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }  
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  
  if(node->type()->name() == ExpressionType::TYPE_INT) _pf.DIV(); 
  else if(node->type()->name() == ExpressionType::TYPE_POINTER) { /* FIXME */ }
  else _pf.DDIV();
}
void cpt::semantics::PFwriter::processMOD(cdk::node::expression::MOD * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }  
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void cpt::semantics::PFwriter::processLT(cdk::node::expression::LT * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }  
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LT();
}
void cpt::semantics::PFwriter::processLE(cdk::node::expression::LE * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}
void cpt::semantics::PFwriter::processGE(cdk::node::expression::GE * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }  
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void cpt::semantics::PFwriter::processGT(cdk::node::expression::GT * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }  
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GT();
}
void cpt::semantics::PFwriter::processNE(cdk::node::expression::NE * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }  
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}
void cpt::semantics::PFwriter::processEQ(cdk::node::expression::EQ * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }  
  
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}

//**************************************************************************************************
//********************************** MAYFLY NODES/EXPRESSIONS **************************************
//**************************************************************************************************


void cpt::semantics::PFwriter::processLeftValue(cpt::node::expression::LeftValue * const node, int lvl) {
  _pf.TEXT();
  
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 	
  catch (std::string str) { std::cerr << "FATAL: " << node->lineno() << str << std::endl; }
  
  _pf.ADDR(node->value());
  
  if(node->type()->name()==ExpressionType::TYPE_DOUBLE) _pf.DLOAD();
  else _pf.LOAD();
  _pf.ADDR(node->value());
}

void cpt::semantics::PFwriter::processLeftValueAsterisco(cpt::node::expression::LeftValueAsterisco * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->value()->accept(this, lvl);
  _pf.LOAD();
}

void cpt::semantics::PFwriter::processAND(cpt::node::expression::AND * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  int newLabel;
  
  node->left()->accept(this,lvl);
  _pf.DUP();
  _pf.JZ(generatepflabel(newLabel = ++_pflabel));
  
  node->right()->accept(this,lvl);
  _pf.AND();
  _pf.LABEL(generatepflabel(newLabel));  
}

void cpt::semantics::PFwriter::processOR(cpt::node::expression::OR * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  int newLabel;
  
  node->left()->accept(this,lvl);
  _pf.DUP();
  _pf.JNZ(generatepflabel(newLabel = ++_pflabel));
  
  node->right()->accept(this,lvl);
  _pf.AND();
  _pf.LABEL(generatepflabel(newLabel));
}

void cpt::semantics::PFwriter::processINC(cpt::node::expression::INC * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->argument()->accept(this, lvl+2);
  _pf.DUP();
  
  if(node->argument()->type()->name() == ExpressionType::TYPE_INT) { _pf.INT(1); _pf.ADD(); }
  else if(node->argument()->type()->name() == ExpressionType::TYPE_DOUBLE) { _pf.INT(1); _pf.DADD(); }
  _pf.TRASH(4);
}

void cpt::semantics::PFwriter::processDEC(cpt::node::expression::DEC * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->argument()->accept(this, lvl+2);
  _pf.DUP();
  
  if(node->argument()->type()->name() == ExpressionType::TYPE_INT) { _pf.INT(1); _pf.SUB(); }
  else if(node->argument()->type()->name() == ExpressionType::TYPE_DOUBLE) { _pf.INT(1); _pf.DSUB(); }
  _pf.TRASH(4);
}

void cpt::semantics::PFwriter::processNOT(cpt::node::expression::NOT * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->argument()->accept(this, lvl);
  _pf.NOT();
}

void cpt::semantics::PFwriter::processMemAloc(cpt::node::expression::MemAloc * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->argument()->accept(this, lvl+2);
  _pf.INT(node->argument()->type()->size());
  _pf.MUL();
  _pf.ALLOC();
}

void cpt::semantics::PFwriter::processIndex(cpt::node::expression::Index * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  //FIXME
}

void cpt::semantics::PFwriter::processInvocation(cpt::node::expression::Invocation * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  //FIXME
}

void cpt::semantics::PFwriter::processReferenceNode(cpt::node::expression::ReferenceNode * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  //FIXME
}

void cpt::semantics::PFwriter::processVectorNode(cpt::node::expression::VectorNode * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  //FIXME
}

void cpt::semantics::PFwriter::processFunctionDefineNode(mayfly::node::FunctionDefineNode * const node, int lvl){
	_isGlobal = false;
	try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
	catch (std::string str) 
	{ std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }

	std::string *id = node->functionName();
	_isGlobal = false;
	_function = *id;

	StackCounter stackcounter(os(), _symtab);
	node->accept(&stackcounter, lvl);
	
	MFSymbol *symbol = new MFSymbol(node->tipo(), *id, node->literal(), node->pblic(), false, false, true, 0, node->vars());
	if (!_symtab.insert(*id, symbol)) 
	{
		if(_symtab.find(*id)->isDefined()) // FUNCTION REDEFINED
		{ std::cerr << "FATAL: " << node->lineno() << ": " << *id << " function redefined" << std::endl;  }
		_symtab.replace(*id, symbol);
	}
	
			
	_pf.TEXT();
	_pf.ALIGN();
	
	if(id->compare("mayfly") == 0) 
	{
		_pf.GLOBAL("_main", _pf.FUNC());
		_pf.LABEL("_main");
	}
	
	else 
	{
		_pf.GLOBAL(*id, _pf.FUNC());
		_pf.LABEL(*id);
	}
	
	_pf.ENTER(stackcounter.stack());

	_symtab.push();
	node->vars()->accept(this, lvl);

	_symtab.push();
	node->statements()->accept(this, lvl);

	_pf.POP();
	_pf.LEAVE();
	_pf.RET();
	_symtab.pop();
	_symtab.pop();
	_isGlobal = true;
	_pf.EXTERN("readi");
	_pf.EXTERN("printi");
	_pf.EXTERN("printd");
	_pf.EXTERN("prints");
	_pf.EXTERN("println");
	_isGlobal = true;
}

void cpt::semantics::PFwriter::processFunctionCallNode(mayfly::node::expression::FunctionCallNode * const node, int lvl){
	
	try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); }
	
	catch (std::string s) { std::cerr << "FATAL: " << node->lineno() << ": " << s << std::endl;  }
	_pf.CALL(node->functionName()->c_str());
}

void cpt::semantics::PFwriter::processFunctionDeclareNode(mayfly::node::FunctionDeclareNode * const node, int lvl){
	
	try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); }
	
	catch (std::string s) {	std::cerr << "FATAL: " << node->lineno() << ": " << s << std::endl;  }

	std::string *id = node->functionName();
	
	if(id->compare("mayfly") == 0) 
	{
		_pf.GLOBAL("_main", _pf.FUNC());
		_pf.LABEL("_main");
	}
	
	else 
	{
		_pf.GLOBAL(*id, _pf.FUNC());
		_pf.LABEL(*id);
	}
	
	MFSymbol *symbol = _symtab.find(*id);
	
	if(!symbol || symbol->isVariable() || symbol->isDefined()) 
	{
	    std::cerr << "FATAL: " << node->lineno() << ": " << *id << " function redeclared" << std::endl;
	} 
	
	else
	{
	    MFSymbol *symbol = new MFSymbol(node->tipo(), *id, node->literal(), node->pblic(), false, false, true, 0, node->vars());
	    _symtab.insert(*id, symbol);
	}
}

void cpt::semantics::PFwriter::processPrintNode(cpt::node::PrintNode * const node, int lvl) {
  
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); }
  catch (std::string s) { std::cerr << "FATAL: " << node->lineno() << ": " << s << std::endl; }
  
  node->argument()->accept(this, lvl);
   
  if(node->argument()->type()->name() == ExpressionType::TYPE_STRING) {
    _pf.EXTERN("prints");
    _pf.CALL("prints");
    _pf.TRASH(4);
  }
    
  else 
    if(node->argument()->type()->name() == ExpressionType::TYPE_DOUBLE) {
    _pf.EXTERN("printd");
    _pf.CALL("printd");
    _pf.TRASH(8);
  }
  
  else {
    _pf.EXTERN("printi");
    _pf.CALL("printi");
    _pf.TRASH(4);
  } 
  
  //if(node->newline()) { _pf.EXTERN("println"); _pf.CALL("println"); }
}

void cpt::semantics::PFwriter::processReadNode(cpt::node::expression::ReadNode * const node, int lvl) {
  _pf.CALL("readi");
  _pf.PUSH();
  
  node->argument()->accept(this, lvl);
  _pf.STORE();
}

void cpt::semantics::PFwriter::processAssignmentNode(cpt::node::expression::AssignmentNode * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  node->value()->accept(this, lvl);
  node->rvalue()->accept(this, lvl);
  
  _pf.STORE();
}

void cpt::semantics::PFwriter::processIfNode(cpt::node::IfNode * const node, int lvl) {
  int newLabel;
  
  node->condition()->accept(this, lvl); //CONDITION
  _pf.JZ(generatepflabel(newLabel = ++_pflabel));
  
  node->block()->accept(this, lvl + 2); //BLOCK
  _pf.LABEL(generatepflabel(newLabel));
  
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
}

void cpt::semantics::PFwriter::processIfElseNode(cpt::node::IfElseNode * const node, int lvl) {
  int newLabel, newLabel2;
  
  node->condition()->accept(this, lvl); //CONDITION
  _pf.JZ(generatepflabel(newLabel = ++_pflabel));
  
  node->thenblock()->accept(this, lvl + 2); //THEN-BLOCK
  _pf.JMP(generatepflabel(newLabel2 = ++_pflabel));
  _pf.LABEL(generatepflabel(newLabel));
  
  node->elseblock()->accept(this, lvl + 2); //ELSE-BLOCK
  _pf.LABEL(generatepflabel(newLabel = newLabel2));
  
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
}

void cpt::semantics::PFwriter::processForNodeDec(cpt::node::ForNodeDec * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  //FIXME
}

void cpt::semantics::PFwriter::processForNodeInc(cpt::node::ForNodeInc * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  //FIXME
}

void cpt::semantics::PFwriter::processDoWhileNode(cpt::node::DoWhileNode * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  int newLabel, newLabel1;
  
  _pf.LABEL(generatepflabel(newLabel = ++_pflabel));
  node->condition()->accept(this, lvl); //CONDITION
  _pf.JZ(generatepflabel(newLabel1 = ++_pflabel));
  
  node->block()->accept(this, lvl + 2); //BLOCK
  _pf.JMP(generatepflabel(newLabel));
  _pf.LABEL(generatepflabel(newLabel1));
}

void cpt::semantics::PFwriter::processBreakNode(cpt::node::BreakNode * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  //FIXME
}

void cpt::semantics::PFwriter::processContinueNode(cpt::node::ContinueNode * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  //FIXME
}

void cpt::semantics::PFwriter::processReturnNode(cpt::node::ReturnNode * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }

  _pf.LEAVE();
  _pf.RET();
}

void cpt::semantics::PFwriter::processBlockNode(cpt::node::BlockNode * const node, int lvl) {
  node->instructions()->accept(this,lvl);
  node->declarations()->accept(this,lvl);
  
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); } 
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
}

void cpt::semantics::PFwriter::processQualifierNode(cpt::node::QualifierNode * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); }
	
  catch (std::string str) 
  { std::cerr << "FATAL: " << node->lineno() << ": " << str << std::endl; }
  
  //FIXME
}

void cpt::semantics::PFwriter::processVarDeclareNode(cpt::node::VarDeclareNode * const node, int lvl) {
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); }
  catch (std::string s) { std::cerr << "FATAL: " << node->lineno() << ": " << s << std::endl; }

  int newLabel;
  std::string *id = node->getname();
  MFSymbol * symbol = _symtab.find(*id);
      
    if(symbol==NULL){ _symtab.insert(*id ,new MFSymbol(node->type(), *id)); }
    
    _pf.BSS();
    _pf.ALIGN(); 
    _pf.LABEL(generatepflabel(newLabel = ++_pflabel));
    
    if(node->type()->name()==ExpressionType::TYPE_DOUBLE){ _pf.DOUBLE(0); }
    else if(node->type()->name()==ExpressionType::TYPE_INT){ _pf.INT(0); }
    _pf.TEXT();
}

void cpt::semantics::PFwriter::processVarDefineNode(cpt::node::VarDefineNode * const node, int lvl) {
  
  try { TypeValidator typeval(os(), _symtab); node->accept(&typeval, lvl); }
  catch (std::string s) { std::cerr << "FATAL: " << node->lineno() << ": " << s << std::endl; }

  int newLabel;
  std::string *id = node->getname();
  MFSymbol * symbol = _symtab.find(*id);
  
    if(symbol==NULL){ _symtab.insert(*id, new MFSymbol(node->type(), *id)); }
  
   _pf.DATA();
   _pf.ALIGN();
   _pf.LABEL(generatepflabel(newLabel = ++_pflabel));
   
   node->value()->accept(this,lvl) ;  
   _pf.TEXT();
   node->value()->accept(this,lvl) ; 
   _pf.ADDRA(*id);  
}