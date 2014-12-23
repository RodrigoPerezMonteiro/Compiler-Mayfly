// $Id: SemanticProcessor.h,v 1.14 2013-05-14 22:08:40 ist173701 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_SEMANTICPROCESSOR_H__
#define __MF_SEMANTICS_SEMANTICPROCESSOR_H__

#include <string>
#include <iostream>

/* include node forward declarations */
#define __NODE_DECLARATIONS_ONLY__
#include "nodes/all.h"  // automatically generated
#undef __NODE_DECLARATIONS_ONLY__

//!
//! Print nodes as XML elements to the output stream.
//!
class SemanticProcessor {
  //! The output stream
  std::ostream &_os;

protected:
  //! Debug flag
  bool _debug;

protected:
  SemanticProcessor(std::ostream &o = std::cout, bool debug = false) :
      _os(o), _debug(debug) {
  }
  inline std::ostream &os() {
    return _os;
  }

public:
  virtual ~SemanticProcessor() {
  }

public:
  // CDK nodes (general)
  virtual void processNil(cdk::node::Nil * const node, int lvl) = 0;
  virtual void processData(cdk::node::Data * const node, int lvl) = 0;
  virtual void processComposite(cdk::node::Composite * const node, int lvl) = 0;
  virtual void processSequence(cdk::node::Sequence * const node, int lvl) = 0;

public:
  virtual void processInteger(cdk::node::expression::Integer * const node, int lvl) = 0;
  virtual void processDouble(cdk::node::expression::Double * const node, int lvl) = 0;
  virtual void processString(cdk::node::expression::String * const node, int lvl) = 0;
  virtual void processIdentifier(cdk::node::expression::Identifier * const node, int lvl) = 0;

public:
  virtual void processNEG(cdk::node::expression::NEG * const node, int lvl) = 0;

public:
  virtual void processADD(cdk::node::expression::ADD * const node, int lvl) = 0;
  virtual void processSUB(cdk::node::expression::SUB * const node, int lvl) = 0;
  virtual void processMUL(cdk::node::expression::MUL * const node, int lvl) = 0;
  virtual void processDIV(cdk::node::expression::DIV * const node, int lvl) = 0;
  virtual void processMOD(cdk::node::expression::MOD * const node, int lvl) = 0;
  virtual void processLT(cdk::node::expression::LT * const node, int lvl) = 0;
  virtual void processLE(cdk::node::expression::LE * const node, int lvl) = 0;
  virtual void processGE(cdk::node::expression::GE * const node, int lvl) = 0;
  virtual void processGT(cdk::node::expression::GT * const node, int lvl) = 0;
  virtual void processNE(cdk::node::expression::NE * const node, int lvl) = 0;
  virtual void processEQ(cdk::node::expression::EQ * const node, int lvl) = 0;

public:
  // Mayfly-specific expressions and left-values
  virtual void processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl) = 0;
  virtual void processLeftValueAsterisco(mayfly::node::expression::LeftValueAsterisco * const node, int lvl) = 0;
  virtual void processAND(mayfly::node::expression::AND * const node, int lvl) = 0;
  virtual void processOR(mayfly::node::expression::OR * const node, int lvl) = 0;
  virtual void processINC(mayfly::node::expression::INC * const node, int lvl) = 0;
  virtual void processDEC(mayfly::node::expression::DEC * const node, int lvl) = 0;
  virtual void processNOT(mayfly::node::expression::NOT * const node, int lvl) = 0;
  virtual void processMemAloc(mayfly::node::expression::MemAloc * const node, int lvl) = 0;
  virtual void processIndex(mayfly::node::expression::Index * const node, int lvl) = 0;
  virtual void processInvocation(mayfly::node::expression::Invocation * const node, int lvl) = 0;
  virtual void processReferenceNode(mayfly::node::expression::ReferenceNode * const node, int lvl) = 0;
  virtual void processVectorNode(mayfly::node::expression::VectorNode * const node, int lvl) = 0;
  virtual void processReadNode(mayfly::node::expression::ReadNode * const node, int lvl) = 0;
  virtual void processAssignmentNode(mayfly::node::expression::AssignmentNode * const node, int lvl) = 0;
  virtual void processFunctionCallNode(mayfly::node::expression::FunctionCallNode * const node, int lvl) = 0;

public:
  // Other Mayfly-specific nodes
  virtual void processFunctionDefineNode(mayfly::node::FunctionDefineNode * const node, int lvl) = 0;
  virtual void processFunctionDeclareNode(mayfly::node::FunctionDeclareNode * const node, int lvl) = 0;
  virtual void processPrintNode(mayfly::node::PrintNode * const node, int lvl) = 0;
  virtual void processIfNode(mayfly::node::IfNode * const node, int lvl) = 0;
  virtual void processIfElseNode(mayfly::node::IfElseNode * const node, int lvl) = 0;
  virtual void processForNodeDec(mayfly::node::ForNodeDec * const node, int lvl) = 0;
  virtual void processForNodeInc(mayfly::node::ForNodeInc * const node, int lvl) = 0;
  virtual void processDoWhileNode(mayfly::node::DoWhileNode * const node, int lvl) = 0;
  virtual void processBreakNode(mayfly::node::BreakNode * const node, int lvl) = 0;
  virtual void processContinueNode(mayfly::node::ContinueNode * const node, int lvl) = 0;
  virtual void processReturnNode(mayfly::node::ReturnNode * const node, int lvl) = 0;
  virtual void processBlockNode(mayfly::node::BlockNode * const node, int lvl) = 0;
  virtual void processQualifierNode(mayfly::node::QualifierNode * const node, int lvl) = 0;
  virtual void processVarDeclareNode(mayfly::node::VarDeclareNode * const node, int lvl) = 0;
  virtual void processVarDefineNode(mayfly::node::VarDefineNode * const node, int lvl) = 0;
};

#endif
