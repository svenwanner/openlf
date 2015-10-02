# -*- coding: utf-8 -*-
"""
Created on Thu Mar 20 11:15:27 2014

@author: swanner
"""

import scipy.misc as mi
import numpy as np
from glob import glob

lftype = "3DV"
cams_h = 5
cams_v = 5

path_in = "./"+lftype+"/h1_v7_h64_w48/rgb/"
path_out = "./"+lftype+"/h1_v7_h64_w48/bw/"
path_lf = "./"+lftype+"/"
fname_lf = "LF"+lftype+".png"
pattern = ""
filetype = "png"


def get_filenames(path,pattern,filetype):
    files = []
    if not path.endswith("/"): path+="/"
    if not filetype.startswith("."): filetype="."+filetype
    print path,pattern,filetype
    for name in glob(path+pattern+"*"+filetype):
        files.append(name)
    files.sort()
    return files
    
    
def get_files(path,pattern,filetype):
    imgs = []    
    file_names = get_filenames(path,pattern,filetype)
    for fname in file_names:
        imgs.append(mi.imread(fname))
    return file_names,imgs
    

def convert_bw(file_names,imgs):
    bw_fnames = []
    bw_imgs = []
    for n,img in enumerate(imgs):
        bw = 0.3*img[:,:,0]+0.59*img[:,:,1]+0.11*img[:,:,2]
        bw_imgs.append(bw)
        fname = file_names[n]
        fname_bw = fname.replace(path_in,path_out)
        bw_fnames.append(fname_bw)
        mi.imsave(fname,img)
        mi.imsave(fname_bw,bw)
    return bw_fnames,bw_imgs
        



    
        
        

fnames,imgs = get_files(path_in,pattern,filetype)
bw_fnames,bw_imgs = convert_bw(fnames,imgs)
