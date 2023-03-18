from typing import List


def hello(s = None):
    if (s == "" or s == None):
        n = "Hello!"
        return n
    else:
        n = "Hello, " + s + "!"
        return n

def int_to_roman(x):
    th = x // 1000 
    ost = x % 1000 
    hun = ost // 100 
    ost %= 100 
    doz = ost // 10 
    ost %= 10 
    un = ost
    Rome = ''
    if th!=0:
        Rome+='M'*th
    if hun!=0:
        if hun == 4:
            Rome+='CD'
        elif hun == 9:
            Rome+='CM'
        elif hun>=1 and hun <=3:
            Rome+='C'*hun
        elif hun>=5 and hun<9:
            Rome = Rome + 'D' + 'C'*(hun-5)
    if doz!=0:
        if doz == 4:
            Rome+='XL'
        elif doz == 9:
            Rome+='XC'
        elif doz>=1 and doz <=3:
            Rome+='X'*doz
        elif doz>=5 and doz<9:
            Rome = Rome + 'L' + 'X'*(doz-5)
    if un!=0:
        if un == 4:
            Rome+='IV'
        elif un == 9:
            Rome+='IX'
        elif un>=1 and un <=3:
            Rome+='I'*un
        elif un>=5 and un<9:
            Rome = Rome + 'V' + 'I'*(un-5)
    return Rome


def longest_common_prefix(x):
    leng = len(x)
    if leng == 0:
        return ''
    elif leng == 1:
        return x[0]
    for i in range(leng):
        x[i] = x[i].strip()
    x.sort()
    minleng = min(len(x[0]),len(x[-1]))
    prefix = ''
    for i in range(0,minleng):
        if x[0][i] == x[-1][i]:
            prefix+=x[0][i]
        else:
            break
    return prefix

def primes():
    x = 2
    while True:
        if isprime(x)==True:
            yield x
        x+=1
        
def isprime(x):
    for i in range(2, (x//2)+1):
        if (x%i) == 0:
            return False
    return True


class BankCard:
        def __init__(self,total_sum: int, balance_limit = -2):
            self.total_sum = total_sum
            self.balance_limit = balance_limit
        def __call__(self, sum_spent):
            print("SUM SPENT ", sum_spent, " BALANCE ", self.total_sum)
            if (self.total_sum < sum_spent):
                raise ValueError("Not enough money to spend ", sum_spent, "dollars")
    
            self.total_sum -= sum_spent
            print("You spent ", sum_spent, "dollars.")
        def __getattribute__(self, attribute):
            if attribute == 'balance':
                if self.balance_limit >=0:
                    self.balance_limit-=1
                    return self.total_sum
                elif self.balance_limit == -2:
                    return self.total_sum
                elif self.balance_limit == -1:
                    raise ValueError("Balance check limits exceeded")
            else:
                return object.__getattribute__(self, attribute)
        def put(self, sum_put):
            self.total_sum+=sum_put
            print("You put ", sum_put, "dollars.")
            return self.total_sum
        def __add__(self, x):
            self.total_sum += x.total_sum
            self.balance_limit = max(self.balance_limit, x.balance_limit)
            return self
        def __repr__(self):
            return "To learn the balance call balance."

