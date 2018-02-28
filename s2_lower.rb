require "yaml"
require "json"

ast = JSON.parse File.read(ARGV[0])

File.write("#{ARGV[0]}.yml", ast.to_yaml)

generic_structures = {

}

output = {
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
			typeidentifier["structname"]["_token"] = instantiate_type(type_arguments[type_variables[typevar]], output, generic_structures)
		else
			STDERR.puts "Unknown type variable #{typevar} at line #{typevar_obj["_line"]}"
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

	# type already instantiated
	if output["structures"].has_key?(instance_name)
		return instance_name
	end

	structure = generic_structures[typeident["structname"]["_token"]]

	if typeident["typeparameterarguments"]
		instance_name += "Of" + 
			typeident["typeparameterarguments"][0]["typeexpressions"].map do |typeexpr|
				type_arguments << typeexpr["_content"]				

				instantiate_type(typeexpr["_content"], output, generic_structures)
			end.join("And") 

		structure["typedeclaration"]["typeparameters"][0]["typevariables"].each_with_index do |typevar, idx|
			type_variables[typevar["_token"]] = idx
		end
	end

	thing = {
		"fields" => [],
		"attributes" => []
	}

	structure["members"].each do |member|
		field = {}

		member = rewrite_member(member, type_arguments, type_variables, output, generic_structures)

		field["name"] = member["membername"]["_token"]

		field["type"] = instantiate_type(member["typeidentifier"], output, generic_structures)

		thing["fields"] << field
	end

	structure["attributes"].each do |attr|
		attribute = {}

		attribute["id"] = instantiate_type(attr["typeexpression"]["_content"], output, generic_structures)

		thing["attributes"] << attribute
	end

	output["structures"][instance_name] = thing

	instance_name
end

def instantiate_type(typeident, output, generic_structures)

	if typeident["typeparameterarguments"].length == 1
		
		construct_struct(typeident, output, generic_structures)
	else
		typeident["structname"]["_token"]
	end
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


puts output.to_yaml
