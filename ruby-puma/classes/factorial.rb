class Factorial
  def calculate(number)
    return unless number.to_i > 0

    result = ''
    result_in_digits = []
    remnant_division = 0

    result_in_digits[0] = 1
    (2..number).each do |i|
      result_in_digits.each_with_index do |digit, j|
        next if digit.nil?

        current_digit_multiplication = digit * i
        result_in_digits[j] = (current_digit_multiplication + remnant_division) % 10
        remnant_division = (current_digit_multiplication + remnant_division) / 10
      end
      while remnant_division != 0
        result_in_digits << remnant_division % 10
        remnant_division /= 10
      end
    end

    (0..(result_in_digits.size - 1)).reverse_each { |i| result += result_in_digits[i].to_s  }

    result
  end
end