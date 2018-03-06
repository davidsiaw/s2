require "s2/s2_parse/s2_parse"

include S2_parse
module S2_parse

	def S2_parse.runtest(hello)
		s2_parse_test(hello)
	end

	def S2_parse.compile_to_ast(string)
		if string.is_a? String
			s2_parse_compile_to_ast(string)
		else
			raise "Invalid type given. This method only accepts strings"
		end
	end

end
