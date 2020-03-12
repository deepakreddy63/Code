import numpy as np

class inc():
    def __init__(self):
        self.p = 0
    def increase(self, n):
        self.p = self.p+n
    

i = inc()
def show(i,n):
    i.increase(n)
show(i,2)
print(i.p)

def emitter(p=0.03):
    'return a random value with probability p, else 0'
    while True:
        v = np.random.rand(1)
        if v > p:
            yield 0.
        else:
            yield np.random.rand(1)

a =emitter(0.5)
#for _ in range(10):
#    print(next(a))

