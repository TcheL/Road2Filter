#!/usr/bin/env python3

import numpy as np

def lowPassFIR(fc, b = 0.08):
  #fc: Cutoff frequency as a fraction of the sampling rate (in (0, 0.5)).
  #b: Transition band, as a fraction of the sampling rate (in (0, 0.5)).

  N = int(np.ceil((4 / b)))
  if not N % 2: N += 1  # Make sure that N is odd.
  n = np.arange(N)
   
  # Compute sinc filter.
  h = np.sinc(2 * fc * (n - (N - 1) / 2))
   
  # Compute Blackman window.
  w = 0.42 - 0.5 * np.cos(2 * np.pi * n / (N - 1)) + \
      0.08 * np.cos(4 * np.pi * n / (N - 1))
   
  # Multiply sinc filter by window.
  h = h * w
   
  # Normalize to get unity gain.
  h = h / np.sum(h)

  return N, h

#-------------------------------------------------------------------------------

import matplotlib.pyplot as plt

fs = 1000 # sampling frequency

# generate properly the time vector
t = np.arange(1000)/fs
sga = np.sin(2*np.pi*2*t)   # signal with f = 2
sgb = np.sin(2*np.pi*10*t)  # signal with f = 10
sgc = sga + sgb

N, h = lowPassFIR(fc = 6/fs, b = 2/fs)
sgf = np.convolve(sgc, h)

plt.plot(t, sgc, label = 'original')
plt.plot(t, sgf[int(N/2):1000 + int(N/2)], label = 'low-pass')
plt.plot(t, sga, label = 'f = 2')
plt.legend()
plt.show()

