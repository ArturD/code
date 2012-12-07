
n = (ARGV[0] || "3").to_i
m = (ARGV[1] || "64").to_i
puts 1
puts n
n.times do
  print "#{Random.new.rand(1..m)} "
end
puts
