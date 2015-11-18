"""

output the sizes of the 5 largest SCCs in the given graph, in decreasing order of sizes
#Which data structure should i use? I think is dictionary.
"""

def read():
    with open("SCC.txt","r") as f:
        numbers = f.readlines()    
    #g = {}
    #for line in numbers:
    #    g[line.split()[0]] = line.split()[1]
    #g = dict([([int(n) for n in line.split()]) for line in numbers])  which is faster
    g = [[int(n) for n in line.split()] for line in numbers]
    n = g[-1][0]
    graph = {}
    rGraph = {}
    nodes = set()
    for edge in g:
        last = edge[0]
        x = graph.get(last,[])
        x.append(edge[1])
        graph[last] = x
        ###
        rLast = edge[1]
        y = rGraph.get(rLast,[])
        y.append(edge[0])
        rGraph[rLast] = y
        
        nodes.add(last)
        nodes.add(rLast)
    
        
    return graph,rGraph,n


def DFS(graph,s):
    global trace #global and pass parameter diff
    global count
    global order

    stack = []
    stack.append(s)
    trace[s-1] = 1
    while (len(stack)):
        v = stack[-1]
        nearby = graph.get(v,[])
        unvisitedVertex = filter(lambda x: trace[x-1] == 0,nearby)
        if (len(unvisitedVertex)):
            for i in unvisitedVertex: 
                stack.append(i)
                trace[i-1] = 1
        else:
            poped = stack.pop()
            order[count-1] = poped
            count += 1
            print count
    
def DFS2(graph,s):
    stack = []
    stack.append(s)
    trace[s-1] = 1
    global count
    while (len(stack)):
        v = stack[-1]
        nearby = graph.get(v,[])
        unvisitedVertex = filter(lambda x: trace[x-1] == 0,nearby)
        if (len(unvisitedVertex)):        
            for i in unvisitedVertex: 
                stack.append(i)
                trace[i-1] = 1
        else:
            poped = stack.pop()
            count += 1
                
def main():
    graph,rGraph,n = read()
    global trace 
    global order
    trace = [0 for x in xrange(n)]
    s = 1
    order = [0 for x in xrange(n)]
    global count 
    count = 1
    while (sum(trace)!=n):
        while (trace[s-1]==1):
            s += 1
        DFS(rGraph,s)
    
    index = n-1  
    trace = [0 for x in xrange(n)]
    count = 1
    lastCount = count

    l = []
    while (sum(trace)!=n):    
        lastCount = count
        while (trace[order[index]-1]==1):
            index -= 1
        DFS2(graph,order[index])  
        l.append(count - lastCount)
    return l
             
if __name__ == "__main__":
    l = main()
    #print l
 
    l.sort()
    if (len(l)<5):
        print l
    else:
        print l[-5:]
 
    
