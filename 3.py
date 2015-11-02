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
    g[a-1] = g[a-1]+g[b-1]
    vertexSet[a-1] = set.union(vertexSet[a-1],vertexSet[b-1])
    v.remove(b)

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
