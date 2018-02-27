
def c_type(typename)

	case typename
	when "Int8"
		"int8_t"
	when "Int16"
		"int16_t"
	when "Int32"
		"int32_t"
	when "Int64"
		"int64_t"
	when "Uint8"
		"uint8_t"
	when "Uint16"
		"uint16_t"
	when "Uint32"
		"uint32_t"
	when "Uint64"
		"uint64_t"
	when "Float32"
		"float"
	when "Float64"
		"double"
	else
		"#{typename}*"
	end
end

def error_types
	[
		"S2_NO_ERROR",
		"S2_OUT_OF_MEMORY",
		"S2_INDEX_OUT_OF_BOUNDS",
		"S2_UNEXPECTED_END_OF_FILE",
		"S2_OBJECT_IS_NULL",
		"S2_VALUE_IS_NULL",
		"S2_WRITE_FAILED",
		"S2_POINTER_IS_WRONG_TYPE",
		"S2_NULL_FILE_POINTER",
		"S2_MEMBER_VALUE_WRONG",
		"S2_INVALID_VALUE_FOR_TYPE",
		"S2_END_OF_STACK"
	]
end

def make_null_check(target, error)
<<-CHECK
	if (#{target} == NULL)
	{
		return #{error};
	}
CHECK
end

def make_function_defines(structure_name, structure, is_source:)

	function_defines = ""


	create_definition = <<-CREATE_DEFINITION

{
#{make_null_check("out_object", "S2_OBJECT_IS_NULL")}
	*out_object = calloc(1, sizeof(#{structure_name}));
	return S2_NO_ERROR;
}
	CREATE_DEFINITION

	delete_definition = <<-DELETE_DEFINITION

{
#{make_null_check("in_object", "S2_OBJECT_IS_NULL")}
	free(in_object);
	return S2_NO_ERROR;
}
	DELETE_DEFINITION

	if !is_source
		create_definition = ";"
		delete_definition = ";"
	end

	function_defines += <<-PROTOTYPES
S2Error Create#{structure_name}(#{structure_name}** out_object)#{create_definition}
S2Error Delete#{structure_name}(#{structure_name}* in_object)#{delete_definition}
	PROTOTYPES

	structure["fields"].each do |field|
		field_name = field["name"]
		field_type = c_type(field["type"])

		get_definition = <<-GET_DEFINITION

{
#{make_null_check("in_object", "S2_OBJECT_IS_NULL")}
#{make_null_check("out_value", "S2_VALUE_IS_NULL")}
	*out_value = in_object->#{field_name};
	return S2_NO_ERROR;
}
		GET_DEFINITION

		set_definition = <<-SET_DEFINITION

{
#{make_null_check("in_object", "S2_OBJECT_IS_NULL")}
	in_object->#{field_name} = in_value;
	return S2_NO_ERROR;
}
		SET_DEFINITION

		if !is_source
			get_definition = ";"
			set_definition = ";"
		end

		function_defines += <<-PROTOTYPES
S2Error Get#{structure_name}_#{field_name}(#{structure_name}* in_object, #{field_type}* out_value)#{get_definition}
S2Error Set#{structure_name}_#{field_name}(#{structure_name}* in_object, #{field_type} in_value)#{set_definition}
		PROTOTYPES
		

	end

	function_defines
end
