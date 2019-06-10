# frozen_string_literal: true

require 'bundler/setup'
require 's2'
require 's2/s2_parse'
require 'json'
require 'open3'

RSpec.configure do |config|
  # Enable flags like --only-failures and --next-failure
  config.example_status_persistence_file_path = '.rspec_status'

  config.expect_with :rspec do |c|
    c.syntax = :expect
  end
end
