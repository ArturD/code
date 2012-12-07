require "set"

$gen_cache = [[], []]
$get_cache = [0,0]

def gen(a)
  return $gen_cache[a] if $gen_cache[a] != nil

  total = []
  for i in 1..(a-1)
    gi = gen(a-i) + [Set.new([a-i])]
    gi.reject! {|s| s.any? {|x| x<=i} }
    gi.map! {|s| s.clone.add(i) }
    total += gi
  end
  $gen_cache[a] = total
end

def get(a)
  return $get_cache[a] if $get_cache[a] != nil
  sets = gen(a)
  legal = []
  for s in sets
    state = s.map {|x| get(x)}.reduce(:^)
    legal[state] = true
  end
  ret = -1
  for i in 0..a
    if legal[i] == nil
      ret = i
      break
    end
  end
  $get_cache[a]= ret
end

#arr = (1..51).map {|x| get(x)}.to_a
#puts("#{arr}")

tab = [nil ,0, 0, 1, 0, 2, 3, 4, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47]

t = gets.to_i
t.times do
  n = gets.to_i
  l = gets.split(" ").map {|x| x.to_i}
  xor = l.map {|x| tab[x]}.reduce(:^)
  puts "BOB" if xor == 0
  puts "ALICE" if xor != 0
end
