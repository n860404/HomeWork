# -*- coding: utf-8 -*-
#Optimistic Initial Value

import numpy as np
import math
class oivBandit:
    def __init__(self,mu,mean=1,times=0):
        self.mu=mu
        self.mean=mean
        self.times=times   #Run how many times
    def pull(self):
        return np.random.randn()+self.mu
    def update(self,xn):
        self.times+=1
        self.mean=(1-1.0/self.times)*self.mean+1.0/self.times*xn
        #the upper line can simply change to the line downward 
        #self.mean=(self.mean*(self.times-1)+self.pull())/self.times
def run(mu1,mu2,mu3,epsilon=0.1,N=10000):
    bandits=[oivBandit(mu1),oivBandit(mu2),oivBandit(mu3)]
    data=np.empty(N)#N個未初始化的值
    for i in range(N):
        p=np.random.random()
        #epsilon = 1 / math.log(i + 0.0000001)
        if p<epsilon:   #exploit others
            j=np.random.choice(3)
        else:   #exploit itself
            j=np.argmax([b.mean for b in bandits])
            
        x=bandits[j].pull()
        bandits[j].update(x)
        data[i]=x
    cumul_average=np.cumsum(data)/(np.arange(N)+1)
    return cumul_average
