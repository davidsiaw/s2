# frozen_string_literal: true

require 'mkmf'

have_library('stdc++')
$CXXFLAGS = '-g -Wall -std=gnu++11'
create_makefile('s2_parse/internal')
