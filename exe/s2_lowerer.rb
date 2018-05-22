require "yaml"
require "json"
require "s2/display"

ast = JSON.parse ARGF.first

INTRINSIC_STRUCTURES = {
	"Uint8" => {},
	"Uint16" => {},
	"Uint32" => {},
	"Uint64" => {},
	"Int8" => {},
	"Int16" => {},
	"Int32" => {},
	"Int64" => {},
	"Float32" => {},
	"Float64" => {}
}

generic_structures = {

}

output = {
	"file" => ast["_file"],
	"structures" => {}
}

def deep_copy(o)
  Marshal.load(Marshal.dump(o))
end

def rewrite_type_expression(typeidentifier, type_arguments, type_variables, output, generic_structures)

	if typeidentifier["typevariable"]

		typevar_obj = typeidentifier["typevariable"]
		typeidentifier["structname"] = typevar_obj
		typevar = typevar_obj["_token"]

		if type_variables.has_key?(typevar)
			typeidentifier["structname"]["_token"] = construct_struct(type_arguments[type_variables[typevar]], output, generic_structures)[:mangled]

		else

			S2::Display.error(typevar_obj, 
				error: "Unknown type variable #{typevar}", 
				extra: "type variables in this context: #{type_variables.map{|k,v| k}.join(",")}")

			exit(1)
		end
	end

	if typeidentifier["typeparameterarguments"].length == 1

		typeidentifier["typeparameterarguments"][0]["typeexpressions"].each do |expr|
			rewrite_type_expression(expr["_content"], type_arguments, type_variables, output, generic_structures)
		end
	end

end

def rewrite_member(member, type_arguments, type_variables, output, generic_structures)

	member = deep_copy(member)

	rewrite_type_expression(member["typeidentifier"], type_arguments, type_variables, output, generic_structures)

	member

end

def construct_struct(typeident, output, generic_structures)

	type_arguments = []
	type_variables = {}

	instance_name = typeident["structname"]["_token"]
	syntactic_name = typeident["structname"]["_token"]

	structure = generic_structures[instance_name]

	if !structure

		if INTRINSIC_STRUCTURES.has_key?(instance_name)
			return {
				mangled: instance_name,
				syntactic: syntactic_name
			}
		else			

			extra = "Please check that the type has been defined elsewhere in the file"

			(INTRINSIC_STRUCTURES.keys + generic_structures.keys).each do |key|
				if key.downcase == instance_name.downcase
					extra = "Did you mean '#{key}'?"
					break
				end
			end

			S2::Display.error(typeident, 
				error: "Unknown type '#{instance_name}'", 
				extra: extra)
			exit(1)
		end
	end

	if typeident["typeparameterarguments"] && typeident["typeparameterarguments"].length == 1

		instance_name += "Of" + 
			typeident["typeparameterarguments"][0]["typeexpressions"].map do |typeexpr|
				type_arguments << typeexpr["_content"]				

				construct_struct(typeexpr["_content"], output, generic_structures)[:mangled]
			end.join("And") 

		syntactic_name_part = typeident["typeparameterarguments"][0]["typeexpressions"].map do |typeexpr|
				
				construct_struct(typeexpr["_content"], output, generic_structures)[:syntactic]
			end.join(",") 

		syntactic_name += "<#{syntactic_name_part}>"

		structure["typedeclaration"]["typeparameters"][0]["typevariables"].each_with_index do |typevar, idx|
			type_variables[typevar["_token"]] = idx
		end
	end

	# type already instantiated
	if output["structures"].has_key?(instance_name)
		return ({
			mangled: instance_name,
			syntactic: syntactic_name
		})
	end

	output["structures"][instance_name] = {}

	thing = {
		"s2name" => syntactic_name,
		"fields" => [],
		"attributes" => []
	}

	structure["members"].each do |member|


		member["membernames"].each do |member_name_entry|

			member_name = member_name_entry["_token"]

			field = {}

			member = rewrite_member(member, type_arguments, type_variables, output, generic_structures)

			field["name"] = member_name

			field["type"] = construct_struct(member["typeidentifier"], output, generic_structures)[:mangled]

			field["attributes"] = []

			member["attributes"].each do |attr|
				attribute = {}

				attribute["id"] = construct_struct(attr["typeexpression"]["_content"], output, generic_structures)[:mangled]

				field["attributes"] << attribute
			end

			thing["fields"] << field
		end

	end

	structure["attributes"].each do |attr|
		attribute = {}

		attribute["id"] = construct_struct(attr["typeexpression"]["_content"], output, generic_structures)[:mangled]

		thing["attributes"] << attribute
	end

	output["structures"][instance_name] = thing

end

def process_structure(structure, output, generic_structures)

	construct_struct(structure["typedeclaration"], output, generic_structures)
end

#collect structures
ast["statements"].select do |statement|
	statement["_content"]["_type"] == "Structure"
end.each do |statement|
	generic_structures[statement["_content"]["typedeclaration"]["structname"]["_token"]] = statement["_content"]
end

#process concrete structures
ast["statements"].select do |statement|
	statement["_content"]["_type"] == "Structure" && 
	statement["_content"]["typedeclaration"]["typeparameters"].length == 0
end.each do |statement|
	process_structure(statement["_content"], output, generic_structures)
end


puts output.to_json
