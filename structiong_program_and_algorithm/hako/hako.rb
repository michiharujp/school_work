Koma = Struct.new(:width, :height, :name, :type, :y, :x)

# 初期配置
INIT = [Koma.new(2, 2, "娘 ", 'A', 0, 1),
        Koma.new(1, 2, "父 ", 'B', 0, 0),
        Koma.new(1, 2, "母 ", 'B', 0, 3),
        Koma.new(1, 2, "男1", 'B', 3, 0),
        Koma.new(1, 2, "男2", 'B', 3, 3),
        Koma.new(2, 1, "番 ", 'C', 3, 1),
        Koma.new(1, 1, "僧1", 'D', 2, 0),
        Koma.new(1, 1, "僧2", 'D', 2, 1),
        Koma.new(1, 1, "僧3", 'D', 2, 2),
        Koma.new(1, 1, "僧4", 'D', 2, 3), ]

# 動かし方 :dy, :dx
MOVES = [[-1, 0], [1, 0], [0, -1], [0, 1]]

# ボードのサイズ
BOARD = { :y => 5, :x => 4 }

class Node

  def init
    @koma = INIT
    @state = Array.new(BOARD[:y]) do Array.new(BOARD[:x]) end
    state
  end

  def copy
    @koma
  end

  def state
    @state.each{ |line| line.fill("   ") }
    @koma.each do |k|
      k.height.times do |h|
        k.width.times do |w|
          @state[k.y + h][k.x + w] = k.name
        end
      end
    end
  end

  def to_s
    str = "--------\n"
    @state.each do |line|
      line.each do |name|
        str += name
      end
      str += "\n"
    end
    str
  end

  def move_koma
    @koma.each_with_index do |k, i|
      MOVES.each do |dy, dx|
        if movable?(i, dy, dx)
          nxt = Node.new(self)
          nxt.koma[i].y += dy
          nxt.koma[i].x += dx
        end
      end
    end
  end

  def movable?(i, dy, dx)
    k = @koma[i]
    # 盤からはみ出ないかチェック
    if ( (0 <= k.y + dy) &&
        (0 <= k.x + dx) &&
        (BORAD[:y] > k.y + k.height + dy) &&
        (BORAD[:x] > k.x + k.height + dx) )
      return false
    end

    # 隣接するコマがないかチェック
    k.height.times do |h|
      k.width.times do |w|
        side = @state[k.y + h][k.x + w]
        if (side != "   ") && (side != k.name)
          return false
        end
      end
    end

    return true
  end

end

node = Node.new
node.init
puts node.to_s
