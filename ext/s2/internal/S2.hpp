
#ifndef S2_HPP
#define S2_HPP

/*
	WARNING: This file is generated using ruco. Please modify the .ruco file if you wish to change anything
	https://github.com/davidsiaw/ruco
*/

#include <string>
#include <memory>
#include <vector>

namespace S2
{

enum StatementType
{
	FORMAT_STATEMENT,
	IMPORT_STATEMENT
};

class Statement 
{
public:
	unsigned _line, _col;
	virtual StatementType get_statement_type() const = 0;
};
typedef std::shared_ptr<Statement> StatementPtr;
typedef std::vector<StatementPtr> StatementArray;

class S2 
{
public:
	unsigned _line, _col;
	StatementArray statements;
};
typedef std::shared_ptr<S2> S2Ptr;
typedef std::vector<S2Ptr> S2Array;

class StructName 
{
public:
	unsigned _line, _col;
	std::wstring content;
};
typedef std::shared_ptr<StructName> StructNamePtr;
typedef std::vector<StructNamePtr> StructNameArray;

class TypeVariable 
{
public:
	unsigned _line, _col;
	std::wstring content;
};
typedef std::shared_ptr<TypeVariable> TypeVariablePtr;
typedef std::vector<TypeVariablePtr> TypeVariableArray;

enum TypeExpressionType
{
	TYPEIDENTIFIER_TYPEEXPRESSION
};

class TypeExpression 
{
public:
	unsigned _line, _col;
	virtual TypeExpressionType get_typeexpression_type() const = 0;
};
typedef std::shared_ptr<TypeExpression> TypeExpressionPtr;
typedef std::vector<TypeExpressionPtr> TypeExpressionArray;

class TypeParameterArguments 
{
public:
	unsigned _line, _col;
	TypeExpressionArray typeexpressions;
};
typedef std::shared_ptr<TypeParameterArguments> TypeParameterArgumentsPtr;
typedef std::vector<TypeParameterArgumentsPtr> TypeParameterArgumentsArray;

class TypeIdentifier : public TypeExpression
{
public:
	unsigned _line, _col;
	StructNamePtr structname;
	TypeVariablePtr typevariable;
	TypeParameterArgumentsArray typeparameterarguments;
	virtual TypeExpressionType get_typeexpression_type() const
	{
		return TYPEIDENTIFIER_TYPEEXPRESSION;
	}

};
typedef std::shared_ptr<TypeIdentifier> TypeIdentifierPtr;
typedef std::vector<TypeIdentifierPtr> TypeIdentifierArray;

class TypeParameters 
{
public:
	unsigned _line, _col;
	TypeVariableArray typevariables;
};
typedef std::shared_ptr<TypeParameters> TypeParametersPtr;
typedef std::vector<TypeParametersPtr> TypeParametersArray;

class TypeDeclaration 
{
public:
	unsigned _line, _col;
	StructNamePtr structname;
	TypeParametersArray typeparameters;
};
typedef std::shared_ptr<TypeDeclaration> TypeDeclarationPtr;
typedef std::vector<TypeDeclarationPtr> TypeDeclarationArray;

class NumberLiteral 
{
public:
	unsigned _line, _col;
	std::wstring content;
};
typedef std::shared_ptr<NumberLiteral> NumberLiteralPtr;
typedef std::vector<NumberLiteralPtr> NumberLiteralArray;

enum ExpressionType
{
	NUMBERLIT_EXPRESSION
};

class Expression 
{
public:
	unsigned _line, _col;
	virtual ExpressionType get_expression_type() const = 0;
};
typedef std::shared_ptr<Expression> ExpressionPtr;
typedef std::vector<ExpressionPtr> ExpressionArray;

class NumberLit : public Expression
{
public:
	unsigned _line, _col;
	NumberLiteralPtr numberliteral;
	virtual ExpressionType get_expression_type() const
	{
		return NUMBERLIT_EXPRESSION;
	}

};
typedef std::shared_ptr<NumberLit> NumberLitPtr;
typedef std::vector<NumberLitPtr> NumberLitArray;

class MemberName 
{
public:
	unsigned _line, _col;
	std::wstring content;
};
typedef std::shared_ptr<MemberName> MemberNamePtr;
typedef std::vector<MemberNamePtr> MemberNameArray;

class AttributeParam 
{
public:
	unsigned _line, _col;
	MemberNamePtr membername;
	ExpressionPtr expression;
};
typedef std::shared_ptr<AttributeParam> AttributeParamPtr;
typedef std::vector<AttributeParamPtr> AttributeParamArray;

class AttributeParamList 
{
public:
	unsigned _line, _col;
	AttributeParamArray attributeparams;
};
typedef std::shared_ptr<AttributeParamList> AttributeParamListPtr;
typedef std::vector<AttributeParamListPtr> AttributeParamListArray;

class Attribute 
{
public:
	unsigned _line, _col;
	TypeExpressionPtr typeexpression;
	AttributeParamListArray attributeparamlists;
};
typedef std::shared_ptr<Attribute> AttributePtr;
typedef std::vector<AttributePtr> AttributeArray;

class Member 
{
public:
	unsigned _line, _col;
	AttributeArray attributes;
	TypeIdentifierPtr typeidentifier;
	MemberNameArray membernames;
};
typedef std::shared_ptr<Member> MemberPtr;
typedef std::vector<MemberPtr> MemberArray;

class Format : public Statement
{
public:
	unsigned _line, _col;
	AttributeArray attributes;
	TypeDeclarationPtr typedeclaration;
	MemberArray members;
	virtual StatementType get_statement_type() const
	{
		return FORMAT_STATEMENT;
	}

};
typedef std::shared_ptr<Format> FormatPtr;
typedef std::vector<FormatPtr> FormatArray;

class StringLiteral 
{
public:
	unsigned _line, _col;
	std::wstring content;
};
typedef std::shared_ptr<StringLiteral> StringLiteralPtr;
typedef std::vector<StringLiteralPtr> StringLiteralArray;

class Import : public Statement
{
public:
	unsigned _line, _col;
	StringLiteralPtr stringliteral;
	virtual StatementType get_statement_type() const
	{
		return IMPORT_STATEMENT;
	}

};
typedef std::shared_ptr<Import> ImportPtr;
typedef std::vector<ImportPtr> ImportArray;


}

#endif // S2_HPP

