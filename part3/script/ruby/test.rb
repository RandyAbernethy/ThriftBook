class Calendar
  def initialize(month, year)
    @month = month
    @year  = year
  end

  # A simple wrapper around the *nix cal command.
  def to_s
    IO.popen(["cal", @month.to_s, @year.to_s]) { |io| io.read }
  end
end

puts Calendar.new(8, 2011)
