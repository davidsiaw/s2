require 'colorize'

module S2
  module Display

    def self.error(info, filename:nil, error:nil, explain:nil, extra:nil)

      if !error
        error = info["_error"]
      end
      if !filename
        filename = info["_file"]
      end
      if !explain
        explain = info["_explain"]
      end
      if !extra
        extra = info["_extra"]
      end
      
      STDERR.puts "#{filename}:#{info["_line"]}:#{info["_col"]} #{"error".colorize(:red)}: #{error}"

      if filename
        source = File.read(filename).gsub("\t", " " * 4)
        line = source.split("\n")

        STDERR.puts line[info["_line"] - 1]

        STDERR.puts " " * (info["_col"] - 1) + "^".colorize(:green)
        STDERR.puts " " * (info["_col"] - 1) + "#{explain}" if explain
      end

      if extra
        STDERR.puts ""
        STDERR.puts "#{extra}"
      end
    end

  end
end
