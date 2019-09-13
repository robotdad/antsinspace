#!/usr/bin/env python

import rediswq
import subprocess
import sys
import time

host="redis"
# Uncomment next two lines if you do not have Kube-DNS working.
# import os
# host = os.getenv("REDIS_SERVICE_HOST")

q = rediswq.RedisWQ(name="antfiles", host="redis")
print("Worker with sessionID: " +  q.sessionID())
print("Initial queue state: empty=" + str(q.empty()))
print('', flush = True)

while not q.empty():
  item = q.lease(lease_secs=120, block=True, timeout=2) 
  if item is not None:
    filename = item.decode("utf-8")
    print()
    print("Ant data found")
    print("Working on " + filename)
    print('', flush = True)
    p = subprocess.call(['/usr/local/bin/antscrewcounter', filename], shell=False, stdout=sys.stdout, stderr=sys.stderr)
    print('', flush = True)
    print("Completed " + filename)
    q.complete(item)
  else:
    print("Waiting for work")
print()
print("Queue empty, exiting")