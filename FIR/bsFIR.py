#!/usr/bin/env python3

import numpy as np
 
def bandStopFIR(fL, fH, b = 0.08):
  N = int(np.ceil(4 / b))
  if not N % 2: N += 1
  n = np.arange(N)

  hlpf = np.sinc(2 * fL * (n - (N - 1) / 2))
  hlpf *= np.blackman(N)
  hlpf /= np.sum(hlpf)

  hhpf = np.sinc(2 * fH * (n - (N - 1) / 2))
  hhpf *= np.blackman(N)
  hhpf /= np.sum(hhpf)
  hhpf *= - 1
  hhpf[(N - 1) // 2] += 1

  h = hlpf + hhpf
  
  return N, h

#-------------------------------------------------------------------------------

import matplotlib.pyplot as plt

fs = 1000 # sampling frequency

# generate properly the time vector
t = np.arange(1000)/fs
sga = np.sin(2*np.pi*2*t)   # signal with f = 2
sgb = np.sin(2*np.pi*6*t)   # signal with f = 6
sgc = np.sin(2*np.pi*10*t)  # signal with f = 10
sgd = sga + sgb + sgc
sge = sga + sgc

N, h = bandStopFIR(fL = 4/fs, fH = 8/fs, b = 2/fs)
sgf = np.convolve(sgd, h)

plt.plot(t, sgd, label = 'original')
plt.plot(t, sge, label = 'f = 2 with f = 10')
plt.plot(t, sgf[int(N/2):1000 + int(N/2)], label = 'band-stop')
plt.legend()
plt.show()

