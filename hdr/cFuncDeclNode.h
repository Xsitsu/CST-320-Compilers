#pragma once
//**************************************
// cFuncDeclNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 10, 2021
//

#include "cAstNode.h"
#include "cStmtsNode.h"
#include "cDeclsNode.h"
#include "cDeclNode.h"

#include "lex.h"

class cFuncDeclNode : public cDeclNode
{
    public:
        cFuncDeclNode(cSymbol *type, cSymbol *name) : cDeclNode()
        {
            cSymbol* funcName = g_symbolTable->FindLocal(name->GetName());
            if (funcName != nullptr)
            {
                cDeclNode* decl = funcName->GetDecl();
                if (decl->IsFunc())
                {
                    cFuncDeclNode* funcDecl = static_cast<cFuncDeclNode*>(decl);
                    if (funcDecl->GetType() != type->GetDecl())
                    {
                        std::string error = name->GetName();
                        error += " previously defined with different return type";
                        SemanticError(error);
                    }
                    else
                    {
                        AddAllChildren(funcDecl);
                        name->SetDecl(this);
                    }
                }
            }
            else
            {
                AddChild(type);
                AddChild(name);
                AddChild(nullptr); // params
                AddChild(nullptr); // decls
                AddChild(nullptr); // stmts
                g_symbolTable->Insert(name);
                name->SetDecl(this);
            }
        }

        void AddParams(cDeclsNode *params)
        {
            cDeclsNode *oldParams = GetParams();
            if (oldParams != nullptr)
            {
                bool matching = true;
                bool matchingLen = true;
                if (params == nullptr)
                {
                    matchingLen = false;
                }
                else if (params->NumDecls() != oldParams->NumDecls())
                {
                    matchingLen = false;
                }
                else
                {
                    for (int i = 0; i < params->NumDecls(); i++)
                    {
                        cDeclNode *oldP = oldParams->GetDecl(i);
                        cDeclNode *p = params->GetDecl(i);
                        if (oldP->GetType() != p->GetType())
                        {
                            matching = false;
                        }
                    }
                }

                if (matchingLen == false)
                {
                    std::string error = GetName()->GetName();
                    error += " redeclared with a different number of parameters";
                    SemanticError(error);
                }

                if (matching == false)
                {
                    std::string error = GetName()->GetName();
                    error += " previously defined with different parameters";
                    SemanticError(error);
                }
            }

            SetChild(2, params);
        }

        void AddDecls(cDeclsNode *decls)
        {
            SetChild(3, decls);
        }

        void AddStmts(cStmtsNode *stmts)
        {
            if (this->GetStmts() != nullptr)
            {
                std::string error = GetName()->GetName();
                error += " already has a definition";
                SemanticError(error);
            }
            else
            {
                SetChild(4, stmts);
            }
        }

        bool IsDefined()
        {
            return (GetStmts() != nullptr);
        }

        int NumParams()
        {
            cDeclsNode* params = this->GetParams();
            if (params != nullptr)
            {
                return params->NumDecls();
            }
            return 0;
        }

        virtual bool IsFunc() { return true; }

        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        virtual cDeclNode* GetType()
        {
            cSymbol *type = this->GetTypeSymbol();
            if (type != nullptr) return type->GetDecl(); 
            return nullptr;
        }

        cSymbol* GetTypeSymbol()
        {
            return static_cast<cSymbol*>(GetChild(0));
        }

        virtual cSymbol* GetName()
        {
            return static_cast<cSymbol*>(GetChild(1));
        }

        cDeclsNode* GetParams()
        {
            return static_cast<cDeclsNode*>(GetChild(2));
        }

        cDeclsNode* GetDecls()
        {
            return static_cast<cDeclsNode*>(GetChild(3));
        }

        cStmtsNode* GetStmts()
        {
            return static_cast<cStmtsNode*>(GetChild(4));
        }
};