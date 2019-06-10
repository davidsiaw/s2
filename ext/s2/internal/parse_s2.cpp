
#include "parse_s2.hpp"

/*
	WARNING: This file is generated using ruco. Please modify the .ruco file if you wish to change anything
	https://github.com/davidsiaw/ruco
*/

namespace S2
{
	S2Ptr Parse(std::string sourceFile)
	{
		std::shared_ptr<FILE> fp (fopen(sourceFile.c_str(), "r"), fclose);
		if (!fp)
		{
			throw FileNotFoundException();
		}
		std::shared_ptr<Scanner> scanner (new Scanner(fp.get()));
		std::shared_ptr<Parser> parser (new Parser(scanner.get()));
		parser->Parse();

		return parser->s2;
	}

	picojson::object CompileS2(S2Ptr pointer);
	picojson::object CompileTypeVariable(TypeVariablePtr pointer);
	picojson::object CompileStructName(StructNamePtr pointer);
	picojson::object CompileMemberName(MemberNamePtr pointer);
	picojson::object CompileNumberLiteral(NumberLiteralPtr pointer);
	picojson::object CompileStringLiteral(StringLiteralPtr pointer);
	picojson::object CompileTypeIdentifier(TypeIdentifierPtr pointer);
	picojson::object CompileTypeExpression(TypeExpressionPtr pointer);
	picojson::object CompileTypeParameterArguments(TypeParameterArgumentsPtr pointer);
	picojson::object CompileTypeDeclaration(TypeDeclarationPtr pointer);
	picojson::object CompileTypeParameters(TypeParametersPtr pointer);
	picojson::object CompileNumberLit(NumberLitPtr pointer);
	picojson::object CompileExpression(ExpressionPtr pointer);
	picojson::object CompileAttributeParam(AttributeParamPtr pointer);
	picojson::object CompileAttributeParamList(AttributeParamListPtr pointer);
	picojson::object CompileAttribute(AttributePtr pointer);
	picojson::object CompileMember(MemberPtr pointer);
	picojson::object CompileFormat(FormatPtr pointer);
	picojson::object CompileImport(ImportPtr pointer);
	picojson::object CompileStatement(StatementPtr pointer);

