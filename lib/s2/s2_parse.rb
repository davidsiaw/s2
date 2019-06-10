# frozen_string_literal: true

require 's2/s2_parse/internal'

module S2
  # Parser module, wraps the native functions with some error handling
  module S2Parse
    def self.runtest(hello)
      s2_parse_test(hello)
    end

    def self.compile_to_ast(string)
      return s2_parse_compile_to_ast(string) if string.is_a? String

      raise 'Invalid type given. This method only accepts strings'
    end
  end
end
