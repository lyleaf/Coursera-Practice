import random

def read():
    with open("3.txt","r") as f:
        numbers = f.readlines()
    g = [[int(n) for n in line.split()] for line in numbers]
    return g

def MinCut(g,v,vertexSet):
    for i in xrange(len(g)-2):
        a,b = random.sample(v,2)
        Merge(a,b,g,v,vertexSet)
    
def Merge(a,b,g,v,vertexSet):
    g[a-1] = g[a-1]+g[b-1] # update the graph, just add the adjacent lists together
    vertexSet[a-1] = set.union(vertexSet[a-1],vertexSet[b-1]) #update the vertexSet, which shows the the vertexes that current vertex actually represents.
    v.remove(b) # v is the set of the vertices that remains, every time we use random sample from v to get the 2 vertices that we are going to merge.

if __name__ == "__main__":
    best = 10000  
    for i in xrange(1000):
        g = read()
        v = set([line[0] for line in g])
        vertexSet = [set((line[0],)) for line in g]
        
        MinCut(g,v,vertexSet)
        a,b = random.sample(v,2)
        r = sum([1 for x in g[a-1] if x not in vertexSet[a-1]])
        if r<best:
            best = r
            
    print best
