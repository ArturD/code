def totals_for firends, max_cost
  total_cost = 0
  total_bought = 0
  for f in firends
    x1 = (-1+Math.sqrt(1+8*max_cost.to_f/f))/2
    x1 = x1.floor.to_i
    cost = x1*(x1+1)/2*f
    total_bought += x1
    total_cost += cost
    #assert
    $stderr.puts "error  #{x1}" if cost > max_cost
    $stderr.puts "error2 #{x1}" if cost + (x1+1)*f <= max_cost
  end
  puts " totals #{max_cost} -> #{[total_cost, total_bought]}"
  [total_cost, total_bought]
end

def bsearch a, b, fun
  return a if a == b
  puts "#{a} #{b}"
  piv = (a+b)/2
  return bsearch piv+1, b, fun if not fun.call(piv)
  return bsearch a, piv, fun
end

(n,k) = gets.split(" ").map {|x| x.to_i }
friends = gets.split(" ").map {|x| x.to_i }
ub = friends.min * k * (k+1)/2 +1
c = bsearch 1, ub, lambda { |tested_cost|
  bought = totals_for(friends,tested_cost)[1]
  bought >= k
}

cost= totals_for(friends, c)[0]
puts "#{cost}"
