# frozen_string_literal: true

require 'colorize'

module S2
  # The class that displays nice errors
  class ErrorDisplayer
    LENGTH_OF_TAB = 4

    attr_reader :info
    attr_accessor :explain, :extra

    def initialize(info)
      @info = info
    end

    def error
      info['_error']
    end

    def filename
      info['_file']
    end

    def line
      info['_line']
    end

    def col
      info['_col']
    end

    def source
      @source ||= File.read(filename)
    end

    def source_lines
      source.split("\n")
    end

    def source_line
      source_lines[line - 1]
    end

    def tab
      ' ' * LENGTH_OF_TAB
    end

    def source_pointer_indent
      ' ' * source_line[0...col - 1].gsub("\t", tab).length
    end

    def error_title_outputs
      "#{filename}:#{line}:#{col} #{'error'.colorize(:red)}: #{error}"
    end

    def source_view_outputs
      return unless filename

      [
        source_line.gsub("\t", tab),
        "#{source_pointer_indent}#{'^'.colorize(:green)}"
      ]
    end

    def explain_outputs
      "#{source_pointer_indent}#{explain}" if explain
    end

    def extra_outputs
      extra
    end

    def output
      [
        error_title_outputs,
        source_view_outputs,
        explain_outputs,
        extra_outputs
      ].flatten.select { |x| x }.join("\n")
    end
  end
end
