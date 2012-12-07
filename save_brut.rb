def diff a,b
  d = 0
  for i in 0..(b.length-1)
    d+= 1 if a[i] != b[i]
  end
  #puts "#{a} #{b} #{d}"
  d
end

t=gets.to_i
t.times do
  a=gets.strip
  b=gets.strip
  gets
  for i in 0..(a.length)
    x = a[i..(i+b.length-1)]
    if x.length == b.length
      d = diff x,b
      if d<=1
        print "#{i} "
      end
    end
  end
  puts
end
