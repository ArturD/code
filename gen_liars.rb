n = 5
m = 5
puts "#{n} #{m}"
r = Random.new
m.times do
  xa = r.rand(1..n)
  xb = r.rand(1..n)
  a= [xa,xb].min
  b= [xa,xb].max
  c= r.rand 0..(b-a+1)

  puts "#{a} #{b} #{c}"
end
