module S2
  module Display

    def self.error(filename, source, err)
      puts "#{filename}:#{err["_line"]}:#{err["_col"]} error: #{err["_error"]}"
      puts source.split("\n")[err["_line"] - 1]
      puts " " * (err["_col"] - 1) + "^"
      puts " " * (err["_col"] - 1) + "#{err["_explain"]}" if err["_explain"]
    end

  end
end
