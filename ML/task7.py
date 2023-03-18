def find_shortest(l):
    str = ''
    for i in l:
        if i.isalpha():
            str+=i
        else:
            str+=' '
    str = str.split()
    if str:
        return len(min(str, key = len))
    else:
        return 0