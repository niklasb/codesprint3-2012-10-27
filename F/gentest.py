import random
N = 10
M = 10
print N, M
for _ in xrange(N):
  print ''.join(random.choice(['a','b','c']) for _ in xrange(M))
