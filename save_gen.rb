t = 20
n = 10
m = 4
puts t
r = Random.new
letters = ('a'..'z').to_a
t.times do
  puts (1..n).map {|x| letters[r.rand(0..3)]}.join
  puts (1..m).map {|x| letters[r.rand(0..3)]}.join
  puts
end
