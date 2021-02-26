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
                cFuncDeclNode* funcDecl = static_cast<cFuncDeclNode*>(name->GetDecl());
                if (!funcDecl->IsDefined())
                {
                    std::string error = name->GetName();
                    error += " is not fully defined";
                    SemanticError(error);
                }
                else if (funcDecl->NumParams() != this->NumParams())
                {
                    std::string error = name->GetName();
                    error += " called with wrong number of arguments";
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

        cParamListNode* GetParams()
        {
            return static_cast<cParamListNode*>(GetChild(1));
        }

        virtual cDeclNode *GetType()
        {
            return this->GetName()->GetDecl()->GetType();
        }

        int NumParams()
        {
            cParamListNode* params = this->GetParams();
            if (params != nullptr)
            {
                return params->NumParams();
            }
            return 0;
        }
};