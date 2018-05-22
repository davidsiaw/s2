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
    source = "struct abcd"
    output = JSON.parse(S2_parse.compile_to_ast(source))
    expect(output["_error"]).not_to be nil
  end

end

RSpec.describe "s2c" do

  it 'Can be executed' do
    stdin, stdout, stderr, wait_thr = Open3.popen3("exe/s2c")
  end

  test_result_spec = /\/(?<resspec>ok|err)_[a-z0-9_]+\.s2$/

  Dir["spec/examples/*/**.s2"].each do |filename|
    testname = filename.sub(/^spec\/examples\//, "")
    m = test_result_spec.match(testname)
    if m[:resspec] == "ok"
      testname += " should pass"

      it testname do
        stdin, stdout, stderr, wait_thr = Open3.popen3("exe/s2c #{filename} h")
        if wait_thr.value.exitstatus != 0
          puts "---"
          puts stderr.read
          puts "---"
        end
        expect(wait_thr.value.exitstatus).to eq(0)
        stdin.close
        stdout.close
        stderr.close
      end
    else
      testname += " should fail"

      it testname do
        stdin, stdout, stderr, wait_thr = Open3.popen3("exe/s2c #{filename} h")
        expect(wait_thr.value.exitstatus).not_to eq 0
        stdin.close
        stdout.close
        stderr.close
      end
    end

  end

end
