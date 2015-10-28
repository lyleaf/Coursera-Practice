def read():
    with open("10.txt","r") as f:
        numbers = f.readlines()
    return numbers
    
def quicksort(x,start,end):
    global n 
    l = end-start
    if l == 1:
        return
    if l == 0:
        return
    n += l-1
    pivot = x[start]
    i = start
    for j in range(1,l):
        if pivot > x[j+start]:
            i+=1
            temp = x[i]
            x[i] = x[j+start]
            x[j+start] = temp
    x[start] = x[i]
    x[i] = pivot
    #print "ha"
    quicksort(x,start,i)
    quicksort(x,i+1,end)
    
def quicksort_end(x,start,end):
    global n 
    l = end-start
    if l == 1:
        return
    if l == 0:
        return
    n += l-1
    pivot = x[end-1]
    i = start
    for j in range(0,l):
        if pivot > x[j+start]:
            i+=1
        else:
            temp = x[i]
            x[i] = x[j+start]
            x[j+start] = temp
    x[end-1] = x[i]
    x[i] = pivot
    #print "ha"
    quicksort(x,start,i)
    quicksort(x,i+1,end)
    
if __name__ == "__main__":
    n = 0
    x = read()
    x = [int(i) for i in x]
    x = [1,2,3,4]
    quicksort_end(x,0,len(x))
    print n
    quicksort(x,0,len(x))
    print n

#162085

