
require 'slyce'
require 'set'

class Summon
	
	self.slyce_class do |spec|
		spec.rest(:string)
	end
	
	def execute
		files = Set.new
		errors = false
		@argv.each do |arg|
			if File.directory?(arg)
				files << File.expand_path(arg)
			elsif File.file?(arg) && File.extname(arg) == '.rift'
				Dir.glob("#{arg.gsub('\\', '/')}/**/*.rift").each do |f|
					files << File.expand_path(f)
				end
			else
				$stderr.puts("Invalid path: #{arg}")
				errors = true
			end
		end
		if errors
			$stderr.puts("Found invalid paths...")
			exit(1)
		end
	end
	
end
