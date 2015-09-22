"""

References:

* This paper describes unary/pairwise features on superpixels, such
  as using different color histograms.
    Sungwoong Kim, Sebastian Nowozin, Pushmeet Kohli, Chang D. Yoo,
    "Task-Specific Image Partitioning",
    IEEE Transactions on Image Processing.
    http://www.nowozin.net/sebastian/papers/kim2012imagepartitioning.pdf

* SLIC superpixels:
    http://ivrg.epfl.ch/research/superpixels

* Downloads for this script:
    cd data
    wget https://documents.epfl.ch/groups/c/cv/cvlab-unit/www/data/%20ElectronMicroscopy_Hippocampus/volumedata.tif
    wget https://documents.epfl.ch/groups/c/cv/cvlab-unit/www/data/%20ElectronMicroscopy_Hippocampus/training.tif
    wget https://documents.epfl.ch/groups/c/cv/cvlab-unit/www/data/%20ElectronMicroscopy_Hippocampus/training_groundtruth.tif
    wget https://documents.epfl.ch/groups/c/cv/cvlab-unit/www/data/%20ElectronMicroscopy_Hippocampus/testing.tif
    wget https://documents.epfl.ch/groups/c/cv/cvlab-unit/www/data/%20ElectronMicroscopy_Hippocampus/testing_groundtruth.tif

* vlfeat
    http://www.vlfeat.org

* scikit.learn
    http://scikit-learn.org

* Mean-Shift:
    http://comaniciu.net

"""


from skimage.io import MultiImage
import numpy
import glob
import vigra
import h5py
import os, sys

def writeH5Block(fname):
    block = None
    d = MultiImage(fname)
    for i, frame in enumerate(d):
        print "%s: frame %d/%d" % (fname, i, len(d))
        if block is None:
            block = numpy.zeros((frame.shape[0], frame.shape[1], len(d)), dtype=numpy.uint8)
        block[:,:,i] = frame
    h5name = fname[0:-4]+".h5"
    print "saving as %s" % h5name
    f = h5py.File(h5name, 'w')
    f.create_dataset("volume/data", data=block.astype(numpy.uint8))
    f.close()
    return h5name

def writeH5Labels(globbing, fname):
    block = []
    for f in sorted(glob.glob(globbing)):
        print f
        img = vigra.impex.readImage(f).squeeze()
        img = img.T #FIXME
        print img.shape
        block.append(img[:,:,numpy.newaxis])
    block = numpy.concatenate(block, axis=2)
    block.shape = (1,) + block.shape + (1,)
    h5name = fname[0:-4]+".h5"

    f = h5py.File(h5name, 'w')
    f.create_dataset("volume/data", data=block.astype(numpy.uint16), compression="gzip")
    f.close()

def view(dset):
    from volumina.api import Viewer
    from PyQt4.QtGui import QApplication
    app = QApplication([])
    v = Viewer()
    if isinstance(dset, str):
        f = h5py.File(dset, 'r')
        d = f["volume/data"].value
        f.close()
        v.setWindowTitle(dset)
        v.addGrayscaleLayer(d, name="raw")
    elif isinstance(dset, numpy.ndarray):
        v.addGrayscaleLayer(dset, name="raw")
    else:
        raise RuntimeError("%r" % dset)
    v.showMaximized()
    app.exec_()

def tiff_to_hdf5():
    dsets = ["testing_groundtruth.tif", "testing.tif", "training_groundtruth.tif", "training.tif", "volumedata.tif"]
    for dset in dsets:
        fname = writeH5Block("data/"+dset)

def export_blocks():
    f = h5py.File("data/volumedata.h5")
    for i in range(4): 
        sl = numpy.s_[400+i*256:400+(i+1)*256, 900:1156, 600:728]
        print sl
        d = f["volume/data"][sl]
        di = vigra.sampling.resize(d.astype(numpy.float32), tuple([2*t for t in d.shape]), order=3).astype(numpy.uint8)

        g = h5py.File("data/block%02d.h5" % i, 'w')
        g.create_dataset("volume/data", data=di)
        g.close()

if __name__ == "__main__":
    ### the following will create .h5 files from the origin TIFF stack
    ### from the EPFL website (see download links above)

    tiff_to_hdf5()

    ### the following will write out the files block00.h5 to block03.h5

    export_blocks() 

    ### the following will show the .h5 dataset specified as first argument
    ### on the command line

    #view(sys.argv[1])

