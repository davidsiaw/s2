require 'colorize'

module S2
  module Display

    def self.error(filename, source, err)
      line = source.split("\n")
      STDERR.puts "#{filename}:#{err["_line"]}:#{err["_col"]} #{"error".colorize(:red)}: #{err["_error"]}"
      STDERR.puts line[err["_line"] - 1]

      STDERR.puts " " * (err["_col"] - 1) + "^".colorize(:green)
      STDERR.puts " " * (err["_col"] - 1) + "#{err["_explain"]}" if err["_explain"]

      if err["_type"] == "parser"
      	STDERR.puts ""
      	STDERR.puts "Please refer to https://davidsiaw.github.com/s2/syntax for correct syntax"
      end
    end

  end
end
