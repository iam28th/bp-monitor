from itertools import cycle

with open('ArmCuff15.txt', 'r') as inp, open('Arm15down.txt', 'w') as out:
	ccl = cycle(range(6))
	for i, line in enumerate(inp):
		c = next(ccl)
		cuff_pressure = line.split(' ')[1]
		tmp = f'down[{i}] = {cuff_pressure};'
		if c == 5:
			tmp += '\n'
		else:
			tmp += ' '
		out.write(tmp)
