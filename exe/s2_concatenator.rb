require "yaml"
require "json"
require "s2/s2_parse"
require "s2/display"

def rewrite_object_with_filename(object, file)
	if object.is_a?(Hash) && object.has_key?("_col") && object.has_key?("_line")
		object["_file"] = file

		object.keys.each do |key|
			object[key] = rewrite_object_with_filename(object[key], file)
		end
	elsif object.is_a?(Array)
		object.each do |item|
			rewrite_object_with_filename(item, file)
		end
	end

	object
end

concatenated_ast = {}

def concatenate(file, concatenated_ast)

	contents = File.read(file)
	ast_str = S2_parse.compile_to_ast(contents)
	ast = JSON.parse(ast_str)

	file_fullname = File.expand_path(file)

	if ast["_error"]
		S2::Display.error(file_fullname, contents, ast)
		exit(1)
	end

	File.write("#{file}.precon.yml", ast.to_yaml)

 	if !concatenated_ast.has_key?(:_col)
 		concatenated_ast[:_files] = {}
 		concatenated_ast[:_col] = ast["_col"]
 		concatenated_ast[:_line] = ast["_line"]
 		concatenated_ast[:_type] = ast["_type"]
 		concatenated_ast[:_file] = file_fullname
 		concatenated_ast[:statements] = []
 	end

	if concatenated_ast[:_files].has_key?(file_fullname)
		return
	end

	concatenated_ast[:_files][file_fullname] = true

	ast["statements"].each do |statement|
		if statement["_content"]["_type"] == "Import"
			child_file = statement["_content"]["stringliteral"]["_token"].sub(/\A"/, "").sub(/"\Z/, "")

			if !File.exist?(child_file)
				S2::Display.error(file_fullname, contents, {
					"_col" => statement["_content"]["stringliteral"]["_col"],
					"_line" => statement["_content"]["stringliteral"]["_line"],
					"_error" => "File not found",
					"_explain" => "Attempted to load #{File.expand_path(child_file)}",
					"_type" => "import"
				})
				exit(1)
			end

			concatenate(child_file, concatenated_ast)
		else
			concatenated_ast[:statements] << rewrite_object_with_filename(statement, file_fullname)
		end
	end

end

concatenate(ARGV[0], concatenated_ast)

puts concatenated_ast.to_json
