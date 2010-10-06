require 'open-uri'
require 'nokogiri'

unless ARGV.length > 0
  puts "usaga: ruby get_sample_code.rb (urls)"
  exit 1
end

ARGV.each{ |url|
  a, b = *url.scan(/(\d)(\d)/)[0]
  name = "#{a}-#{b}.c"
  puts name
  s = Nokogiri open(url)
  open(name, "w"){ |f|
    f.write s.at('pre').text
  }
}
