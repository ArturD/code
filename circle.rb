require "matrix"

$cache = {}
def pow(m, p)
  hash = "p#{m.to_a.length}_#{p}"
  puts hash
  return $cache[hash] if $cache[hash]
  r = Matrix.I m.to_a.length
  pp = m
  ex  = 1
  while p!=0
    if p.modulo(2) == 1
      r = pp*r
    end
    pp = (pp*pp).map {|x| x.modulo 1000000007}
    ex *= 2
    p/=2
  end
  puts "end"
  $cache[hash] = r
end

def mult(m, a, b, cached_only=false)
  hash = "m#{m.to_a.length}_#{a}-#{b}"
  puts hash
  return m[a] if a==b
  return $cache[hash] if $cache[hash]
  return nil if cached_only
  tmp = mult(m,a,b-1, true)
  if tmp
    r = m[b]*tmp
  else
    tmp = mult(m,a+1,b)
    r = tmp*m[a]
  end
  
  puts "end"
  $cache[hash] = r.map {|x| x.modulo 1000000007}
end

def go()
  (n,m) = gets.split(" ").map {|x| x.to_i}
  ns = gets.split(" ").map {|x| x.to_i}
  mm = []
  for i in 0..(n-1)
    mm[i] = Matrix.build(n,n) do |a,b|
      if a==b or 
        (i==a and (n+b-a+1).modulo(n) == 0) or 
        (i==a and (n+b-a-1).modulo(n) == 0)
        then 1
        else 0
        end
    end
    #puts mm[i]
  end
    sm = Vector.elements(ns)
    mmm = mult(mm,0,n-1)
    puts mmmt
    for i in 0..(n-1)
      u = [n-1,i+m-1].min
      m0 = Matrix.I n
      if i<=u
        m0 = mult(mm,i,u)
      end
      nn = m - (u+1 - i)
      m1 = pow(mmm,(nn/n)) or Matrix.I n
      nn = nn.modulo(n)
      #puts nn
      if nn > 0
        m2 = mult(mm,0,nn-1) or Matrix.I n
        #puts nn
      else
        m2 = Matrix.I n
      end
     
      ssm = m2*m1*m0
      #puts "  - -- "
      #puts "#{m0}"
      #puts "#{m1}"
      #puts "#{m2}"
      #puts " ==== "
      ssm = (ssm*sm).map {|x| x.modulo 1000000007}
      #puts "#{ssm}"
      xx = (0..n-1).map {|x| ssm[x]}.to_a
      puts "#{xx.join(" ")}"
    end
    puts
end

t = gets.to_i
t.times do
  go()
end
