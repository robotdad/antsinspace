import os
import redis
import subprocess
import sys

numfiles = sys.argv[1]
minlines = sys.argv[2]
maxlines = sys.argv[3]

print('Transmission incoming...')
print('Ants sorting screws...')
print('Expecting {} files with at least {} but no more than {} lines.'.format(numfiles, minlines, maxlines))
print('Start')
print('', flush = True)

p = subprocess.call(['/usr/local/bin/antspacedata', numfiles, minlines, maxlines], shell=False, stdout=sys.stdout, stderr=sys.stderr)

print('', flush = True)
print('End transmission')
print()
r = redis.Redis(host='redis', port=6379, db=0)
print('Queing work...')
print()

for root, dirs, files in os.walk('.'):
    for filename in files:
        print(filename, flush = True)
        r.rpush('antfiles', filename)
print('', flush = True)
print('Work queued')
print('Exit')
