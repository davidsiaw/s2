require "yaml"
require "json"
require "s2/internal/c"

def fail_if(expr, i, test_name)
	<<-CHECK
	if (#{expr})
	{
		printf("[FAIL] Test#{test_name} (#{i+1})\\n");
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
#{fail_exprs.each_with_index.map{|x,i|fail_if(x, i, test_name)}.join("\n")}
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

	test(test_info, "CreateNullPointer#{structure_name}", [
		"err != S2_OBJECT_IS_NULL"
	], <<-SCRIPT)
	S2Error err = Create#{structure_name}(NULL);
	SCRIPT

	structure["fields"].each do |field|

		field_name = field["name"]
		field_type = c_type(field["type"])


		test(test_info, "Get#{structure_name}_#{field_name}", [
			"err != S2_NO_ERROR"
		], <<-SCRIPT)
	#{field_type} value;
	S2Error err = Get#{structure_name}_#{field_name}(object_#{structure_name}, &value);
			SCRIPT

		test(test_info, "Get#{structure_name}WithNullObject_#{field_name}", [
			"err != S2_OBJECT_IS_NULL"
		], <<-SCRIPT)
	#{field_type} value;
	S2Error err = Get#{structure_name}_#{field_name}(NULL, &value);
			SCRIPT

		test(test_info, "Get#{structure_name}WithNullValue_#{field_name}", [
			"err != S2_VALUE_IS_NULL"
		], <<-SCRIPT)
	S2Error err = Get#{structure_name}_#{field_name}(object_#{structure_name}, NULL);
			SCRIPT

		test_value_create = <<-TESTVALUE
	S2Error err0 = S2_NO_ERROR;
	#{field_type} value = 42;
		TESTVALUE

		test_value_delete = ""

		if field_type.end_with?("*")

			if struct["structures"].has_key?(field["type"])
				test_value_create = <<-TESTVALUE
	#{field_type} value;
	S2Error err0 = Create#{field["type"]}(&value);
				TESTVALUE

				test_value_delete = <<-TESTVALUE
	Delete#{field["type"]}(value);
				TESTVALUE
			else

			end

		
		end

		test(test_info, "Set#{structure_name}_#{field_name}", [
			"err0 != S2_NO_ERROR",
			"err1 != S2_NO_ERROR"
		], <<-SCRIPT)
#{test_value_create}
	S2Error err1 = Set#{structure_name}_#{field_name}(object_#{structure_name}, value);
#{test_value_delete}
		SCRIPT

		test(test_info, "Set#{structure_name}WithNullObject_#{field_name}", [
			"err0 != S2_NO_ERROR",
			"err1 != S2_OBJECT_IS_NULL"
		], <<-SCRIPT)
#{test_value_create}
	S2Error err1 = Set#{structure_name}_#{field_name}(NULL, value);
#{test_value_delete}
			SCRIPT

		test(test_info, "SetAndGet#{structure_name}_#{field_name}", [
			"err0 != S2_NO_ERROR",
			"err1 != S2_NO_ERROR",
			"err2 != S2_NO_ERROR",
			"gotten_value != value"
		], <<-SCRIPT)
#{test_value_create}
	#{field_type} gotten_value;
	S2Error err1 = Set#{structure_name}_#{field_name}(object_#{structure_name}, value);
	S2Error err2 = Get#{structure_name}_#{field_name}(object_#{structure_name}, &gotten_value);
#{test_value_delete}
		SCRIPT

	end

	test(test_info, "Delete#{structure_name}", [
		"err != S2_NO_ERROR"
	], <<-SCRIPT)
	S2Error err = Delete#{structure_name}(object_#{structure_name});
	SCRIPT

	test(test_info, "DeleteNullPointer#{structure_name}", [
		"err != S2_OBJECT_IS_NULL"
	], <<-SCRIPT)
	S2Error err = Delete#{structure_name}(NULL);
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
