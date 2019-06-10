

#if !defined(S2_COCO_PARSER_H__)
#define S2_COCO_PARSER_H__

#include <iostream>
#include <memory>
#include "S2.hpp"


#include "Scanner.h"

namespace S2 {


class ParserException {

	int line,col;
	std::wstring message;

public:
	ParserException(int line, int col, std::wstring message) :
	line(line), col(col), message(message)
	{
	}

	int LineNumber() const
	{
		return line;
	}

	int ColumnNumber() const
	{
		return col;
	}

	std::wstring GetMessage() const
	{
		return message;
	}
};

class Errors {
public:
	int count;			// number of errors detected
	std::vector<ParserException> warnings;

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_pascalcase=1,
		_camelcase=2,
		_number=3,
		_hexinteger=4,
		_string=5,
		_badString=6,
		_char=7,
		_endOfLine=8,
		_customTokenTypeVariable=9,
		_ddtSym=22,
		_optionSym=23
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token

S2Ptr s2;



	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void S2();
	void Statement(StatementPtr& production);
	void TypeVariable(TypeVariablePtr& production);
	void StructName(StructNamePtr& production);
	void MemberName(MemberNamePtr& production);
	void NumberLiteral(NumberLiteralPtr& production);
	void StringLiteral(StringLiteralPtr& production);
	void TypeIdentifier(TypeIdentifierPtr& production);
	void TypeParameterArguments(TypeParameterArgumentsPtr& production);
	void TypeExpression(TypeExpressionPtr& production);
	void TypeDeclaration(TypeDeclarationPtr& production);
	void TypeParameters(TypeParametersPtr& production);
	void NumberLit(NumberLitPtr& production);
	void Expression(ExpressionPtr& production);
	void AttributeParam(AttributeParamPtr& production);
	void AttributeParamList(AttributeParamListPtr& production);
	void Attribute(AttributePtr& production);
	void Member(MemberPtr& production);
	void Format(FormatPtr& production);
	void Import(ImportPtr& production);

	void Parse();

}; // end Parser

} // namespace


#endif

