(n, k) = gets.split(" ").map {|num| num.to_i}
nums = gets.split(" ").map {|num| num.to_i}.sort

j = 1
count = 0
for i in 0..nums.length-2
  while j < nums.length and nums[j] < nums[i]+k do j += 1 end
  count += 1 if j < nums.length and nums[j] == nums[i]+k
end

puts "#{count}"
