def dynamic_resolve p, pow, x
  #puts " compute #{p}, #{pow}, #{x}"
  return 0 if pow == 0
  pp1 = p**(pow-1)
  pp = pp1*p
  x1 = (x-1).modulo(pp1) + 1
  ret = dynamic_resolve(p, pow-1, x1) 
  #puts "  -- #{x}/#{pp1} #{ret}"
  ret *= (x/pp1+1)
  ret += (pp1-x1)*(x/pp1) if pow > 1

  #puts "  ret = #{ret}"
  return ret
end
def compute n, p
  return 0 if n < p
  pow = 0
  while p**(pow+1) <= n do
    pow += 1
  end
  x = n.modulo(p**pow)+1
  result = dynamic_resolve p, pow, x
  result *= n/(p**pow) + 1
  result += n/(p**pow) * ((p**pow)-x)
end

def brut n, p
  bin = 1
  res = 0
  for k in 1..n
    bin *= n-k+1
    bin /= k
    #$stderr.puts " brut #{bin}"
    res += 1 if bin.modulo(p) == 0
  end
  res
end

tests = gets.to_i
tests.times do
  (n, p) = gets.split(" ").map {|num| num.to_i}
  result = compute n, p
  #bresult = brut n, p
  #$stderr.puts "#{result}  (brute-force: #{bresult})"
  puts "#{result}"
end

