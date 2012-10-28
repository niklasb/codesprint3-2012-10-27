n, m = map(int, raw_input().split())
strs = [raw_input() for _ in xrange(n)]
def is_palin(s):
  return s == s[::-1]
best = -1
dat = None
for i in xrange(n):
  for j in xrange(n):
    if i == j: continue
    for x in xrange(m+1):
      for y in xrange(m+1):
        s = strs[i][:x] + strs[j][y:]
        if is_palin(s):
          if len(s) > best:
            best = len(s)
            dat = [i,j,x,y,strs[i],strs[j]]

print best
#print dat
