#ifndef __MF_SEMANTICS_TYPEVALIDATOR_H__
#define __MF_SEMANTICS_TYPEVALIDATOR_H__

#include "semantics/SemanticProcessor.h"

#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <cdk/semantics/SymbolTable.h>
#include "semantics/MFSymbol.h"

class TypeValidator : public virtual SemanticProcessor {
    cdk::semantics::SymbolTable<MFSymbol> &_symtab;
  
  bool _error;

  public:
    ~TypeValidator();
  
  public:
    TypeValidator(std::ostream &os, cdk::semantics::SymbolTable<MFSymbol> &symtab)
      : SemanticProcessor(os), _symtab(symtab), _error(false) {}
	
  public:
    void processNode     (cdk::node::Node      *const node, int lvl);
    void processNil      (cdk::node::Nil       *const node, int lvl);
    void processData     (cdk::node::Data      *const node, int lvl);
    void processComposite(cdk::node::Composite *const node, int lvl);
    void processSequence (cdk::node::Sequence  *const node, int lvl);

    template <typename T> void processSimple(cdk::node::expression::Simple<T> *const node, int lvl);
    void processInteger   (cdk::node::expression::Integer    *const node, int lvl);
    void processDouble    (cdk::node::expression::Double     *const node, int lvl);
    void processString    (cdk::node::expression::String     *const node, int lvl);
    void processIdentifier(cdk::node::expression::Identifier *const node, int lvl);

    void processUnaryExpression(cdk::node::expression::UnaryExpression *const node, int lvl);
    void processNEG(cdk::node::expression::NEG *const node, int lvl);
    void processBinaryExpression(cdk::node::expression::BinaryExpression * const node, int lvl);
      
  public:
    void processADD(cdk::node::expression::ADD * const node, int lvl);
    void processSUB(cdk::node::expression::SUB * const node, int lvl);
    void processMUL(cdk::node::expression::MUL * const node, int lvl);
    void processDIV(cdk::node::expression::DIV * const node, int lvl);
    void processMOD(cdk::node::expression::MOD * const node, int lvl);
    void processLT(cdk::node::expression::LT * const node, int lvl);
    void processLE(cdk::node::expression::LE * const node, int lvl);
    void processGE(cdk::node::expression::GE * const node, int lvl);
    void processGT(cdk::node::expression::GT * const node, int lvl);
    void processNE(cdk::node::expression::NE * const node, int lvl);
    void processEQ(cdk::node::expression::EQ * const node, int lvl);

  protected:
    virtual void processArithmeticExpression(cdk::node::expression::BinaryExpression *const node, int lvl);
    virtual void processIntOnlyExpression   (cdk::node::expression::BinaryExpression *const node, int lvl);

  protected:
    virtual void processScalarLogicalExpression (cdk::node::expression::BinaryExpression *const node, int lvl);
    virtual void processBooleanLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl);
    virtual void processGeneralLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl);

  public:      
      void processINC(mayfly::node::expression::INC * const node, int lvl);
      void processDEC(mayfly::node::expression::DEC * const node, int lvl);
      void processAND(mayfly::node::expression::AND * const node, int lvl);
      void processOR(mayfly::node::expression::OR * const node, int lvl);
      void processMemAloc(mayfly::node::expression::MemAloc * const node, int lvl);
      void processReferenceNode(mayfly::node::expression::ReferenceNode * const node, int lvl);
      void processInvocation(mayfly::node::expression::Invocation * const node, int lvl);
      void processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl);
      void processLeftValueAsterisco(mayfly::node::expression::LeftValueAsterisco * const node, int lvl);
      void processIndex(mayfly::node::expression::Index * const node, int lvl);
      void processNOT(mayfly::node::expression::NOT * const node, int lvl);
      void processFunctionCallNode(mayfly::node::expression::FunctionCallNode * const node, int lvl);
      void processReadNode(mayfly::node::expression::ReadNode * const node, int lvl);
      void processVectorNode(mayfly::node::expression::VectorNode * const node, int lvl);
      void processAssignmentNode(mayfly::node::expression::AssignmentNode * const node, int lvl);
      
  public:
      void processBlockNode(mayfly::node::BlockNode * const node, int lvl);  
      void processBreakNode(mayfly::node::BreakNode * const node, int lvl);
      void processContinueNode(mayfly::node::ContinueNode * const node, int lvl);
      void processDoWhileNode(mayfly::node::DoWhileNode * const node, int lvl);
      void processForNodeInc(mayfly::node::ForNodeInc * const node, int lvl);
      void processForNodeDec(mayfly::node::ForNodeDec * const node, int lvl);
      void processFunctionDefineNode(mayfly::node::FunctionDefineNode * const node, int lvl);
      void processFunctionDeclareNode(mayfly::node::FunctionDeclareNode * const node, int lvl);
      void processIfElseNode(mayfly::node::IfElseNode * const node, int lvl);
      void processIfNode(mayfly::node::IfNode * const node, int lvl);
      void processPrintNode(mayfly::node::PrintNode * const node, int lvl);      
      void processQualifierNode(mayfly::node::QualifierNode * const node, int lvl);      
      void processReturnNode(mayfly::node::ReturnNode * const node, int lvl);
      void processVarDeclareNode(mayfly::node::VarDeclareNode * const node, int lvl);
      void processVarDefineNode(mayfly::node::VarDefineNode * const node, int lvl);
};

#endif 