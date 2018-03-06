require "yaml"
require "json"
require "s2/internal/c"

struct = YAML.load_file ARGV[0]

include_name = ARGV[0].sub(/\.yml$/, ".h")

structure_defines = ""
function_defines = ""

struct["structures"].each do |structure_name, structure|

	member_defines = ""

	structure["fields"].each do |field|

		field_name = field["name"]
		field_type = c_type(field["type"])

		member_defines += <<-MEMBER
	#{field_type} #{field_name};
		MEMBER

	end

	structure_defines += <<-STRUCTURE
struct _tag_#{structure_name}
{
#{member_defines}};
	STRUCTURE

	function_defines += make_function_defines(structure_name, structure, is_source: true)

end

puts <<-SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "#{include_name}"

#{structure_defines}

#{function_defines}
SOURCE
