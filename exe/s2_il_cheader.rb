require "yaml"
require "json"
require "s2/internal/c"

struct = JSON.parse ARGF.first

define_name = File.basename(struct["file"]).sub(/\.s2$/, "").gsub(/[^0-9a-z]+/, "_").upcase
header_define = "_#{define_name}_H_"

structure_defines = ""
function_defines = ""


struct["structures"].each do |structure_name, structure|

	structure_defines += <<-STRUCTURE
typedef struct _tag_#{structure_name} #{structure_name};
	STRUCTURE

	function_defines += make_function_defines(structure_name, structure, is_source: false)

end

s2runtime = <<-RUNTIME

#ifndef S2_RUNTIME
#define S2_RUNTIME
typedef enum
{
	#{error_types.join(",\n\t")}
} S2Error;

#endif /* S2_RUNTIME */

RUNTIME

puts <<-HEADER
#ifndef #{header_define}
#define #{header_define}

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#{s2runtime}

#{structure_defines}

#{function_defines}

#ifdef __cplusplus
}
#endif

#endif /* #{header_define} */
HEADER
