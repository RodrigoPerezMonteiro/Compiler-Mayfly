// $Id: PFwriter.h,v 1.16 2013-05-17 21:15:52 ist173701 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_PFWRITER_H__
#define __MF_SEMANTICS_PFWRITER_H__

#include <string>
#include <iostream>
#include <cdk/semantics/SymbolTable.h>
#include <cdk/generators/Postfix.h>
#include "semantics/SemanticProcessor.h"
#include "semantics/MFSymbol.h"

namespace mayfly {
  namespace semantics {

    class PFwriter: public virtual SemanticProcessor {
      cdk::semantics::SymbolTable<MFSymbol> &_symtab;
      cdk::generator::Postfix &_pf;
      int _pflabel;
      std::string _function;
      bool _isGlobal = true;

    public:
      PFwriter(std::ostream &os, bool debug, cdk::semantics::SymbolTable<MFSymbol> &symtab, cdk::generator::Postfix &pf) :
          SemanticProcessor(os, debug), _symtab(symtab), _pf(pf), _pflabel(0) {
      }

    public:
      ~PFwriter() {
        os().flush();
      }

    private:
      inline std::string generatepflabel(int pflabel) {
        std::ostringstream oss;
        if (pflabel < 0)
          oss << ".L" << -pflabel;
        else
          oss << "_L" << pflabel;
        return oss.str();
      }

    public:
      void processNil(cdk::node::Nil * const node, int lvl) {
      }
      void processData(cdk::node::Data * const node, int lvl) {
      }
      void processComposite(cdk::node::Composite * const node, int lvl) {
      }
      void processSequence(cdk::node::Sequence * const node, int lvl);

    public:
      void processInteger(cdk::node::expression::Integer * const node, int lvl);
      void processDouble(cdk::node::expression::Double * const node, int lvl);
      void processString(cdk::node::expression::String * const node, int lvl);
      void processIdentifier(cdk::node::expression::Identifier * const node, int lvl);

    public:
      void processNEG(cdk::node::expression::NEG * const node, int lvl);

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

    public:
      void processAND(mayfly::node::expression::AND * const node, int lvl);
      void processOR(mayfly::node::expression::OR * const node, int lvl);
      void processINC(mayfly::node::expression::INC * const node, int lvl);
      void processDEC(mayfly::node::expression::DEC * const node, int lvl);
      void processNOT(mayfly::node::expression::NOT * const node, int lvl);
      void processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl);
      void processLeftValueAsterisco(mayfly::node::expression::LeftValueAsterisco * const node, int lvl);
      void processMemAloc(mayfly::node::expression::MemAloc * const node, int lvl);
      void processIndex(mayfly::node::expression::Index * const node, int lvl);
      void processInvocation(mayfly::node::expression::Invocation * const node, int lvl);
      void processReferenceNode(mayfly::node::expression::ReferenceNode * const node, int lvl);
      void processVectorNode(mayfly::node::expression::VectorNode * const node, int lvl);
      void processReadNode(mayfly::node::expression::ReadNode * const node, int lvl);
      void processAssignmentNode(mayfly::node::expression::AssignmentNode * const node, int lvl);
      void processFunctionCallNode(mayfly::node::expression::FunctionCallNode * const node, int lvl);

    public:
      void processFunctionDefineNode(mayfly::node::FunctionDefineNode * const node, int lvl);
      void processFunctionDeclareNode(mayfly::node::FunctionDeclareNode * const node, int lvl);
      void processPrintNode(mayfly::node::PrintNode * const node, int lvl);
      void processIfNode(mayfly::node::IfNode * const node, int lvl);
      void processIfElseNode(mayfly::node::IfElseNode * const node, int lvl);
      void processForNodeDec(mayfly::node::ForNodeDec * const node, int lvl);
      void processForNodeInc(mayfly::node::ForNodeInc * const node, int lvl);
      void processDoWhileNode(mayfly::node::DoWhileNode * const node, int lvl);
      void processBreakNode(mayfly::node::BreakNode * const node, int lvl);
      void processContinueNode(mayfly::node::ContinueNode * const node, int lvl);
      void processReturnNode(mayfly::node::ReturnNode * const node, int lvl);
      void processBlockNode(mayfly::node::BlockNode * const node, int lvl);
      void processQualifierNode(mayfly::node::QualifierNode * const node, int lvl);
      void processVarDeclareNode(mayfly::node::VarDeclareNode * const node, int lvl);
      void processVarDefineNode(mayfly::node::VarDefineNode * const node, int lvl);
    };

  }    // namespace semantics
} // namespace mayfly

#endif
