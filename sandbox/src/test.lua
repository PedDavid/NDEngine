foo = 4
bar = {}
bar[3] = "hi"
bar["key"] = "there"

function helloWorld()
	print 'Hello Lua!'
end

function sum_and_difference(a, b)
	return (a + b), (a - b)
end

function add(a, b)
	return a + b
end

function take(a, b)
	takeFunction(add, a, b)
end