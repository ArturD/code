class Point
  attr_accessor :x, :y
  
  def initialize x,y
    @x = x
    @y = y
  end

  def cp o
    return @x*o.y - @y*o.x
  end

  def - o
    return Point.new @x-o.x, @y-o.y
  end

  def left a,b
    a = a - self
    b = b - self
    (a.cp b) <=> 0
  end
  def order a,b
    a = a - self
    b = b - self
    return a.sector <=> b.sector if a.sector != b.sector
    return (a.cp b) <=> 0
  end

  def sector
    return 0 if @x == 0 && @y == 0
    return 1 if @x > 0 || (@x==0 && @y >= 0)
    return 2
  end
end
class Star < Point
  attr_accessor :v
  def initialize x,y,v
    super(x,y)
    @v = v
  end

  def to_s
    "(#{@x},#{@y}:#{@z})"
  end
end

n = gets.to_i
stars = []
n.times do
  (x,y,z) = gets.split(" ").map {|a| a.to_i}
  stars.push Star.new x,y,z
end
$total = stars.map {|x| x.v}.inject(:+)
half = ($total + 1) / 2

#puts $total
$bv = 0
def relax x
  x = [x,$total-x].min
  $bv = x if x > $bv
end
if n == 1
  $bv = 0
elsif n == 2
  $bv = stars.map {|x| x.v}.min
else
  for s in stars
    ss = stars.sort {|a,b| s.order a,b }
    s0 = ss[0]
    ss = ss[1..(n-1)] * 3
    j = 0
    sum = 0
    for i in 0..(n-1)
      while j < i+1
        sum += ss[j].v
        j+=1
      end
      while j-i < n-1
        break if s0.left(ss[i], ss[j]) > 0
        sum += ss[j].v
        j += 1
      end
      #puts "  #{sum}"
      relax sum
      relax sum+s0.v
      sum -= ss[i].v
    end
  end
end
puts "#{$bv}"
