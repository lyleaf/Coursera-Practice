# -*- coding: utf-8 -*-
"""
Created on Wed Nov 18 14:15:48 2015

@author: yiling
"""

import Queue 
with open("dijkstraData.txt","r") as f:
    lines = f.readlines()
graph = [[tuple([int(i.split(",")[1]),int(i.split(",")[0])]) for i in line.split()[1:]] for line in lines]
q = Queue.PriorityQueue()

#class Vertex(object):
#    def __init__(self, weight)
distance = [100000 for i]

A = [(0,1)]
B = [range(2,201)]
for i in graph[0]:
    q.put(i)
#initialization part
while True:
    if q.empty(): break
    x=q.get()
    print x
    if x[1] in map(lambda x:x[1],A):
        continue
    for i in graph[x[1]-1]:
        q.put(i[0]+x[0],i[1])
    
   
q.get()

A.append()

while True:
    x 
    
for weight,vertex in q.get():
    pass
