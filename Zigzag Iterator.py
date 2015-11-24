"""
https://leetcode.com/problems/zigzag-iterator/

评论：     自己在形成v3的时候写的东西有点乱。可以用一个变量Lcommon来表达v1与v2的common length部分。
"""

class ZigzagIterator(object):

    def __init__(self, v1, v2):
        self.v1 = v1
        self.v2 = v2
        self.v3 = []
        if (len(v1)<=len(v2)):
            for index,value in enumerate(v1):
                self.v3.append(value)
                self.v3.append(v2[index])
            for value in self.v2[len(v1)::]:
                self.v3.append(value)
        else:
            for index,value in enumerate(v2):
                self.v3.append(v1[index])
                self.v3.append(value)
            for value in self.v1[len(v2)::]:
                self.v3.append(value)
        self.n = 0
	  
        

    def next(self):
        """
        :rtype: int
        """
        x = self.v3[self.n]
        self.n += 1
        return x

    def hasNext(self):
        """
        :rtype: bool
        """
        return not (self.n == len(self.v3))
