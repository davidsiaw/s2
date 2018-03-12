require "yaml"
require "json"
require "s2/internal/c"

struct = JSON.parse ARGF.first

include_name = File.basename(struct["file"]).sub(/\.s2$/, ".h")

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
