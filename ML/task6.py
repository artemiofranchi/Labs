from collections import Counter
def check(s, filename):
    f = open(filename, 'w')
    s = s.split(" ")
    for i in range(len(s)):   
        s[i] = s[i].lower()
    povt = Counter(s)
    new_s = list(set(s))
    new_s.sort()
    counter = 0
    for i in range(len(new_s)):
        counter = povt[new_s[i]]
        f.write(new_s[i].lower()+" "+str(counter)+"\n")
    
    f.close()

