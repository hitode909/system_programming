require 'open-uri'
require 'cgi'

unless ARGV.length > 0
  puts "usaga: ruby get_sample_code.rb (urls)"
  exit 1
end

ARGV.each{ |url|
  name = url.split('/').last
  name.gsub!('html', 'c')
  puts name
  s = open(url).read.scan(/<pre>(.*)<\/pre>/m)[0][0]
  open(name, "w"){ |f|
    f.write CGI.unescapeHTML(s)
  }
}
