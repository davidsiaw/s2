# frozen_string_literal: true

require 'bundler/gem_tasks'
require 'rspec/core/rake_task'
require 'rake/extensiontask'
require 'fileutils'

RSpec::Core::RakeTask.new(:spec)

gemspec = Gem::Specification.load('s2.gemspec')
Rake::ExtensionTask.new do |ext|
  ext.name = 'internal'
  ext.ext_dir = 'ext/s2/internal'
  ext.lib_dir = 'lib/s2/s2_parse'
  ext.gem_spec = gemspec
  ext.source_pattern = '*.{c,cpp}'
end

task :regen_parser do
  sh %(cd ext/s2/internal && bundle exec ruco s2.ruco)
end

task default: [:test]
task test: %i[regen_parser compile spec]
