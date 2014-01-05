module Graphics

  module Renderers
  	Ascii = :Ascii
  	Html = :Html
  end

  module HtmlHelper
    def initialize_html_printer()
      printer = ""
      first_part(printer)
      second_part(printer)
      third_part(printer)
      fourth_part(printer)
      printer
    end

    def first_part(html)
      html << "<!DOCTYPE html>
      <html>
      <head>
        <title>Rendered Canvas</title>
        <style type=\"text/css\">
          .canvas {"
    end

    def second_part(html)
      html << "font-size: 1px;
            line-height: 1px;
          }
          .canvas * {
            display: inline-block;
            width: 10px;"
    end

    def third_part(html)
      html << "height: 10px;
            border-radius: 5px;
          }
          .canvas i {
            background-color: #eee;
          }"
    end

    def fourth_part(html)
      html << ".canvas b {
            background-color: #333;
          }
        </style>
      </head>
      <body><div class=\"canvas\">\n"
    end

    def last_part
      "\n  </div>
      </body>
      </html>" 
    end
  end

  class Point
    attr_reader :x, :y

    def initialize(x, y)
      @x = x
      @y = y
    end

    def ==(other)
      @x == other.x && @y == other.y
    end

    def eql?(other)
      @x == other.x && @y == other.y
    end
  end

  class Line
    attr_reader :from, :to

    def initialize(from, to)
      @from = from
      @to = to
    end

    def from
      if @from.x + @from.y < @to.x + @to.y
        @from
      else
        @to
      end
    end

    def to
      if @from.x + @from.y < @to.x + @to.y
        @to
      else
        @from
      end
    end

    def ==(other)
      self.from == other.from && self.to == other.to
    end

    def eql?(other)
      self.from == other.from && self.to == other.to
    end
  end

  class Rectangle
    attr_reader :first_point, :second_point

    def initialize(first_point, second_point)
      @first_point = first_point
      @second_point = second_point
    end

    def top_left
      coordinate_x = @first_point.x < @second_point.x ? @first_point.x : @second_point.x
      coordinate_y = @first_point.y < @second_point.y ? @first_point.y : @second_point.y
      Point.new coordinate_x, coordinate_y
    end

    def top_right
      coordinate_x = @first_point.x < @second_point.x ? @second_point.x : @first_point.x
      coordinate_y = @first_point.y < @second_point.y ? @first_point.y : @second_point.y
      Point.new coordinate_x, coordinate_y
    end

    def bottom_left
      coordinate_x = @first_point.x < @second_point.x ? @first_point.x : @second_point.x
      coordinate_y = @first_point.y < @second_point.y ? @second_point.y : @first_point.y
      Point.new coordinate_x, coordinate_y
    end

    def bottom_right
      coordinate_x = @first_point.x < @second_point.x ? @second_point.x : @first_point .x
      coordinate_y = @first_point.y < @second_point.y ? @second_point.y : @first_point.y
      Point.new coordinate_x, coordinate_y
    end

    def ==(other)
      self.top_left == other.top_left &&
      self.top_right == other.top_right &&
      self.bottom_left == other.bottom_left &&
      self.bottom_right == other.bottom_right
    end

    def eql?(other)
      self.top_left == other.top_left &&
      self.top_right == other.top_right &&
      self.bottom_left == other.bottom_left &&
      self.bottom_right == other.bottom_right
    end
  end

  class BresenhamAlgorithmCanvas
    attr_reader :width, :height

    private
    def initialize_bresenham_algorithm(from, to)
      @error = 0
      @deltax_error = (to.y.to_f - from.y.to_f)/(to.x.to_f - from.x.to_f)
      @deltay_error = (to.x.to_f - from.x.to_f)/(to.y.to_f - from.y.to_f)
      @y = from.y
      @x = from.x
    end

    private
    def set_pixel(horizontal_position, vertical_position)
      if horizontal_position >= @width || vertical_position >= @height
        raise ArgumentError, 'Argument is out of range'
      end
      @the_picture[vertical_position][horizontal_position] = '@'
    end

    private
    def draw_near_horizontal(from, to)
      (from.x..to.x).each do |index|
        set_pixel index, @y
        @error += @deltax_error
        if @error >= 0.5
          @y += 1
          @error -= 1.0
        end
      end
    end

    private
    def draw_near_vertical(from, to)
      (from.y..to.y).each do |index|
        set_pixel @x, index
        @error += @deltay_error
        if @error >= 0.5
          @x += 1
          @error -= 1.0
        end
      end
    end
  end

  class Canvas < BresenhamAlgorithmCanvas
    include HtmlHelper

	  def initialize(width, height)
      super()
  	  @width = width
  	  @height = height
  	  @the_picture = Array.new(height, '-').map { Array.new(width, '-') }
  	end

  	def set_pixel(horizontal_position, vertical_position)
      super(horizontal_position, vertical_position)
  	end

  	def pixel_at?(horizontal_position, vertical_position)
  	  @the_picture[vertical_position][horizontal_position] == '@' ? true : false
  	end

  	def render_as(type_of_renderer)
  	  case type_of_renderer
  	  when Renderers::Ascii
  	  	render_as_ascii
  	  when Renderers::Html
  	  	render_as_html
  	  end
  	end

    def draw(figure)
      case figure
      when Point 
        set_pixel(figure.x, figure.y)
      when Line
        draw_line(figure.from, figure.to)
      else draw_rectangle(figure)
      end
    end

    private
    def draw_line(from, to)
      initialize_bresenham_algorithm(from, to)
      if to.x - from.x > to.y - from.y
        draw_near_horizontal(from, to)
      else
        draw_near_vertical(from, to)
      end
    end

    private
    def draw_rectangle(figure)
      draw_line(figure.top_left, figure.top_right)
      draw_line(figure.top_left, figure.bottom_left)
      draw_line(figure.top_right, figure.bottom_right)
      draw_line(figure.bottom_left, figure.bottom_right)
    end

    private
  	def render_as_ascii()
  	  printer = []
  	  @the_picture.each { |row| printer << row.join('') }
  	  printer
  	end

    private
  	def render_as_html()
      printer = initialize_html_printer
  	  @the_picture.each do |row|
  	  	row.each { |index| index == '@' ?  printer << '<b></b>' : printer << '<i></i>' }
  	  	printer << '<br>'
  	  end
  	  printer << last_part
  	end
  end
end

############# Example of how it works #################
module Graphics
  canvas = Canvas.new 30, 30

  # Door frame and window
  canvas.draw Rectangle.new(Point.new(3, 3), Point.new(18, 12))
  canvas.draw Rectangle.new(Point.new(1, 1), Point.new(20, 28))

  # Door knob
  canvas.draw Line.new(Point.new(4, 15), Point.new(7, 15))
  canvas.draw Point.new(4, 16)

  # Big "R"
  canvas.draw Line.new(Point.new(8, 5), Point.new(8, 10))
  canvas.draw Line.new(Point.new(9, 5), Point.new(12, 5))
  canvas.draw Line.new(Point.new(9, 7), Point.new(12, 7))
  canvas.draw Point.new(13, 6)
  canvas.draw Line.new(Point.new(12, 8), Point.new(13, 10))

  puts canvas.render_as(Renderers::Ascii)
end

