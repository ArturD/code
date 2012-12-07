def kmp_search(s, w)  
  m = i = 0  
  slen = s.length  
  wlen = w.length
  found = [0]*slen
  t = kmp_table(w)
  puts " #{t}"
  while m+i < slen
    #puts " #{i} #{w[i]}"
    #puts "             #{m+i} #{s[m+i]}"
    #found[m+i-t[i]] = [i-t[i],m+i-t[i]].max
    if w[i] == s[m+i]
      i += 1
      found[m] = [i,found[m]].max
      if i == wlen
        puts "  #{i} #{m}"
        m += i - t[i] 
        i = [0, t[i]].max
        found[m] = [i,found[m]].max
        puts "  #{i} #{m}"
      end
    else
      #puts "#{t} #{i}"
      m += i - t[i]  
      i = [0, t[i]].max  
      #found[m] = [i,found[m]].max
    end  
  end  
  found[0..slen-1]
end  
  
def kmp_table(w)  
  pos = 2  
  cnd = 0  
  t = [-1, 0]  
  wlen = w.length  
  while pos <= wlen  
    if w[pos-1] == w[cnd]  
      cnd += 1  
      t[pos] = cnd  
      pos += 1  
    elsif cnd > 0  
      cnd = t[cnd]  
    else  
      t[pos] = 0  
      pos += 1  
    end  
  end
  t.push cnd
  t  
end

def kmp(t,p)
 n = t.length-1
 m = p.length-1
 pi = pref(p)
 ret = [0]*(n+1)
 q = -1
 for i in 0..n-1
  while q>-1 and p[q+1] != t[i]
    q=pi[q]
  end
  if p[q+1] = t[i]
    q+=1
  end
  ret[i-q] = q 
  q = pi[q]
 end
 ret
end 
def pref(p)
  m = p.length
  pi = [-1]
  k = -1
  for q in 1..m-1
    while k > -1 and p[k+1] != p[q]
      k = pi[k]
    end
    k += 1 if p[k+1] == p[q]
    pi[q] = k
  end
  return pi
end

n = gets.to_i
n.times do
  sa = gets.strip
  sb = gets.strip
  pre  = kmp_search(sa,sb)
  pre2 = kmp_search(sa.reverse, sb.reverse).reverse
  puts "#{pre}"
  puts "#{pre2}"
  a = sa.length
  b = sb.length
  for i in (0..(a-b))
    print "#{i} " if pre[i] == b || (pre[i] or 0)+(pre2[i+b-1] or 0) == b-1
  end
  puts
  gets
end
