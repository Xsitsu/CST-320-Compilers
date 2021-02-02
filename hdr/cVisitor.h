#pragma once
//*******************************************************
// Declaration of the visitor class.
// This class is used to implement the visitor pattern.
//
// As you add AST node types, you must add the forward declaration and
// the virtual Visit function.
// Lab 4 will work without this, BUT Lab 5 will go more smoothly if you
// keep this class current with all your AST node types.


// Forward (incomplete) declarations for all AST node types
class cAstNode;
class cBlockNode;
class cBinaryExprNode;
class cDeclNode;
class cDeclsNode;
class cVarDeclNode;
class cExprNode;
class cIntExprNode;
class cFloatExprNode;
class cOpNode;
class cPrintNode;
class cProgramNode;
class cStmtNode;
class cStmtsNode;
class cSymbol;

class cVisitor
{
    public:
        cVisitor() {}

        virtual void VisitAllNodes(cAstNode *node) = 0;

        virtual void Visit(cAstNode *node);
        virtual void Visit(cBlockNode *node);
        virtual void Visit(cBinaryExprNode *node);
        virtual void Visit(cDeclNode *node);
        virtual void Visit(cDeclsNode *node);
        virtual void Visit(cVarDeclNode *node);
        virtual void Visit(cExprNode *node);
        virtual void Visit(cIntExprNode *node);
        virtual void Visit(cFloatExprNode *node);
        virtual void Visit(cOpNode *node);
        virtual void Visit(cPrintNode *node);
        virtual void Visit(cProgramNode *node);
        virtual void Visit(cStmtNode *node);
        virtual void Visit(cStmtsNode *node);
        virtual void Visit(cSymbol *node);
};
