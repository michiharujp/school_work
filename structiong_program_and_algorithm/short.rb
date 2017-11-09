s = []
gets.chomp.split('').each_with_index{|c,i| (c == '(') ? (s.push i+1) : (puts "[#{s.pop},#{i+1}]")}
