require "bundler/gem_tasks"
require "rspec/core/rake_task"
require "rake/extensiontask"
require 'fileutils'

RSpec::Core::RakeTask.new(:spec)

gemspec = Gem::Specification.load('s2.gemspec')
Rake::ExtensionTask.new do |ext|
  ext.name = 's2_parse'
  ext.ext_dir = 'ext/s2/s2_parse'
  ext.lib_dir = 'lib/s2/s2_parse'
  ext.gem_spec = gemspec
  ext.source_pattern = "*.{c,cpp}" 
end

task :regen_parser do
  sh %{cd ext/s2/s2_parse && bundle exec ruco s2.ruco && rm *.old}
end

task :default => [:test]
task :test => [:regen_parser, :compile, :spec]