	picojson::object CompileS2(S2Ptr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"S2");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>3, :type=>:id}

		picojson::array statements;

		for(unsigned i=0; i<pointer->statements.size(); i++)
		{
			statements.push_back(picojson::value(CompileStatement(pointer->statements[i])));
		}

		object[L"statements"] = picojson::value(statements);




		return object;
	}

	picojson::object CompileTypeVariable(TypeVariablePtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"TypeVariable");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:token}
		object[L"_token"] = picojson::value(pointer->content);




		return object;
	}

	picojson::object CompileStructName(StructNamePtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"StructName");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:token}
		object[L"_token"] = picojson::value(pointer->content);




		return object;
	}

	picojson::object CompileMemberName(MemberNamePtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"MemberName");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:token}
		object[L"_token"] = picojson::value(pointer->content);




		return object;
	}

	picojson::object CompileNumberLiteral(NumberLiteralPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"NumberLiteral");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:token}
		object[L"_token"] = picojson::value(pointer->content);




		return object;
	}

	picojson::object CompileStringLiteral(StringLiteralPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"StringLiteral");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:token}
		object[L"_token"] = picojson::value(pointer->content);




		return object;
	}

	picojson::object CompileTypeIdentifier(TypeIdentifierPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"TypeIdentifier");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:id}
		if (pointer->structname)
		{
			picojson::object structname;

			structname = CompileStructName(pointer->structname);

			object[L"structname"] = picojson::value(structname);
		}
		// {:count=>1, :type=>:id}
		if (pointer->typevariable)
		{
			picojson::object typevariable;

			typevariable = CompileTypeVariable(pointer->typevariable);

			object[L"typevariable"] = picojson::value(typevariable);
		}
		// {:count=>3, :type=>:id}

		picojson::array typeparameterarguments;

		for(unsigned i=0; i<pointer->typeparameterarguments.size(); i++)
		{
			typeparameterarguments.push_back(picojson::value(CompileTypeParameterArguments(pointer->typeparameterarguments[i])));
		}

		object[L"typeparameterarguments"] = picojson::value(typeparameterarguments);




		return object;
	}

	picojson::object CompileTypeExpression(TypeExpressionPtr pointer)
	{
		picojson::object object;

		// variation
		object[L"_type"] = picojson::value(L"TypeExpression");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		picojson::object content;
		switch(pointer->get_typeexpression_type())
		{
			case TYPEIDENTIFIER_TYPEEXPRESSION:
			{
				content = CompileTypeIdentifier(std::dynamic_pointer_cast<TypeIdentifier>(pointer));
				break;
			}

		}

		object[L"_content"] = picojson::value(content);

		return object;
	}

	picojson::object CompileTypeParameterArguments(TypeParameterArgumentsPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"TypeParameterArguments");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>3, :type=>:id}

		picojson::array typeexpressions;

		for(unsigned i=0; i<pointer->typeexpressions.size(); i++)
		{
			typeexpressions.push_back(picojson::value(CompileTypeExpression(pointer->typeexpressions[i])));
		}

		object[L"typeexpressions"] = picojson::value(typeexpressions);




		return object;
	}

	picojson::object CompileTypeDeclaration(TypeDeclarationPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"TypeDeclaration");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:id}
		if (pointer->structname)
		{
			picojson::object structname;

			structname = CompileStructName(pointer->structname);

			object[L"structname"] = picojson::value(structname);
		}
		// {:count=>3, :type=>:id}

		picojson::array typeparameters;

		for(unsigned i=0; i<pointer->typeparameters.size(); i++)
		{
			typeparameters.push_back(picojson::value(CompileTypeParameters(pointer->typeparameters[i])));
		}

		object[L"typeparameters"] = picojson::value(typeparameters);




		return object;
	}

	picojson::object CompileTypeParameters(TypeParametersPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"TypeParameters");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>3, :type=>:id}

		picojson::array typevariables;

		for(unsigned i=0; i<pointer->typevariables.size(); i++)
		{
			typevariables.push_back(picojson::value(CompileTypeVariable(pointer->typevariables[i])));
		}

		object[L"typevariables"] = picojson::value(typevariables);




		return object;
	}

	picojson::object CompileNumberLit(NumberLitPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"NumberLit");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:id}
		if (pointer->numberliteral)
		{
			picojson::object numberliteral;

			numberliteral = CompileNumberLiteral(pointer->numberliteral);

			object[L"numberliteral"] = picojson::value(numberliteral);
		}




		return object;
	}

	picojson::object CompileExpression(ExpressionPtr pointer)
	{
		picojson::object object;

		// variation
		object[L"_type"] = picojson::value(L"Expression");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		picojson::object content;
		switch(pointer->get_expression_type())
		{
			case NUMBERLIT_EXPRESSION:
			{
				content = CompileNumberLit(std::dynamic_pointer_cast<NumberLit>(pointer));
				break;
			}

		}

		object[L"_content"] = picojson::value(content);

		return object;
	}

	picojson::object CompileAttributeParam(AttributeParamPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"AttributeParam");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:id}
		if (pointer->membername)
		{
			picojson::object membername;

			membername = CompileMemberName(pointer->membername);

			object[L"membername"] = picojson::value(membername);
		}
		// {:count=>1, :type=>:id}
		if (pointer->expression)
		{
			picojson::object expression;

			expression = CompileExpression(pointer->expression);

			object[L"expression"] = picojson::value(expression);
		}




		return object;
	}

	picojson::object CompileAttributeParamList(AttributeParamListPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"AttributeParamList");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>3, :type=>:id}

		picojson::array attributeparams;

		for(unsigned i=0; i<pointer->attributeparams.size(); i++)
		{
			attributeparams.push_back(picojson::value(CompileAttributeParam(pointer->attributeparams[i])));
		}

		object[L"attributeparams"] = picojson::value(attributeparams);




		return object;
	}

	picojson::object CompileAttribute(AttributePtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"Attribute");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:id}
		if (pointer->typeexpression)
		{
			picojson::object typeexpression;

			typeexpression = CompileTypeExpression(pointer->typeexpression);

			object[L"typeexpression"] = picojson::value(typeexpression);
		}
		// {:count=>3, :type=>:id}

		picojson::array attributeparamlists;

		for(unsigned i=0; i<pointer->attributeparamlists.size(); i++)
		{
			attributeparamlists.push_back(picojson::value(CompileAttributeParamList(pointer->attributeparamlists[i])));
		}

		object[L"attributeparamlists"] = picojson::value(attributeparamlists);




		return object;
	}

	picojson::object CompileMember(MemberPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"Member");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>3, :type=>:id}

		picojson::array attributes;

		for(unsigned i=0; i<pointer->attributes.size(); i++)
		{
			attributes.push_back(picojson::value(CompileAttribute(pointer->attributes[i])));
		}

		object[L"attributes"] = picojson::value(attributes);
		// {:count=>1, :type=>:id}
		if (pointer->typeidentifier)
		{
			picojson::object typeidentifier;

			typeidentifier = CompileTypeIdentifier(pointer->typeidentifier);

			object[L"typeidentifier"] = picojson::value(typeidentifier);
		}
		// {:count=>3, :type=>:id}

		picojson::array membernames;

		for(unsigned i=0; i<pointer->membernames.size(); i++)
		{
			membernames.push_back(picojson::value(CompileMemberName(pointer->membernames[i])));
		}

		object[L"membernames"] = picojson::value(membernames);




		return object;
	}

	picojson::object CompileFormat(FormatPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"Format");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>3, :type=>:id}

		picojson::array attributes;

		for(unsigned i=0; i<pointer->attributes.size(); i++)
		{
			attributes.push_back(picojson::value(CompileAttribute(pointer->attributes[i])));
		}

		object[L"attributes"] = picojson::value(attributes);
		// {:count=>1, :type=>:id}
		if (pointer->typedeclaration)
		{
			picojson::object typedeclaration;

			typedeclaration = CompileTypeDeclaration(pointer->typedeclaration);

			object[L"typedeclaration"] = picojson::value(typedeclaration);
		}
		// {:count=>4, :type=>:id}

		picojson::array members;

		for(unsigned i=0; i<pointer->members.size(); i++)
		{
			members.push_back(picojson::value(CompileMember(pointer->members[i])));
		}

		object[L"members"] = picojson::value(members);




		return object;
	}

	picojson::object CompileImport(ImportPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"Import");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:id}
		if (pointer->stringliteral)
		{
			picojson::object stringliteral;

			stringliteral = CompileStringLiteral(pointer->stringliteral);

			object[L"stringliteral"] = picojson::value(stringliteral);
		}




		return object;
	}

	picojson::object CompileStatement(StatementPtr pointer)
	{
		picojson::object object;

		// variation
		object[L"_type"] = picojson::value(L"Statement");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		picojson::object content;
		switch(pointer->get_statement_type())
		{
			case FORMAT_STATEMENT:
			{
				content = CompileFormat(std::dynamic_pointer_cast<Format>(pointer));
				break;
			}
			case IMPORT_STATEMENT:
			{
				content = CompileImport(std::dynamic_pointer_cast<Import>(pointer));
				break;
			}

		}

		object[L"_content"] = picojson::value(content);

		return object;
	}



	picojson::value Jsonify(S2Ptr parseResult)
	{
		return picojson::value(CompileS2(parseResult));
	}

}

