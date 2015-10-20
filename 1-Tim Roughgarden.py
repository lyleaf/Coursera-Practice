def read():
    with open("IntegerArray.txt","r") as f:
        numbers = f.readlines()
    return numbers
    
def sortup(x):
    l = len(x)
    if l == 1:
        return x
    a = x[0:l/2]
    b = x[l/2:]
    a = sortup(a)
    b = sortup(b)
    i = 0
    j = 0
    c = []
    for k in xrange(l):
        if i == len(a):
            c.append(b[j])
            j += 1
        elif j == len(b):
            c.append(a[i])
            i += 1
        elif a[i] < b[j]:
            c.append(a[i])
            i += 1
        else:
            c.append(b[j])
            global n
            n += len(a)-i
            j += 1 
    x = c
    return x
    
if __name__ == "__main__":
    import time
    start_time = time.time()
    n = 0
    x = read()
    x = [int(i) for i in x]
    sortup(x)
    print n
    print "------%s seconds ------" % (time.time()-start_time)
