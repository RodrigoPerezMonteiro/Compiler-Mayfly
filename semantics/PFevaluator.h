// $Id: PFevaluator.h,v 1.2 2013-04-15 11:45:39 ist173701 Exp $
#ifndef __MF_SEMANTICS_PFEVALUATOR_H__
#define __MF_SEMANTICS_PFEVALUATOR_H__

#include <cdk/semantics/Evaluator.h>
#include <cdk/semantics/SymbolTable.h>
#include <cdk/nodes/Node.h>
#include <cdk/Compiler.h>
#include <cdk/generators/ix86.h>
#include "semantics/PFwriter.h"
#include "semantics/MFSymbol.h"

namespace mayfly {
  namespace semantics {

    class PFevaluator: public cdk::semantics::Evaluator {
      static PFevaluator _self;

    protected:
      inline PFevaluator(const char *target = "asm") :
          cdk::semantics::Evaluator(target) {
      }

    public:
      inline bool evaluate(cdk::Compiler *compiler) {
        std::ostream &os = compiler->ostream();

        // this symbol table will be used to check identifiers
        cdk::semantics::SymbolTable<MFSymbol> symtab;

        // this is the backend postfix machine
        cdk::generator::ix86 pf(os, compiler->debug());

        // generate assembly code from the syntax tree
        // identifiers will be checked during code generation
        PFwriter pfwriter(os, compiler->debug(), symtab, pf);
        compiler->ast()->accept(&pfwriter, 0);

        return true;
      }

    };

  } // namespace semantics
} // namespace mayfly

#endif
