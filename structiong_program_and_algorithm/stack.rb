inputs = gets.chomp.split("")
stack = []
inputs.each_with_index do |c, i|
  if c == '('
    stack.push i+1
  elsif c == ')'
    puts "[#{stack.pop},#{i+1}]"
  end
end
