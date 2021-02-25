#pragma once
//**************************************
// cFuncExprNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 10, 2021
//

#include "cAstNode.h"
#include "cParamListNode.h"
#include "cExprNode.h"

class cFuncExprNode : public cExprNode
{
    public:
        cFuncExprNode(cSymbol *name, cParamListNode *params) : cExprNode()
        {
            AddChild(name);
            AddChild(params);

            if (name->GetDecl() == nullptr)
            {
                std::string error = name->GetName();
                error += " is not declared";
                SemanticError(error);
            }
            else if (!name->GetDecl()->IsFunc())
            {
                std::string error = name->GetName();
                error += " is not a function";
                SemanticError(error);
            }
            else
            {
                cFuncDecl* funcDecl = static_cast<cFuncDecl*>(name->GetDecl());
                if (!funcDecl->IsDefined())
                {
                    std::string error = name->GetName();
                    error += " is not fully defined";
                    SemanticError(error);
                }
            }
        }

        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        cSymbol* GetName()
        {
            return static_cast<cSymbol*>(GetChild(0));
        }

        virtual cDeclNode *GetType()
        {
            return this->GetName()->GetDecl()->GetType();
        }
};