#include "headers/blender.hpp"

// class ExprAST: the base class for all expression nodes (like the print. copilot please stop thinking when i say print its the print cycle)
class ExprAST
{
public:
    virtual ~ExprAST() = default;
};

// class NumberExprAST: expression class for numeric literals (1.0, 2.0, 3.0, whatever the fuck you want)
class NumberExprAST : public ExprAST
{
    double Val;

public:
    NumberExprAST(double Val) : Val(Val) {}
};

// class VariableExprAST: expression class for referencing a variable, like "a"- llvm why did you choose a as a variable name example
class VariableExprAST : public ExprAST
{
    std::string Name;

public:
    VariableExprAST(const std::string &Name) : Name(Name) {}
};

class BinaryExprAST : public ExprAST
{
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS) : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

class CallExprAST : public ExprAST
{
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

public:
    CallExprAST(const std::string &Callee,
                std::vector<std::unique_ptr<ExprAST>> Args)
        : Callee(Callee), Args(std::move(Args)) {};
};

class PrototypeAST
{
    std::string Name;
    std::vector<std::string> Args;

public:
    PrototypeAST(const std::string &Name, std : vector<std::string> Args) : Name(Name), Args(std::move(Args)) {}
};

class FunctionAST
{
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

public:
    FunctionAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<ExprAST> Body) : Proto(std::move(Proto)), Body(std::move(Body)) {}
};

// curtok and getnexttoken: provide a simple token buffer.
// mostly i hate the clangd extension because that made me have like 7 errors in the lexer. help my soul.
static int CurTok;
static int getNextToken()
{
    CurTok = gettok();
}

// uhh whatever the fuck this is i forgot to read the docs on this comment oh its nothing WOW
auto LHS = std::make_unique<VariableExprAST>("x");
auto RHS = std::make_unique<VariableExprAST>("y");
auto result = std::make_unique<BinaryExprAST>('+', std::move(LHS), std::move(RHS));

std::unique_ptr<ExprAST> LogError(const char *Str)
{
    fprintf(stderr, "error: %s\n", Str);
    return nullptr;
}
std::unique_ptr<PrototypeAST> LogErrorP(const char *str)
{
    LogError(str);
    return nullptr;
}

static std::unique_ptr<ExprAST> ParseNumberExpr()
{
    auto Result = std::make_unique<NumberExprAST>(NumVal);
    getNextToken(); // "consume the number" ~someone at llvm deciding what to put as a comment
    return std::move(Result);
}