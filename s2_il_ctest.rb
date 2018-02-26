require "yaml"
require "json"
require "./c"

def fail_if(expr, test_name)
	<<-CHECK
	if (#{expr})
	{
		printf("[FAIL] Test#{test_name}\\n");
		fail++;
		return;
	}
	CHECK
end

def test(test_info, test_name, fail_exprs, script)
	test_info[:test_calls] += <<-CALLS
	Test#{test_name}();
	CALLS

	test_info[:test_functions] += <<-TEST
void Test#{test_name}()
{
#{script}
#{fail_exprs.map{|x|fail_if(x, test_name)}.join("\n")}
	printf("[PASS] Test#{test_name}\\n");
	pass++;
}
	TEST
end

struct = YAML.load_file ARGV[0]

include_name = ARGV[0].sub(/\.yml$/, ".h")

test_info = {
	test_declarations: "",
	test_calls: "",
	test_functions: ""
}

struct["structures"].each do |structure_name, structure|

	test_info[:test_declarations] += <<-DECLS
#{structure_name}* object_#{structure_name} = NULL;
	DECLS

	test(test_info, "Create#{structure_name}", [
		"object_#{structure_name} == NULL",
		"err != S2_NO_ERROR"
	], <<-SCRIPT)
	S2Error err = Create#{structure_name}(&object_#{structure_name});
	SCRIPT

	structure["fields"].each do |field|

		field_name = field["name"]
		field_type = c_type(field["type"])

		if field["is_array"]

			test(test_info, "Count#{structure_name}_#{field_name}", [
			], <<-SCRIPT)
			SCRIPT

			test(test_info, "GetElement#{structure_name}_#{field_name}", [
			], <<-SCRIPT)
			SCRIPT

			test(test_info, "SetElement#{structure_name}_#{field_name}", [
			], <<-SCRIPT)
			SCRIPT

		else

			test(test_info, "Get#{structure_name}_#{field_name}", [
				"err != S2_NO_ERROR"
			], <<-SCRIPT)
	#{field_type} value;
	S2Error err = Get#{structure_name}_#{field_name}(object_#{structure_name}, &value);
			SCRIPT

			test(test_info, "Set#{structure_name}_#{field_name}", [
			], <<-SCRIPT)
			SCRIPT
		end

	end

	test(test_info, "Delete#{structure_name}", [
		"err != S2_NO_ERROR"
	], <<-SCRIPT)
	S2Error err = Delete#{structure_name}(object_#{structure_name});
	SCRIPT

end

puts <<-SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "#{include_name}"

int pass = 0;
int fail = 0;
#{test_info[:test_declarations]}
#{test_info[:test_functions]}
int main()
{
	printf("[INFO] Start testing\\n");
#{test_info[:test_calls]}
	printf("[INFO] Testing Completed. Passed: %d Failed: %d\\n", pass, fail);
	return 0;
}

SOURCE
