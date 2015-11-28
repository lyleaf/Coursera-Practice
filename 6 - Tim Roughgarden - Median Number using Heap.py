import heapq

with open("Median.txt","r") as f:
	lines = f.readlines()

nums = [int(line) for line in lines]

#initialisation

median = nums[0]
SMALL = [nums[0]]
LARGE = []
heapq.heapify([nums[0]])
heapq.heapify(LARGE)
flag = 1

s = median
y = [median]
for i in nums[1::]:
    if i > median:
        heapq.heappush(LARGE,i)
        flag += 1
    else:
        heapq.heappush(SMALL,-i)
        flag -= 1
    if flag == 2:
        x = heapq.heappop(LARGE)
        heapq.heappush(SMALL,-x)
        flag = 0
    elif flag == -2:
        x = heapq.heappop(SMALL)
        heapq.heappush(LARGE,-x)
        flag = 0
    elif flag == 2:
        x = heapq.heappop(LARGE)
        heapq.heappush(SMALL,-x)
        flag = 0
    if flag == 1:
        median = LARGE[0]
    else: 
        median = -SMALL[0]
    # median
    s += median
    y.append(median)
    

print s%10000



