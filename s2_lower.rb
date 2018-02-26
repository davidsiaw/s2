require "yaml"
require "json"

ast = JSON.parse File.read(ARGV[0])

File.write("#{ARGV[0]}.yml", ast.to_yaml)

output = {
	"structures" => {}
}

def process_structure(structure, output)
	thing = {
		"fields" => []
	}
	structure["members"].each do |member|
		field = {}

		field["name"] = member["membername"]["_token"]
		field["type"] = member["structname"]["_token"]
		field["is_array"] = member["arrayannotations"].length != 0

		thing["fields"] << field
	end
	output["structures"][structure["structname"]["_token"]] = thing
end

ast["statements"].each do |statement|
	if statement["_content"]["_type"] == "Structure"
		process_structure(statement["_content"], output)
	end
end

puts output.to_yaml
