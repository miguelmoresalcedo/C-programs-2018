#! /urs/bin/env ruby
# Example of a class

name = [ "Sussane", "Cindy", "Stacy", "Caroline", "Claire", "Chloe", "Sthepanie", "Lucy" ]
staff = []

7.times { | | staff.push Steward.new ( name[x] )  }

puts "We have #{Steward.count} stewards."

staff.each { |s| s.greet "Txema" }

