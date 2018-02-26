require "yaml"
require "json"
require "./c"

struct = YAML.load_file ARGV[0]

define_name = ARGV[0].sub(/\.yml$/, "").gsub(/[^0-9a-z]+/, "_").upcase
header_define = "_#{define_name}_H_"

structure_defines = ""
function_defines = ""


struct["structures"].each do |structure_name, structure|

	structure_defines += <<-STRUCTURE
typedef struct _tag_#{structure_name} #{structure_name};
	STRUCTURE

	function_defines += make_function_defines(structure_name, structure, is_source: false)

end

puts <<-HEADER
#ifndef #{header_define}
#define #{header_define}

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
	#{error_types.join(",\n\t")}
} S2Error;

#{structure_defines}

#{function_defines}

#ifdef __cplusplus
}
#endif

#endif /* #{header_define} */
HEADER
