# -*- coding: utf-8 -*-

import numpy as np

class greedyBandit:
    def __init__(self,mu,mean=0,times=0):
        self.mu=mu
        self.mean=mean
        self.times=times   #Run how many times
    def pull(self):
        return np.random.randn()+self.mu
    def update(self,xn):
        self.times+=1
        self.mean=(1-1.0/self.times)*self.mean+1.0/self.times*xn

def run(mu1,mu2,mu3,epsilon=0.1,N=10000):
    bandits=[greedyBandit(mu1),greedyBandit(mu2),greedyBandit(mu3)]
    data=np.empty(N)#N個未初始化的值
    for i in range(N):
        p=np.random.random()
        if p<epsilon:   #exploit others
            j=np.random.choice(3)
        else:   #exploit itself
            j=np.argmax([b.mean for b in bandits])
            
        x=bandits[j].pull()
        bandits[j].update(x)
        data[i]=x
    cumul_average=np.cumsum(data)/(np.arange(N)+1)

    return cumul_average
    
        
