

#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"


namespace S2 {


void Parser::SynErr(int n) {
	if (errDist >= minErrDist) errors->SynErr(la->line, la->col, n);
	errDist = 0;
}

void Parser::SemErr(const wchar_t* msg) {
	if (errDist >= minErrDist) errors->Error(t->line, t->col, msg);
	errDist = 0;
}

void Parser::Get() {
	for (;;) {
		t = la;
		la = scanner->Scan();
		if (la->kind <= maxT) { ++errDist; break; }
		if (la->kind == _ddtSym) {
		}
		if (la->kind == _optionSym) {
		}

		if (dummyToken != t) {
			dummyToken->kind = t->kind;
			dummyToken->pos = t->pos;
			dummyToken->col = t->col;
			dummyToken->line = t->line;
			dummyToken->next = NULL;
			coco_string_delete(dummyToken->val);
			dummyToken->val = coco_string_create(t->val);
			t = dummyToken;
		}
		la = t;
	}
}

void Parser::Expect(int n) {
	if (la->kind==n) Get(); else { SynErr(n); }
}

void Parser::ExpectWeak(int n, int follow) {
	if (la->kind == n) Get();
	else {
		SynErr(n);
		while (!StartOf(follow)) Get();
	}
}

bool Parser::WeakSeparator(int n, int syFol, int repFol) {
	if (la->kind == n) {Get(); return true;}
	else if (StartOf(repFol)) {return false;}
	else {
		SynErr(n);
		while (!(StartOf(syFol) || StartOf(repFol) || StartOf(0))) {
			Get();
		}
		return StartOf(syFol);
	}
}

void Parser::S2() {
		s2 = std::make_shared<class S2>(); 
		unsigned curline = la->line, curcol = la->col; 
		StatementPtr statement; 
		while (la->kind == 15 /* "[" */ || la->kind == 17 /* "format" */ || la->kind == 20 /* "import" */) {
			Statement(statement);
			s2->statements.push_back(statement); 
		}
		s2->_line = curline; s2->_col = curcol; 
}

void Parser::Statement(StatementPtr& production) {
		unsigned curline = la->line, curcol = la->col; 
		FormatPtr format; 
		ImportPtr import; 
		if (la->kind == 15 /* "[" */ || la->kind == 17 /* "format" */) {
			Format(format);
			production = format; 
		} else if (la->kind == 20 /* "import" */) {
			Import(import);
			production = import; 
		} else SynErr(22);
		production->_line = curline; production->_col = curcol; 
}

void Parser::TypeVariable(TypeVariablePtr& production) {
		production = std::make_shared<class TypeVariable>(); 
		unsigned curline = la->line, curcol = la->col; 
		Expect(_customTokenTypeVariable);
		production->content = t->val; 
		production->_line = curline; production->_col = curcol; 
}

void Parser::StructName(StructNamePtr& production) {
		production = std::make_shared<class StructName>(); 
		unsigned curline = la->line, curcol = la->col; 
		Expect(_pascalcase);
		production->content = t->val; 
		production->_line = curline; production->_col = curcol; 
}

void Parser::MemberName(MemberNamePtr& production) {
		production = std::make_shared<class MemberName>(); 
		unsigned curline = la->line, curcol = la->col; 
		Expect(_camelcase);
		production->content = t->val; 
		production->_line = curline; production->_col = curcol; 
}

void Parser::NumberLiteral(NumberLiteralPtr& production) {
		production = std::make_shared<class NumberLiteral>(); 
		unsigned curline = la->line, curcol = la->col; 
		Expect(_number);
		production->content = t->val; 
		production->_line = curline; production->_col = curcol; 
}

void Parser::StringLiteral(StringLiteralPtr& production) {
		production = std::make_shared<class StringLiteral>(); 
		unsigned curline = la->line, curcol = la->col; 
		Expect(_string);
		production->content = t->val; 
		production->_line = curline; production->_col = curcol; 
}

void Parser::TypeIdentifier(TypeIdentifierPtr& production) {
		production = std::make_shared<class TypeIdentifier>(); 
		unsigned curline = la->line, curcol = la->col; 
		StructNamePtr structname; 
		TypeVariablePtr typevariable; 
		TypeParameterArgumentsPtr typeparameterarguments; 
		if (la->kind == _pascalcase) {
			StructName(structname);
			production->structname = structname; 
		} else if (la->kind == _customTokenTypeVariable) {
			TypeVariable(typevariable);
			production->typevariable = typevariable; 
		} else SynErr(23);
		if (la->kind == 10 /* "<" */) {
			TypeParameterArguments(typeparameterarguments);
			production->typeparameterarguments.push_back(typeparameterarguments); 
		}
		production->_line = curline; production->_col = curcol; 
}

void Parser::TypeParameterArguments(TypeParameterArgumentsPtr& production) {
		production = std::make_shared<class TypeParameterArguments>(); 
		unsigned curline = la->line, curcol = la->col; 
		TypeExpressionPtr typeexpression; 
		Expect(10 /* "<" */);
		TypeExpression(typeexpression);
		production->typeexpressions.push_back(typeexpression); 
		while (la->kind == 11 /* "," */) {
			Get();
			TypeExpression(typeexpression);
			production->typeexpressions.push_back(typeexpression); 
		}
		Expect(12 /* ">" */);
		production->_line = curline; production->_col = curcol; 
}

void Parser::TypeExpression(TypeExpressionPtr& production) {
		unsigned curline = la->line, curcol = la->col; 
		TypeIdentifierPtr typeidentifier; 
		TypeIdentifier(typeidentifier);
		production = typeidentifier; 
		production->_line = curline; production->_col = curcol; 
}

void Parser::TypeDeclaration(TypeDeclarationPtr& production) {
		production = std::make_shared<class TypeDeclaration>(); 
		unsigned curline = la->line, curcol = la->col; 
		StructNamePtr structname; 
		TypeParametersPtr typeparameters; 
		StructName(structname);
		production->structname = structname; 
		if (la->kind == 10 /* "<" */) {
			TypeParameters(typeparameters);
			production->typeparameters.push_back(typeparameters); 
		}
		production->_line = curline; production->_col = curcol; 
}

void Parser::TypeParameters(TypeParametersPtr& production) {
		production = std::make_shared<class TypeParameters>(); 
		unsigned curline = la->line, curcol = la->col; 
		TypeVariablePtr typevariable; 
		Expect(10 /* "<" */);
		TypeVariable(typevariable);
		production->typevariables.push_back(typevariable); 
		while (la->kind == 11 /* "," */) {
			Get();
			TypeVariable(typevariable);
			production->typevariables.push_back(typevariable); 
		}
		Expect(12 /* ">" */);
		production->_line = curline; production->_col = curcol; 
}

void Parser::NumberLit(NumberLitPtr& production) {
		production = std::make_shared<class NumberLit>(); 
		unsigned curline = la->line, curcol = la->col; 
		NumberLiteralPtr numberliteral; 
		NumberLiteral(numberliteral);
		production->numberliteral = numberliteral; 
		production->_line = curline; production->_col = curcol; 
}

void Parser::Expression(ExpressionPtr& production) {
		unsigned curline = la->line, curcol = la->col; 
		NumberLitPtr numberlit; 
		NumberLit(numberlit);
		production = numberlit; 
		production->_line = curline; production->_col = curcol; 
}

void Parser::AttributeParam(AttributeParamPtr& production) {
		production = std::make_shared<class AttributeParam>(); 
		unsigned curline = la->line, curcol = la->col; 
		MemberNamePtr membername; 
		ExpressionPtr expression; 
		MemberName(membername);
		production->membername = membername; 
		Expect(13 /* "=" */);
		Expression(expression);
		production->expression = expression; 
		production->_line = curline; production->_col = curcol; 
}

void Parser::AttributeParamList(AttributeParamListPtr& production) {
		production = std::make_shared<class AttributeParamList>(); 
		unsigned curline = la->line, curcol = la->col; 
		AttributeParamPtr attributeparam; 
		Expect(14 /* ":" */);
		AttributeParam(attributeparam);
		production->attributeparams.push_back(attributeparam); 
		while (la->kind == 11 /* "," */) {
			Get();
			AttributeParam(attributeparam);
			production->attributeparams.push_back(attributeparam); 
		}
		production->_line = curline; production->_col = curcol; 
}

void Parser::Attribute(AttributePtr& production) {
		production = std::make_shared<class Attribute>(); 
		unsigned curline = la->line, curcol = la->col; 
		TypeExpressionPtr typeexpression; 
		AttributeParamListPtr attributeparamlist; 
		Expect(15 /* "[" */);
		TypeExpression(typeexpression);
		production->typeexpression = typeexpression; 
		if (la->kind == 14 /* ":" */) {
			AttributeParamList(attributeparamlist);
			production->attributeparamlists.push_back(attributeparamlist); 
		}
		Expect(16 /* "]" */);
		production->_line = curline; production->_col = curcol; 
}

void Parser::Member(MemberPtr& production) {
		production = std::make_shared<class Member>(); 
		unsigned curline = la->line, curcol = la->col; 
		AttributePtr attribute; 
		TypeIdentifierPtr typeidentifier; 
		MemberNamePtr membername; 
		while (la->kind == 15 /* "[" */) {
			Attribute(attribute);
			production->attributes.push_back(attribute); 
		}
		TypeIdentifier(typeidentifier);
		production->typeidentifier = typeidentifier; 
		MemberName(membername);
		production->membernames.push_back(membername); 
		while (la->kind == 11 /* "," */) {
			Get();
			MemberName(membername);
			production->membernames.push_back(membername); 
		}
		production->_line = curline; production->_col = curcol; 
}

void Parser::Format(FormatPtr& production) {
		production = std::make_shared<class Format>(); 
		unsigned curline = la->line, curcol = la->col; 
		AttributePtr attribute; 
		TypeDeclarationPtr typedeclaration; 
		MemberPtr member; 
		while (la->kind == 15 /* "[" */) {
			Attribute(attribute);
			production->attributes.push_back(attribute); 
		}
		Expect(17 /* "format" */);
		TypeDeclaration(typedeclaration);
		production->typedeclaration = typedeclaration; 
		Expect(18 /* "{" */);
		Member(member);
		production->members.push_back(member); 
		while (la->kind == _pascalcase || la->kind == _customTokenTypeVariable || la->kind == 15 /* "[" */) {
			Member(member);
			production->members.push_back(member); 
		}
		Expect(19 /* "}" */);
		production->_line = curline; production->_col = curcol; 
}

void Parser::Import(ImportPtr& production) {
		production = std::make_shared<class Import>(); 
		unsigned curline = la->line, curcol = la->col; 
		StringLiteralPtr stringliteral; 
		Expect(20 /* "import" */);
		StringLiteral(stringliteral);
		production->stringliteral = stringliteral; 
		production->_line = curline; production->_col = curcol; 
}




// If the user declared a method Init and a mehtod Destroy they should
// be called in the contructur and the destructor respctively.
//
// The following templates are used to recognize if the user declared
// the methods Init and Destroy.

template<typename T>
struct ParserInitExistsRecognizer {
	template<typename U, void (U::*)() = &U::Init>
	struct ExistsIfInitIsDefinedMarker{};

