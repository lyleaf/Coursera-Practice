# -*- coding: utf-8 -*-
"""
Created on Wed Nov 18 14:15:48 2015

Dijkstra Algorithm using Priority Queue

Used PriorityQueue. Other choices: use heapq
Didn't implement the heap that support deletion
Used tuple in PriorityQueue. Other choices: use Class

TODO: An updated version of Dijkstra. 

@author: yiling
"""
import Queue 

with open("dijkstraData.txt","r") as f:
    lines = f.readlines()
graph = [[tuple([int(i.split(",")[1]),int(i.split(",")[0])]) for i in line.split()[1:]] for line in lines]
q = Queue.PriorityQueue()


distance = [100000 for i in xrange(len(graph))]

s = 1 #start point


A = [(0,s)]
distance[s-1] = 0

for i in graph[s-1]:
    q.put(i)
    distance[i[1]-1] = i[0]
#initialization part


while (not q.empty()):
    x = q.get()
    if x[1] in map(lambda x:x[1],A):#This added a lot of complexity to my algorithm
        continue
    A.append(x)
    for i in graph[x[1]-1]:
        if i[0]+x[0] < distance[i[1]-1]:
            distance[i[1]-1] = i[0]+x[0] 
            q.put((distance[i[1]-1],i[1]))

index = [7,37,59,82,99,115,133,165,188,197]
ans = [distance[i-1] for i in index]

print ans
