# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 's2/version'

Gem::Specification.new do |spec|
  spec.name          = "s2"
  spec.version       = S2::VERSION
  spec.authors       = ["David Siaw"]
  spec.email         = ["davidsiaw@gmail.com"]

  spec.summary       = %q{Data Handling Code Generator}
  spec.description   = %q{S2 generates code to handle data in an uniform manner}
  spec.homepage      = "https://github.com/davidsiaw/s2"
  spec.license       = "MIT"

  # Prevent pushing this gem to RubyGems.org. To allow pushes either set the 'allowed_push_host'
  # to allow pushing to a single host or delete this section to allow pushing to any host.
  if spec.respond_to?(:metadata)
    spec.metadata['allowed_push_host'] = "https://rubygems.org"
  else
    raise "RubyGems 2.0 or newer is required to protect against " \
      "public gem pushes."
  end

  spec.files         = Dir['lib/**/*.rb'] + 
                        Dir['bin/*'] + 
                        Dir['ext/**/*'] + 
                        Dir['data/**/*'] +
                        ["Rakefile"]
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]

  spec.extensions = %w[ext/s2/s2_parse/extconf.rb]

  spec.add_development_dependency "bundler", "~> 1.14"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rake-compiler", "~> 0.9.5"
  spec.add_development_dependency "rspec", "~> 3.0"
  spec.add_development_dependency "ruco-cpp", "~> 0.4"
  spec.add_development_dependency "rspec_junit_formatter"

  spec.add_dependency "colorize"
  spec.add_dependency "trollop"
end
