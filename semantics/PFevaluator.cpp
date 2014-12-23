// $Id: PFevaluator.cpp,v 1.2 2013-04-15 11:45:39 ist173701 Exp $
#include "semantics/PFevaluator.h"

/**
 * Postfix for ix86.
 * @var create and register an evaluator for ASM targets.
 */
mayfly::semantics::PFevaluator mayfly::semantics::PFevaluator::_self("asm");
