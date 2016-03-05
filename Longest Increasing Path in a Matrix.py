class Node(object):
    def __init__(self,x,y,value):
        self.x = x
        self.y = y
        self.v = value
    def __cmp__(self,other):
        return cmp(self.v, other.v)
    def __str__(self):
        return str([self.x,self.y,self.v])
        
class Solution(object):
    def longestIncreasingPath(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: int
        """
        if not matrix:
            return 0
        l = len(matrix)
        l2 = len(matrix[0])
        s = []
        
        def findNeighbors(node):
            X = []
            x = node.x
            y = node.y
            if x-1 >= 0:
                X.append(Node(x-1,y,matrix[x-1][y]))
            if x<l-1:
                X.append(Node(x+1,y,matrix[x+1][y]))
            if y>=1:
                X.append(Node(x,y-1,matrix[x][y-1]))
            if y<l2-1:
                X.append(Node(x,y+1,matrix[x][y+1]))
            return X
        
        dp = [[1 for i in range(l2)] for j in range(l)]

        for i in xrange(l):
            for j in xrange(l2):
                n = Node(i,j,matrix[i][j])
                s.append(n)
        s.sort()
        highest_in_dp = 1
        for i in s:
            #print i
            #print dp
            ns = findNeighbors(i)
            highest = 1
            for j in ns:
                if j<i:
                    temp=dp[j.x][j.y]+1
                    if temp > highest:
                        highest = temp
            dp[i.x][i.y] = highest
            if highest > highest_in_dp:
                highest_in_dp = highest
        return highest_in_dp
