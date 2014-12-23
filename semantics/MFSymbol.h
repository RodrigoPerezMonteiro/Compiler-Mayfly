// $Id: MFSymbol.h,v 1.6 2013-05-21 01:03:27 ist173701 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_SYMBOL_H__
#define __MF_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/semantics/ExpressionType.h>
#include <cdk/nodes/expressions/Expression.h>

class MFSymbol {
  ExpressionType* _type;
  
  std::string _name;

  cdk::node::expression::Expression *_value;

  bool _isPublic;
  bool _isConst;
  bool _isVariable;
  bool _isDefined;
  bool _isGlobal;
  
  int _stack;
  
  cdk::node::Sequence *_arguments;
 
  public:

  inline MFSymbol(ExpressionType* type, const std::string &name, cdk::node::expression::Expression *value, bool isPublic, bool isConst, bool isVariable, bool isDefined, int stack, cdk::node::Sequence *arguments = NULL) :
    _type(type), _name(name), _value(value), _isPublic(isPublic), _isConst(isConst), _isVariable(isVariable), _isDefined(isDefined), _stack(stack), _arguments(arguments) {
  }

  inline MFSymbol(ExpressionType* type, const char *name, cdk::node::expression::Expression *value, bool isPublic, bool isConst, bool isVariable, bool isDefined, int stack, cdk::node::Sequence *arguments = NULL) :
    _type(type), _name(name), _value(value), _isPublic(isPublic), _isConst(isConst), _isVariable(isVariable), _isDefined(isDefined), _stack(stack), _arguments(arguments) {
  }
  
    inline MFSymbol(ExpressionType* type, const std::string &name) :
    _type(type), _name(name) {}

  inline MFSymbol(ExpressionType* type, const char *name) :
    _type(type), _name(name) {}


  virtual ~MFSymbol() {}
  
  //*****************************************************************************
  //********************************** GETTERS **********************************
  //*****************************************************************************
  
  inline ExpressionType *type() const {
    return _type;
  }
  
  inline const std::string &name() const {
    return _name;
  }
  
  inline cdk::node::expression::Expression *value() const {
    return _value;
  }
  
  inline bool isPublic() const {
	  return _isPublic;
  }

  inline bool isConst() const {
	  return _isConst;
  }
  
  inline bool isVariable() const {
	  return _isVariable;
  }
  
  inline bool isDefined() const {
	  return _isDefined;
  }
    
  inline bool isGlobal() const {
  	  return _isGlobal;
  }
  
  inline int stack() const {
	  return _stack;
  }
  
  inline cdk::node::Sequence *arguments() const {
	  return _arguments;
  }
  
  
  //*****************************************************************************
  //********************************** SETTERS **********************************
  //*****************************************************************************
  
  
  inline bool isPublic(bool isPublic) {
	  return _isPublic = isPublic;
  }
  
  inline bool isConst(bool isConst) {
	  return _isConst = isConst;
  }

  inline bool isVariable(bool isVariable) {
	  return _isVariable = isVariable;
  }

  inline bool isDefined(bool isDefined) {
	  return _isDefined = isDefined;
  }

  inline bool isGlobal(bool isGlobal) {
	  return _isGlobal = isGlobal;
  }

  inline int stack(int stack) {
	  return _stack = stack;
  }
  
  inline cdk::node::Sequence *arguments(cdk::node::Sequence * arguments) {
	  return _arguments = arguments;
  }
  
  inline cdk::node::expression::Expression *value(cdk::node::expression::Expression *value1) {
    return _value = value1;
  }
};

#endif