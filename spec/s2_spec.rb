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

def run_command_that_shouldnt_fail(command, &block)
  Open3.popen3(command) do |stdin, stdout, stderr, wait_thr|
    if wait_thr.value.exitstatus != 0
      puts "---"
      puts stderr.read
      puts "---"
    end
    expect(wait_thr.value.exitstatus).to eq(0)
    yield stdin, stdout, stderr, wait_thr if block
  end
end

RSpec.describe "s2c" do

  it 'Can be executed' do
    stdin, stdout, stderr, wait_thr = Open3.popen3("exe/s2c")
  end

  test_result_spec = /\/(?<resspec>ok|err)_[a-z0-9_]+\.s2$/

  Dir["spec/examples/*/**.s2"].each do |filename|

    artifact_dir = ".test_artifacts"
    FileUtils.mkdir_p(artifact_dir)

    testname = filename.sub(/^spec\/examples\//, "")
    m = test_result_spec.match(testname)
    if m[:resspec] == "ok"
      stage1testname = testname + " should transpile"
      stage2testname = testname + " should compile"

      basename = File.basename(filename, File.extname(filename))
      header_file = "#{artifact_dir}/#{basename}.h"
      source_file = "#{artifact_dir}/#{basename}.c"
      main_file = "#{artifact_dir}/#{basename}_main.c"
      executable_file = "#{artifact_dir}/#{basename}"

      it stage1testname do
        run_command_that_shouldnt_fail("exe/s2c h #{filename}")
      end

      it stage2testname do

        run_command_that_shouldnt_fail("exe/s2c h #{filename}") do |stdin, stdout, stderr, wait_thr|
          File.write(header_file, stdout.read)
        end

        run_command_that_shouldnt_fail("exe/s2c c #{filename}") do |stdin, stdout, stderr, wait_thr|
          File.write(source_file, stdout.read)
        end

        run_command_that_shouldnt_fail("exe/s2c ctest #{filename}") do |stdin, stdout, stderr, wait_thr|
          File.write(main_file, stdout.read)
        end

        cc = ENV["CC"] || "gcc"

        run_command_that_shouldnt_fail("#{cc} -ansi -pedantic-errors -Wall -g -Werror #{main_file} #{source_file} -o #{executable_file}") do
          |stdin, stdout, stderr, _|
          File.write("#{executable_file}.compile.out", stdout.read)
          File.write("#{executable_file}.compile.err", stderr.read)
        end

        run_command_that_shouldnt_fail(executable_file) do
          |stdin, stdout, stderr, _|
          File.write("#{executable_file}.run.out", stdout.read)
          File.write("#{executable_file}.run.err", stderr.read)
        end

      end

    else
      testname += " should fail transpilation"

      it testname do
        Open3.popen3("exe/s2c h #{filename}") do |stdin, stdout, stderr, wait_thr|
          expect(wait_thr.value.exitstatus).not_to eq 0
        end
      end
    end

  end

end
