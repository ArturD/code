t = gets # expect 1
$n = gets.to_i
$ns = gets.split(" ").map {|x| x.to_i}
$dp = []
$inf = 10000000
def test c, u, xor
  #puts "#{c} #{u} #{xor}"
  return true if xor == 0
  return false if c == $n
  cur = $inf
  for i in 0..(u)
    x2 = xor ^ $ns[c] ^ ($ns[c] + i)
    if test c+1, u-i, x2
      #puts " use #{i}"
      return true 
    end
  end
  return false
end

xor=$ns.inject(:^)
i = 0
while true
  ok = test 0, i, xor
  if ok
    puts i
    break
  end
  i+=1
end
