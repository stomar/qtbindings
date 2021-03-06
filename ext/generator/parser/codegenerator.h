/*
   Copyright 2008 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <QTextStream>
#include <QString>

#include "cppparser_export.h"
#include "default_visitor.h"

class Token;

class CPPPARSER_EXPORT CodeGenerator : public DefaultVisitor
{
public:
  CodeGenerator(ParseSession* session);
  virtual ~CodeGenerator();

  QString output();

protected:
  virtual void visitAccessSpecifier (AccessSpecifierAST*);
  virtual void visitAsmDefinition (AsmDefinitionAST*);
  virtual void visitBaseClause (BaseClauseAST*);
  virtual void visitBaseSpecifier (BaseSpecifierAST*);
  virtual void visitBinaryExpression (BinaryExpressionAST*);
  virtual void visitCastExpression (CastExpressionAST*);
  virtual void visitClassMemberAccess (ClassMemberAccessAST*);
  virtual void visitClassSpecifier (ClassSpecifierAST*);
  virtual void visitCompoundStatement (CompoundStatementAST*);
  virtual void visitCondition (ConditionAST*);
  virtual void visitConditionalExpression (ConditionalExpressionAST*);
  virtual void visitCppCastExpression (CppCastExpressionAST*);
  virtual void visitCtorInitializer (CtorInitializerAST*);
  virtual void visitDeclarationStatement (DeclarationStatementAST*);
  virtual void visitDeclarator (DeclaratorAST*);
  virtual void visitDeleteExpression (DeleteExpressionAST*);
  virtual void visitDoStatement (DoStatementAST*);
  virtual void visitElaboratedTypeSpecifier (ElaboratedTypeSpecifierAST*);
  virtual void visitEnumSpecifier (EnumSpecifierAST*);
  virtual void visitEnumerator (EnumeratorAST*);
  virtual void visitExceptionSpecification (ExceptionSpecificationAST*);
  virtual void visitExpressionOrDeclarationStatement (ExpressionOrDeclarationStatementAST*);
  virtual void visitExpressionStatement (ExpressionStatementAST*);
  virtual void visitForStatement (ForStatementAST*);
  virtual void visitFunctionCall (FunctionCallAST*);
  virtual void visitFunctionDefinition (FunctionDefinitionAST*);
  virtual void visitIfStatement (IfStatementAST*);
  virtual void visitIncrDecrExpression (IncrDecrExpressionAST*);
  virtual void visitInitDeclarator (InitDeclaratorAST*);
  virtual void visitInitializer (InitializerAST*);
  virtual void visitInitializerClause (InitializerClauseAST*);
  virtual void visitJumpStatement (JumpStatementAST*);
  virtual void visitLabeledStatement (LabeledStatementAST*);
  virtual void visitLinkageBody (LinkageBodyAST*);
  virtual void visitLinkageSpecification (LinkageSpecificationAST*);
  virtual void visitMemInitializer (MemInitializerAST*);
  virtual void visitName (NameAST*);
  virtual void visitNamespace (NamespaceAST*);
  virtual void visitNamespaceAliasDefinition (NamespaceAliasDefinitionAST*);
  virtual void visitNewDeclarator (NewDeclaratorAST*);
  virtual void visitNewExpression (NewExpressionAST*);
  virtual void visitNewInitializer (NewInitializerAST*);
  virtual void visitNewTypeId (NewTypeIdAST*);
  virtual void visitOperator (OperatorAST*);
  virtual void visitOperatorFunctionId (OperatorFunctionIdAST*);
  virtual void visitParameterDeclaration (ParameterDeclarationAST*);
  virtual void visitParameterDeclarationClause (ParameterDeclarationClauseAST*);
  virtual void visitPostfixExpression (PostfixExpressionAST*);
  virtual void visitPrimaryExpression (PrimaryExpressionAST*);
  virtual void visitPtrOperator (PtrOperatorAST*);
  virtual void visitPtrToMember (PtrToMemberAST*);
  virtual void visitReturnStatement (ReturnStatementAST*);
  virtual void visitSimpleDeclaration (SimpleDeclarationAST*);
  virtual void visitSimpleTypeSpecifier (SimpleTypeSpecifierAST*);
  virtual void visitSizeofExpression (SizeofExpressionAST*);
  virtual void visitStringLiteral (StringLiteralAST*);
  virtual void visitSubscriptExpression (SubscriptExpressionAST*);
  virtual void visitSwitchStatement (SwitchStatementAST*);
  virtual void visitTemplateArgument (TemplateArgumentAST*);
  virtual void visitTemplateDeclaration (TemplateDeclarationAST*);
  virtual void visitTemplateParameter (TemplateParameterAST*);
  virtual void visitThrowExpression (ThrowExpressionAST*);
  virtual void visitTranslationUnit (TranslationUnitAST*);
  virtual void visitTryBlockStatement (TryBlockStatementAST*);
  virtual void visitCatchStatement (CatchStatementAST*);
  virtual void visitTypeId (TypeIdAST*);
  virtual void visitTypeIdentification (TypeIdentificationAST*);
  virtual void visitTypeParameter (TypeParameterAST*);
  virtual void visitTypedef (TypedefAST*);
  virtual void visitUnaryExpression (UnaryExpressionAST*);
  virtual void visitUnqualifiedName (UnqualifiedNameAST*);
  virtual void visitUsing (UsingAST*);
  virtual void visitUsingDirective (UsingDirectiveAST*);
  virtual void visitWhileStatement (WhileStatementAST*);
  virtual void visitWinDeclSpec (WinDeclSpecAST*);

private:
  void outputToken(std::size_t tokenPosition);

  void print(const ListNode<std::size_t>* tokenList, bool followingSpace = false);
  void print(std::size_t token, bool followingSpace = false);
  void printToken(int token, bool followingSpace = false);

  template <class AstNode>
  void visitCommaPrint(const ListNode<AstNode>* list)
  {
    const ListNode<AstNode>* it = list->toFront(), *end = it;
    bool first = true;
    do {
      if (first) first = false; else m_output << ",";
      visit(it->element);
      it = it->next;
    } while (it != end);
  }

  template <class _Tp>
  void commaPrintNodes(Visitor *v, const ListNode<_Tp> *nodes, const QString& separator = QString(","))
  {
    if (!nodes)
      return;

    const ListNode<_Tp>
      *it = nodes->toFront(),
      *end = it;

    bool first = true;

    do
      {
        if (first) first = false; else m_output << separator;
        v->visit(it->element);
        it = it->next;
      }
    while (it != end);
  }

  template <class _Tp>
  void surroundPrintNodes(Visitor *v, const ListNode<_Tp> *nodes, const QString& separatorLeft, const QString& separatorRight)
  {
    if (!nodes)
      return;

    const ListNode<_Tp>
      *it = nodes->toFront(),
      *end = it;

    do
      {
        m_output << separatorLeft;
        v->visit(it->element);
        m_output << separatorRight;
        it = it->next;
      }
    while (it != end);
  }

  QString m_outputString;
  QTextStream m_output;
  ParseSession* m_session;
};

#endif // CODEGENERATOR_H
