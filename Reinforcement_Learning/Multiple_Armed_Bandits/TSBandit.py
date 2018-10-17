# -*- coding: utf-8 -*-

import numpy as np
import math
import pymc
class TSBandit:
    def __init__(self,mu,mean=0,times=0,wins=0,lose=0):
        self.mu=mu
        self.mean=mean
        self.times=times   #Run how many times
        self.wins=wins
        self.lose=lose
    def pull(self):
        #if np.random.randn()+self.mu>=self.mu:
        if np.random.rand()<=self.mu:
            self.wins+=1
            return 1
        else:
            self.lose+=1
            return 0
    def update(self,xn):
        self.times+=1
        self.mean=(1-1.0/self.times)*self.mean+1.0/self.times*xn
        #the upper line can simply change to the line downward 
        #self.mean=(self.mean*(self.times-1)+self.pull())/self.times
def run(mu1,mu2,mu3,N=10000):
    bandits=[TSBandit(mu1),TSBandit(mu2),TSBandit(mu3)]
    data=np.empty(N)#N個未初始化的值
    n_arm=len(bandits)
    for i in range(N):

        j = np.argmax([pymc.rbeta(1 + b.wins, 1 +b.lose)for b in bandits])

        x=bandits[j].pull()
        bandits[j].update(x)
        data[i]=x
    cumul_average=np.cumsum(data)/(np.arange(N)+1)
    return cumul_average
    
   
