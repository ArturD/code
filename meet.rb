n = gets.to_i
x=[]
y=[]
n.times do
  (a,b) = gets.split(" ").map {|x| x.to_i}
  x.push a-b
  y.push a+b
end

def dists(tab, &f)
  tab = tab.sort {|a,b| f.call(a) <=> f.call(b) }
  ret = {tab[0] => 0}
  for i in 1..(tab.length-1)
    ret[tab[i]] = ret[tab[i-1]] + i*(f.call(tab[i])-f.call(tab[i-1]))
  end
  return ret
end

a = dists (0..(n-1)) {|i| x[i]}
b = dists (0..(n-1)) {|i| -x[i]}
c = dists (0..(n-1)) {|i| y[i]}
d = dists (0..(n-1)) {|i| -y[i]}
res = (0..(n-1)).map { |i| a[i]+b[i]+c[i]+d[i] }.min / 2
puts "#{res}"
