from collections import defaultdict

d = defaultdict(int)
state = (0,0)

def frame(state, left, total, throws = ()):
  if left == 0:
    if state[1]:
      for a in xrange(11):
        maxb = 10 if a == 10 else 10 - a
        for b in xrange(maxb+1):
          t = total + state[0] * a + state[1] * b
          d[t] += 1
    elif state[0]:
      for a in xrange(11):
        t = total + a*state[0]
        d[t] += 1
    else:
      d[total] += 1
    return

  for a in xrange(11):
    if a == 10:
      frame((state[1] + 1, 1), left - 1, total + a + state[0] * a,
           throws + ((a,),))
    else:
      for b in xrange(10 - a + 1):
        if a + b == 10:
          frame((1, 0), left - 1, total + a + state[0]*a + b + state[1]*b,
              throws + ((a,b),))
        else:
          frame((0, 0), left - 1, total + a + state[0]*a + b + state[0]*b,
              throws + ((a,b),))

import sys
N = 2
frame((0,0), N, 0)
#print d
print len(d)
for k, v in sorted(d.items()):
  print N, k
  sys.stderr.write("%d\n" % v)
