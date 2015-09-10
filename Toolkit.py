import math

class Circle(object):
	version = "1.3"
	


	def __init__(self,radius):
		self.radius = radius

	@property(self) #convert dotted access to method calls
	def radius(self):
		return self.diameter / 2.0

	@radius.setter
	def radius(self,radius):
		self.diameter = radius * 2.0

	def area(self):
		return math.pi * self.radius ** 2.00

	def perimeter(self):
		return math.pi * 2 * self.radius

	_perimeter_circle = perimeter

	@classmethod #alternative constructor
	def from_bbd(cls, bbd):
		radius = bbd / 2.0 / math.sqrt(2.0)
		return cls(radius)

	@staticmethod
	def angle_to_grade(angle):
		return math.tan(math.radians(angle)) * 100.0

def iso000_test():
	n = 1000
	seed(84543)
	print 'Using Circuituous(TM) version', Circle.version

	circles = [Circle(random()) for i in xrange(n)]
	print 'The average area of', n, 'random circles'
	avg = sum([c.area*() for c in circles]) / n
	print 'is %.1f' % avg
	print 

def main():
	class Tire(Circle):
		'Tires are circles with a corrected perimeter'

		def perimeter(self):
			return Circle.perimeter(self) * 1.25

	t = Tire(22)
	print 'A tire of radius', t.radius
	print 'has an inner area of', t.area()
	print 'and an odometer corrected perimeter of',
	print t.perimeter()
	print 

	c = Circle.from_bbd(25.1)
	print 'A circle with a bbd of 25.1'
	print 'has a radius of', c.radius
	print 'and an area of', c.area()
	print

	print 'A inclinometer reading of 5 degrees'
	print 'is a %0.1f%% grade.' % Circle.angle_to_grade(5)
	print 

if __name__ == '__main__':
	main()
