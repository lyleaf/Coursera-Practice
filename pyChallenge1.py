'''
My solution is write a lambda function and convert it to list.
Convert a list to string I can just join method. 

Other methods are: 

1.from string import maketrans
string.maketrans(trantab)

2.Use a dictionary.
zip function input two lists, return a list of tuples.
We can turn a list of tuples into dictionary. 

'''

def trans(x):
    if ord(x)+2 > 122:
        return chr(ord(x)+2-26)
    else: return chr(ord(x)+2)
s = "g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
a = np.array(list(s))
b = map(lambda x: trans(x),a)
''.join(str(e) for e in b)


from string import maketrans 
table = string.maketrans(string.ascii_lowercase,
	string.ascii_lowercase[2:]+string.ascii_lowercase[:2])
"map".translate(table)

import string
cypher = dict(zip(string.lowercase,string.lowercase[2:]+string.lowercase[:2]))
codedmessage="g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
print "".join(cypher.get(c,c) for c in codedmessage)