from random import randint
from itertools import cycle

values = [i for i in range(0, 161)]

up = []
for v in values:
	up.extend([v] * 3)

while len(up) != 600:

	up.append(randint(0, 160))

up.sort()

ccl = cycle(range(7))
with open('up_array.txt', 'w') as f:
	for i, value in enumerate(up):
		tmp = f'up[{i}] = {value};'
		c = next(ccl)
		if c == 4:
			tmp += '\n'
		else:
			tmp += ' '
		f.write(tmp)
print(len(up))
print(up[:7])
print(up[-7:])