	struct InitIsMissingType {
		char dummy1;
	};
	
	struct InitExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static InitIsMissingType is_here(...);

	// exist only if ExistsIfInitIsDefinedMarker is defined
	template<typename U>
	static InitExistsType is_here(ExistsIfInitIsDefinedMarker<U>*);

	enum { InitExists = (sizeof(is_here<T>(NULL)) == sizeof(InitExistsType)) };
};

template<typename T>
struct ParserDestroyExistsRecognizer {
	template<typename U, void (U::*)() = &U::Destroy>
	struct ExistsIfDestroyIsDefinedMarker{};

	struct DestroyIsMissingType {
		char dummy1;
	};
	
	struct DestroyExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static DestroyIsMissingType is_here(...);

	// exist only if ExistsIfDestroyIsDefinedMarker is defined
	template<typename U>
	static DestroyExistsType is_here(ExistsIfDestroyIsDefinedMarker<U>*);

	enum { DestroyExists = (sizeof(is_here<T>(NULL)) == sizeof(DestroyExistsType)) };
};

// The folloing templates are used to call the Init and Destroy methods if they exist.

// Generic case of the ParserInitCaller, gets used if the Init method is missing
template<typename T, bool = ParserInitExistsRecognizer<T>::InitExists>
struct ParserInitCaller {
	static void CallInit(T *t) {
		// nothing to do
	}
};

// True case of the ParserInitCaller, gets used if the Init method exists
template<typename T>
struct ParserInitCaller<T, true> {
	static void CallInit(T *t) {
		t->Init();
	}
};

// Generic case of the ParserDestroyCaller, gets used if the Destroy method is missing
template<typename T, bool = ParserDestroyExistsRecognizer<T>::DestroyExists>
struct ParserDestroyCaller {
	static void CallDestroy(T *t) {
		// nothing to do
	}
};

// True case of the ParserDestroyCaller, gets used if the Destroy method exists
template<typename T>
struct ParserDestroyCaller<T, true> {
	static void CallDestroy(T *t) {
		t->Destroy();
	}
};

void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	la->val = coco_string_create(L"Dummy Token");
	Get();
	S2();
	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 21;

