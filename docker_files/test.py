import numpy as np
from PySTARE import SSTARE
s = SSTARE()

from time import time

print()
print("For (lat, lon) = (0, 0)")
print("app/lookup stats:")
from subprocess import Popen, PIPE
for d in range(5,30,5):
    vtime=[]
    ptime=[]
    for i in range(100):
        p = Popen("/root/stare/build/app/lookup {0} 0 0".format(d).split(), stdout=PIPE)
        start = time()
        result = p.communicate()
        end = time()
        vtime.append(end-start)
        ptime.append(float(result[0].split()[-5]))
    vtime=np.array(vtime)
    ptime=np.array(ptime)
    sidx = result[0].split()[-1]
    print("###################################################################################")
    print("Depth {0}".format(d))
    print("STARE index {0:b}".format(int(sidx)))
    print("Python Popen communicate takes: {0:e} +- {1:e}".format(np.mean(vtime),np.std(vtime)))
    print("lookup performance stats: {0:e} +- {1:e} / sec".format(np.mean(ptime),np.std(ptime)))
    #print("###################################################################################")
#lat,lon=s.LatLonDegreesFromValueNP(idx)

print()
print()
print("For (lat, lon) = (0, 0)")
print("python module stats:")
for d in range(5,30,5):
    vtime=[]
    for i in range(100):
        start = time()
        idx=s.ValueFromLatLonDegreesNP(np.array([0]),np.array([0]),d)
        end = time()
        vtime.append(end-start)
    vtime=np.array(vtime)
    print("###################################################################################")
    print("Depth {0}".format(d))
    print("STARE index: {0:b}".format(idx[0]))
    print("Time used: {0:e} +- {1:e}".format(np.mean(vtime),np.std(vtime)))
    #print("###################################################################################")
#lat,lon=s.LatLonDegreesFromValueNP(idx)
#print(idx)
#print(lat, lon)

