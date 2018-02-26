#include "parse_s2.hpp"
#include "sstream"

picojson::value JsonifyParserError(S2::ParserException e)
{
	picojson::object error;
	error[L"_error"] = picojson::value(e.GetMessage());
	error[L"_line"] = picojson::value((double)e.LineNumber());
	error[L"_col"] = picojson::value((double)e.ColumnNumber());
	return picojson::value(error);
}

picojson::value JsonifyOtherError(std::wstring message)
{
	picojson::object error;
	error[L"_error"] = picojson::value(message);
	return picojson::value(error);
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		// Tell the user to use serialist-gen instead
		std::wcout << JsonifyOtherError(L"USAGE: s2parse <filename>").serialize() << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		auto s = S2::Parse(argv[1]);
		auto json = S2::Jsonify(s);
		std::wcout << json.serialize() << std::endl;
	}
	catch (S2::ParserException e)
	{
		std::wcout << JsonifyParserError(e).serialize() << std::endl;

		return EXIT_FAILURE;
	}
	catch (S2::FileNotFoundException e)
	{
		std::wstringstream str;
		str << "File not found: " << argv[1];
		std::wcout << JsonifyOtherError(str.str()).serialize() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
