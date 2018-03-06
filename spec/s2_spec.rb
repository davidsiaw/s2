require "spec_helper"

RSpec.describe S2 do
  it "has a version number" do
    expect(S2::VERSION).not_to be nil
  end

  it 'Extension can be called' do
    expect(S2_parse.runtest("meow")).to eq("test-meow")
  end

  it 'Only accepts strings' do
    begin
      S2_parse.compile_to_ast(nil)
      fail "needs to raise exception"
    rescue
    end
  end

  it 'Can parse simplest file' do
    JSON.parse(S2_parse.compile_to_ast(""))
  end

  it 'Can throw errors' do
    output = JSON.parse(S2_parse.compile_to_ast("struct"))
    expect(output["_error"]).not_to be nil
  end
end
