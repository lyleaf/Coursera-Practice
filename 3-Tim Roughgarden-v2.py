# -*- coding: utf-8 -*-
"""
Created on Wed Nov  4 22:04:24 2015

Use condition check to check if the merges are possible or not. 
TODO: Use a union check data structure. 

@author: yiling
"""

import random

def read():
    with open("test","r") as f:
        numbers = f.readlines()
    g = [[int(n) for n in line.split()] for line in numbers]
    return g

def MinCut(g,v,vertexSet):
    for i in xrange(len(g)-2):
        a,b = sample(g,v)
        Merge(a,b,g,v,vertexSet)
    a,b = random.sample(v,2)
    r = sum([1 for x in g[a-1] if x not in vertexSet[a-1]])
    #print r
    return r
        
def sample(g,v):
    a = random.sample(v,1)[0]
    g[a-1] = [x for x in g[a-1] if x not in vertexSet[a-1]]
    b = random.sample(set(g[a-1]),1)[0]
    return a,b
    
def Merge(a,b,g,v,vertexSet):
    g[a-1] = g[a-1] + g[b-1]
    for x in g[a-1]:
        if x in [a,b]: del x   
    for x in g:
        for y in x:
            y = y if y is not b else a
    g[b-1] = []
    vertexSet[a-1] = set.union(vertexSet[a-1],vertexSet[b-1]) #update the vertexSet, which shows the the vertexes that current vertex actually represents.
    v.remove(b) # v is the set of the vertices that remains, every time we use random sample from v to get the 2 vertices that we are going to merge.

def change(g):
    g = [[] for x in g]
    
if __name__ == "__main__":
    best = 1000000  
    for i in xrange(100000):
        g = read()
        v = set([line[0] for line in g])
        vertexSet = [set((line[0],)) for line in g]    
        r = MinCut(g,v,vertexSet)    
        if r<best:
            best = r
            
    print best
