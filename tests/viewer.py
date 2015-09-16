# -*- coding: utf-8 -*-
"""
Created on Sat May 23 18:34:36 2015

@author: kiryl
"""
import numpy as np





#a = imread('/home/kiryl/Documents/openlf/openlf/tests/data_2/stxx.jpg')
#b = imread('/home/kiryl/Documents/openlf/openlf/tests/data_2/stxy.jpg')
#c = imread('/home/kiryl/Documents/openlf/openlf/tests/data_2/styy.jpg')
#d = imread('/home/kiryl/Documents/openlf/openlf/tests/data_2/stcoherence.jpg')
e = imread('/home/kiryl/Documents/openlf/openlf/tests/data_2/focused_scharr3x3_full.jpg')

#c = imread('/home/kiryl/Documents/openlf/openlf/tests/data_2/3epi_backfocus_26.jpg')

#d = imread('/home/kiryl/Documents/openlf/openlf/tests/data_2/4epi_uncut_26_2.jpg')

#e = imread('/home/kiryl/Documents/openlf/openlf/tests/data_2/5epi_backfocus_26_2.jpg')
#a = a.astype(float)/255.0
#b = b.astype(float)/255.0
#c = c.astype(float)/255.0
#print shape(a)
#print shape(b)
#print shape(c)
#print shape(d)
#print shape(e)
#up = np.sqrt((c-a)**2 + 4*b**2)
#down = c + a
#np.place(down, down < 1e-9, 1)
#coh = up / down

#imshow(coh,interpolation="nearest")
e = e.astype(float)/255.0
imshow(e,interpolation="nearest")

