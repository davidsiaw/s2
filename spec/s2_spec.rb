# frozen_string_literal: true

require 'spec_helper'

RSpec.describe S2 do
  it 'has a version number' do
    expect(S2::VERSION).not_to be nil
  end

  it 'Extension can be called' do
    expect(S2::S2Parse.runtest('meow')).to eq('test-meow')
  end

  it 'Only accepts strings' do
    expect { S2::S2Parse.compile_to_ast(nil) }.to raise_error
  end

  it 'Can parse simplest file' do
    JSON.parse(S2::S2Parse.compile_to_ast(''))
  end

  it 'Can throw errors' do
    source = 'struct abcd'
    output = JSON.parse(S2::S2Parse.compile_to_ast(source))
    expect(output['_error']).not_to be nil
  end
end
