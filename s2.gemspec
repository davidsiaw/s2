# frozen_string_literal: true

lib = File.expand_path('lib', __dir__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 's2/version'

dev_dependencies = [
  ['bundler', '~> 1.14'],
  ['pry'],
  ['pry-byebug'],
  ['rake', '~> 10.0'],
  ['rake-compiler', '~> 0.9.5'],
  ['rspec', '~> 3.0'],
  ['rspec_junit_formatter'],
  ['ruco-cpp', '~> 0.4']
]

dependencies = [
  ['colorize'],
  ['optimist']
]

Gem::Specification.new do |spec|
  spec.name          = 's2'
  spec.version       = S2::VERSION
  spec.authors       = ['David Siaw']
  spec.email         = ['davidsiaw@gmail.com']

  spec.summary       = spec.description = 'Data Handling Code Generator'
  spec.homepage      = 'https://github.com/davidsiaw/s2'
  spec.license       = 'MIT'

  if spec.respond_to?(:metadata)
    spec.metadata['allowed_push_host'] = 'https://rubygems.org'
  else
    raise 'RubyGems 2.0 or newer is required to protect against ' \
      'public gem pushes.'
  end

  spec.files         = Dir['lib/**/*.rb'] +
                       Dir['bin/*'] +
                       Dir['ext/**/*'] +
                       Dir['data/**/*'] +
                       ['Rakefile']
  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
  spec.extensions = %w[ext/s2/internal/extconf.rb]

  dev_dependencies.each { |dep| spec.add_development_dependency(*dep) }
  dependencies.each { |dep| spec.add_dependency(*dep) }
end
