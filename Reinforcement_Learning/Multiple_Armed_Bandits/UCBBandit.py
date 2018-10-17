# -*- coding: utf-8 -*-

import numpy as np
import math


class UCBBandit:
    def __init__(self,mu,mean=0,times=0):
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
def run(mu1,mu2,mu3,N=10000):
    bandits=[UCBBandit(mu1),UCBBandit(mu2),UCBBandit(mu3)]
    data=np.empty(N)#N個未初始化的值
    n_arm=len(bandits)
        
    for i in range(N):
        total_counts=i     
        if i<3:
            for arm in range(n_arm):
                if bandits[arm].times==0:
                    j=arm
                    break
                        
                        
        else:
            ucb_value=[0.0 for arm in range(n_arm)] 
            for arm in range(n_arm):        
                
                bonus=math.sqrt((2*math.log(total_counts))/float(bandits[arm].times))
                ucb_value[arm]=bandits[arm].mean+bonus
                #print(ucb_value)
            j=np.argmax(ucb_value)
            
        x=bandits[j].pull()
        bandits[j].update(x)
        data[i]=x
        
    cumul_average=np.cumsum(data)/(np.arange(N)+1)
    return cumul_average