	ParserInitCaller<Parser>::CallInit(this);
	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors();
}

bool Parser::StartOf(int s) {
	const bool T = true;
	const bool x = false;

	static bool set[1][23] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x}
	};



	return set[s][la->kind];
}

Parser::~Parser() {
	ParserDestroyCaller<Parser>::CallDestroy(this);
	delete errors;
	delete dummyToken;
}

Errors::Errors() {
	count = 0;
}

void Errors::SynErr(int line, int col, int n) {
	wchar_t* s;
	switch (n) {
			case 0: s = coco_string_create(L"EOF expected"); break;
			case 1: s = coco_string_create(L"pascalcase expected"); break;
			case 2: s = coco_string_create(L"camelcase expected"); break;
			case 3: s = coco_string_create(L"number expected"); break;
			case 4: s = coco_string_create(L"hexinteger expected"); break;
			case 5: s = coco_string_create(L"string expected"); break;
			case 6: s = coco_string_create(L"badString expected"); break;
			case 7: s = coco_string_create(L"char expected"); break;
			case 8: s = coco_string_create(L"endOfLine expected"); break;
			case 9: s = coco_string_create(L"customTokenTypeVariable expected"); break;
			case 10: s = coco_string_create(L"\"<\" expected"); break;
			case 11: s = coco_string_create(L"\",\" expected"); break;
			case 12: s = coco_string_create(L"\">\" expected"); break;
			case 13: s = coco_string_create(L"\"=\" expected"); break;
			case 14: s = coco_string_create(L"\":\" expected"); break;
			case 15: s = coco_string_create(L"\"[\" expected"); break;
			case 16: s = coco_string_create(L"\"]\" expected"); break;
			case 17: s = coco_string_create(L"\"format\" expected"); break;
			case 18: s = coco_string_create(L"\"{\" expected"); break;
			case 19: s = coco_string_create(L"\"}\" expected"); break;
			case 20: s = coco_string_create(L"\"import\" expected"); break;
			case 21: s = coco_string_create(L"??? expected"); break;
			case 22: s = coco_string_create(L"invalid Statement"); break;
			case 23: s = coco_string_create(L"invalid TypeIdentifier"); break;

		default:
		{
			wchar_t format[20];
			coco_swprintf(format, 20, L"error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	throw ParserException(line, col, s);
	//wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	coco_string_delete(s);
	count++;
}

void Errors::Error(int line, int col, const wchar_t *s) {
	throw ParserException(line, col, s);
	//wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	count++;
}

void Errors::Warning(int line, int col, const wchar_t *s) {
	warnings.push_back(ParserException(line, col, s));
	//wprintf(L"-- line %d col %d: %ls\n", line, col, s);
}

void Errors::Warning(const wchar_t *s) {
	warnings.push_back(ParserException(0, 0, s));
	//wprintf(L"%ls\n", s);
}

void Errors::Exception(const wchar_t* s) {
	throw ParserException(0, 0, s);
	//wprintf(L"%ls", s); 
	exit(1);
}

} // namespace

