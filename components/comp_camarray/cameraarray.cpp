// Code to grab images from several SiSo framegrabber
// HCI 2013, W.Mischler
// wolfgang.mischler@iwr.uni-heidelberg.de

#include <vector>
#include <iostream>

#include "cameraarray.h"

using namespace std;
using namespace cv;

namespace camerarray {

//
// Framegrabber
//

Framegrabber::Framegrabber(int inBoardNumber, string inConfig) 
	: mBoardNumber(inBoardNumber), mConfig( inConfig ) 
{
	int result;
	
	mHandle = Fg_Init("QuadAreaGray8.dll", mBoardNumber);

	if(mHandle == NULL)
		throw(ERROR_FG_INIT);

	result = Fg_loadConfig(mHandle, mConfig.c_str()); 

	if(result)
		throw(result);

	result = Gbe_initBoard(mBoardNumber, 0, &mGBEHandle);

	if(result)
		throw(result);
}

Framegrabber::~Framegrabber() {
	for(int i = 0; i < mCams.size(); i++) {
		delete mCams[i];
	}

	Gbe_freeBoard(mGBEHandle);
    Fg_FreeGrabber(mHandle);	
}

int Framegrabber::GetParameter(int inParameter, int inPort) {
	int		result;
	int64_t lval;
	
	result = Fg_getParameter(mHandle, inParameter,  &lval, inPort);
	if(result)
		throw(result);

	return lval;
}

void Framegrabber::SetParameter(int inParameter, int inPort, int inValue) {
	int		result;
	int64_t lval;
	
	lval = inValue;

	result = Fg_setParameter(mHandle, inParameter,  &lval, inPort);
	if(result)
		throw(result);
}

//
//
//		Camera
//
//

Mat Camera::GetSnapshot() {
	Acquire(1);
	Wait();
	return GetImageFromBuffer(0);
}

void Camera::Wait() {
	if(mAcqStatus == ACQ_SNAP)
		WaitToImage(mImToGrab);

	mImToGrab = 0;
}


//
//
//	FileStreamCamera
//
//
FileStreamCamera::FileStreamCamera(const string& inConfig, unsigned int inCamNum) : mVirtualCamNum(inCamNum), mConfig(inConfig), mMaxFrame(0), mStartFrame(0) {
	bool success;

	success = readStringList(mConfig, mFiles, mStartFrame, mMaxFrame);

	if(!success)
		throw(ERROR_CAM_LOADFILEFAILED);
}

bool	FileStreamCamera::readStringList( const string& filename, vector<string>& l, int& image, int& max) {
        l.clear();
        FileStorage fs( filename, FileStorage::READ);
        if( !fs.isOpened() )
            return false;
        FileNode n = fs.getFirstTopLevelNode();
        if( n.type() != FileNode::SEQ )
            return false;
        FileNodeIterator it = n.begin(), it_end = n.end();
        for( ; it != it_end; ++it )
            l.push_back((string)*it);
        cout<< "First file:\n " << l[0]  << endl;
		fs["Calibrate_StartFrame"] >> image;
		fs["Calibrate_MaxFrame"] >> max;
        return true;
}
				
Mat	FileStreamCamera::GetImageFromBuffer(unsigned int inPos) {
	Mat result, tmp;

	unsigned int idx;

	idx =  mCurrentImage - mAcquiredImages + inPos + mStartFrame;

    if( idx < (int) mMaxFrame && mVirtualCamNum < mFiles.size()) {
			char out[2048];
			sprintf_s(out, mFiles[mVirtualCamNum].c_str(), idx);
			try {
				cout << "reading to camera " << mVirtualCamNum << " : " << out << endl; 
				tmp = imread(out, CV_LOAD_IMAGE_COLOR);//CV_LOAD_IMAGE_UNCHANGED
			} catch(...) {
				throw(ERROR_CAM_LOADFILEFAILED);
			}
			cvtColor(tmp, result, CV_BGR2GRAY);
			// TODO set mBits according to result type
	} 

    return result;
}

void	FileStreamCamera::Acquire() {							//	non blocking
	return;
}

void	FileStreamCamera::Acquire(unsigned int inN) {			//	non blocking
	mCurrentImage	+= inN;
	mAcquiredImages = inN;
	return;
}

void	FileStreamCamera::StopAcquire() {
	return;
}

void	FileStreamCamera::WaitToImage(unsigned int inPos) {	//	block
	return;
}

unsigned int	FileStreamCamera::GetAcqStatus() {
	return(mAcqStatus);
}

unsigned int	FileStreamCamera::GetCurrentImage() {
	return(mCurrentImage);
}

//
//
//		SiSoGigECamera Camera
//
//

SiSoGigECamera::SiSoGigECamera(Framegrabber& inFG, int inCamNumber, int inNT) : mFG(inFG), mImageBuffer(NULL), mNT(inNT) {
	int result, NrOfCams;

	mCamNumber = inCamNumber;

	result = Gbe_scanNetwork(mFG.mGBEHandle,mCamNumber, 200);

	if(result)
		throw(result);

		// Get number of cameras connected to port mCamNumber
	NrOfCams = Gbe_getCameraCount(mFG.mGBEHandle, mCamNumber);
	if (NrOfCams > 1) 
		throw(ERROR_FG_ONLYONECAM);
			
	if (NrOfCams == 0) 
		throw(ERROR_FG_NOCAM);
				
		// Get first camera connected to port mCamNumber
	result = Gbe_getFirstCamera(mFG.mGBEHandle, mCamNumber, &mCamHandle);
	if(result)
		throw(ERROR_FG_CAM);

		// Connect to camera
	result = Gbe_connectCamera(mCamHandle);
	if(result)
		throw(ERROR_FG_CAMCONNECT);

	
	mOX = 0;
	mOY = 0;

	UpdateCameraInfo();
	
	mFG.mCams.push_back(this);

	AllocateBuffer();
}

SiSoGigECamera::~SiSoGigECamera() {
	for(int i = 0; i < mFG.mCams.size(); i++) {
		if(mFG.mCams[i] == this) 
			mFG.mCams.erase(mFG.mCams.begin() + i);
	}

	Gbe_stopAcquisition(mCamHandle);
	Gbe_disconnectCamera(mCamHandle);
	Gbe_freeCamera(mCamHandle);
}

void SiSoGigECamera::UpdateCameraInfo() {
			// Get camera info
		struct CameraInfo* caminfo = Gbe_getCameraInfo(mCamHandle);
				
		mSerialNumber.assign(caminfo->serial_number, 16);
		mManufacturerName.assign(caminfo->manufactor_name, 32);
		mModelName.assign(caminfo->model_name, 32);		

				// width 
		mNX = mFG.GetParameter(FG_WIDTH, mCamNumber);

		SetGigE_Parameter("Width",(int64_t)mNX);

				// height
		mNY = mFG.GetParameter(FG_HEIGHT, mCamNumber);

		SetGigE_Parameter("Height",(int64_t)mNY);
		
			// get framerate and exposure
		mExposureTime = GetGigE_ParameterFloat("ExposureTimeAbs");

		mFramerate = GetGigE_ParameterFloat("AcquisitionFrameRateAbs");

			// format
		string tmp;

		tmp = GetGigE_ParameterString("PixelFormat");
		if(tmp == "Mono8") {
			mBits = 8;
			mDataBytes = 1;
		} else if(tmp == "Mono12") {
			mBits = 12;
			mDataBytes = 2;
		} else if(tmp == "Mono16") {
			mBits = 16;
			mDataBytes = 2;
		}

		tmp = GetGigE_ParameterString("TriggerMode");
		if(tmp == "On") {
			mTriggerMode = 1;
		} else {
			mTriggerMode = 0;
		}
}

void SiSoGigECamera::AllocateBuffer() {

	mBufferSize	= mNT * mNX * mNY * mDataBytes;

	if(mImageBuffer)
		FreeBuffer();

    mImageBuffer = Fg_AllocMem(mFG.mHandle, mBufferSize, mNT, mCamNumber);
	if(mImageBuffer == NULL)
		throw(ERROR_CAM_ALLOCBUFFER);
/*
    for (it = 0; it < nt; it++) {
        buf2[it] = Fg_getImagePtr(acd1->fg1, it+1, ibuf);
		_RPT3(_CRT_WARN, "  buffer %03i @%p size 0x%x\n", it, buf2[it], ny*nx);
    }*/
}

void SiSoGigECamera::FreeBuffer() {
	Fg_FreeMem(mFG.mHandle, mCamNumber);
}
			// setter functions
void	SiSoGigECamera::SetNXYT(unsigned int inNX, unsigned int inNY, unsigned int inNT, unsigned int inOX, unsigned int inOY) {
	mNX = inNX;
	mNY = inNY;
	mNT = inNT;
	mOX = inOX;
	mOY = inOY;

				// width 
	mFG.SetParameter(FG_WIDTH, mCamNumber, mNX);
	SetGigE_Parameter("Width",(int64_t)mNX);
	SetGigE_Parameter("OffsetX",(int64_t)mOX);

				// height
	mFG.SetParameter(FG_HEIGHT, mCamNumber, mNY);
	SetGigE_Parameter("Height",(int64_t)mNY);
	SetGigE_Parameter("OffsetY",(int64_t)mOY);

	AllocateBuffer();
}

void	SiSoGigECamera::SetBits(unsigned int inBits) {
	switch(inBits) {
	case 8:		mBits = 8;
				mDataBytes = 1;
				SetGigE_Parameter("PixelFormat","Mono8");
				break;

	case 12:	mBits = 12;
				mDataBytes = 2;
				SetGigE_Parameter("PixelFormat","Mono12");
				break;

	default:	throw(ERROR_CAM_BITSNOTSUPPORTED);
	}
}

void	SiSoGigECamera::SetTriggerMode(unsigned int inMode) {
	if(inMode) {
		SetGigE_Parameter("TriggerMode","On");
	} else {
		SetGigE_Parameter("TriggerMode","Off");
	}
}

void	SiSoGigECamera::SetFramerate(float inFPS) {
	mFramerate = inFPS;
	SetGigE_Parameter("AcquisitionFrameRateAbs", mFramerate);
}

void	SiSoGigECamera::SetExposureTime(float inEXP) {
	mExposureTime = inEXP;
	SetGigE_Parameter("ExposureTimeAbs", mExposureTime);
}

// acq

void SiSoGigECamera::Acquire() {
	int result;

	if(GetAcqStatus() != ACQ_IDLE)
		throw(ERROR_CAM_ACQRUNNING);

	mAcqStatus = ACQ_CONT;

	result = Gbe_startAcquisition(mCamHandle);
	if (result < 0) 
		throw(result);

	result = Fg_Acquire(mFG.mHandle, mCamNumber, GRAB_INFINITE);
	if (result < 0) 
		throw(result);
	
}

void SiSoGigECamera::Acquire(unsigned int inN) {
	int result;

	if(GetAcqStatus() != ACQ_IDLE)
		throw(ERROR_CAM_ACQRUNNING);

	mImToGrab  = inN;
	mAcqStatus = ACQ_SNAP;

	result = Gbe_startAcquisition(mCamHandle);
	if (result < 0) 
		throw(result);

	result = Fg_Acquire(mFG.mHandle, mCamNumber, mImToGrab);
	if (result < 0) 
		throw(result);
}

void SiSoGigECamera::StopAcquire() {
	int result;

	result = Fg_stopAcquire(mFG.mHandle, mCamNumber);
	if (result < 0) 
		throw(result);

	mAcqStatus = ACQ_IDLE;
	mImToGrab  = 0;

	GetCurrentImage();
}


Mat SiSoGigECamera::GetImageFromBuffer(unsigned int inPos) {
	if(mDataBytes == 1)
		return Mat(mNY, mNX, DataType<unsigned char>::type, Fg_getImagePtr(mFG.mHandle, inPos+1, mCamNumber));
	else if(mDataBytes == 2)
		return Mat(mNY, mNX, DataType<unsigned short>::type, Fg_getImagePtr(mFG.mHandle, inPos+1, mCamNumber));
	else
		throw(ERROR_CAM_FORMAT);
}


unsigned int	SiSoGigECamera::GetAcqStatus() {
	frameindex_t result;
	
		// see if eventual ACQ_SNAP is finished
	result = Fg_getStatus(mFG.mHandle, GRAB_ACTIVE, 0, mCamNumber);
	if (result < 0) 
		throw(result);
	
	if(result == 0)
		mAcqStatus = ACQ_IDLE;
	// otherwise mAcqStatus is still valid

	return mAcqStatus;
}

unsigned int SiSoGigECamera::GetCurrentImage() {
	frameindex_t idx;

	idx = Fg_getLastPicNumber(mFG.mHandle, mCamNumber);
	if (idx < 0) 
		throw(idx);

	mCurrentImage = idx;
	mAcquiredImages = mCurrentImage;

	return mCurrentImage;
}

void SiSoGigECamera::WaitToImage(unsigned int inPos) {
	frameindex_t idx;

	idx = Fg_getLastPicNumberBlocking(mFG.mHandle, inPos, mCamNumber, 10);
	if (idx < 0) 
		throw(idx);

	mAcqStatus = ACQ_IDLE;

	GetCurrentImage();
}

// helper

unsigned int SiSoGigECamera::GetGigE_Parameter(char* param1) {
	int64_t ival1;
	int result = Gbe_getIntegerValue(mCamHandle, param1, &ival1);
	if (result < 0) 
		throw(result);
		
	return ival1;
}

float SiSoGigECamera::GetGigE_ParameterFloat(char* param1) {
	double ival1;
	int result = Gbe_getFloatValue(mCamHandle, param1, &ival1);
	if (result < 0) 
		throw(result);

	return ival1;
}

string SiSoGigECamera::GetGigE_ParameterString(char* param1) {
	const char* ival1;

	int result = Gbe_getEnumerationValue(mCamHandle, param1, &ival1);
	if (result < 0) 
		throw(result);

	return string(ival1);
}

void SiSoGigECamera::SetGigE_Parameter(char* param1, int64_t ival) {
	/*
	//variant B: adjust value to valid value
	int64_t min,max,inc,temp;
	int result;

	result = Gbe_getIntegerValueLimits(ch1, param1, &min, &max, &inc);
	if (result < 0) {
		const char* sErr = Gbe_getErrorDescription(result);
		xDebugTextOut("GigE error setting parameter %s to %lli: %s", param1, ival, sErr);
		return 1;
	}
	
	temp = ival;

	// loose error handling
	if(ival < min) ival = min;
	if(ival > max) ival = max;
	ival = (ival + inc/2) - (ival + inc/2)%inc; // round
	
	if(temp < min || temp > max || temp%inc) 
		xDebugTextOut("changed value from %i to %i!", temp, ival);
		*/
	
	int result = Gbe_setIntegerValue(mCamHandle, param1, ival);
	if (result < 0) 
		throw(result);
}

void SiSoGigECamera::SetGigE_Parameter(char* param1, float ival) {
	/*
	//variant B: adjust value to valid value
	int64_t min,max,inc,temp;
	int result;

	result = Gbe_getIntegerValueLimits(ch1, param1, &min, &max, &inc);
	if (result < 0) {
		const char* sErr = Gbe_getErrorDescription(result);
		xDebugTextOut("GigE error setting parameter %s to %lli: %s", param1, ival, sErr);
		return 1;
	}
	
	temp = ival;

	// loose error handling
	if(ival < min) ival = min;
	if(ival > max) ival = max;
	ival = (ival + inc/2) - (ival + inc/2)%inc; // round
	
	if(temp < min || temp > max || temp%inc) 
		xDebugTextOut("changed value from %i to %i!", temp, ival);
		*/

	int result = Gbe_setFloatValue(mCamHandle, param1, ival);
	if (result < 0) 
		throw(result);
}

void SiSoGigECamera::SetGigE_Parameter(char* param1, string ival) {

	int result = Gbe_setEnumerationValue(mCamHandle, param1, ival.c_str());
	if (result < 0) 
		throw(result);
}

void SiSoGigECamera::PrintInformation() {
	cout << "Camera " << mCamNumber << " on Board " << mFG.mBoardNumber << endl;
	cout << "Serial:    " << mSerialNumber << endl;
	cout << "Exposure:  " << mExposureTime/1000.0 << "ms" << endl; 
	cout << "Framerate: " << mFramerate << "Hz" << endl; 
}


//
//
//		CameraArray
//
//


CameraArray::CameraArray(string inConfig, unsigned int inNT, int NoOfFramegrabber) : mConfig(inConfig), mNT(inNT), mStatus(ACQ_IDLE),	mImagesToGrab(0), mBits(8) {
	int i;

	/*********************************************************************************************/
	// load all framegrabbers
	/*********************************************************************************************/
	std::cout << "Load all framegrabbers" << std::endl;
	i = 0;
	try {
		while (i < NoOfFramegrabber) {
			
			Framegrabber* fg = new Framegrabber(i, mConfig.c_str());
			cout << "Load Board: " << i << endl;
			mFGs.push_back(fg);
			i++;
		}
		
	} 
	catch(ERR err) {
		cout << "Number of Boards loaded: " << i;
	} 
	catch(int err) {
		cout << "Error " << err << endl;
	}
	std::cout << " ---->   Done!" << std::endl;
	/*********************************************************************************************/
	/*********************************************************************************************/
	/*********************************************************************************************/

	/*********************************************************************************************/
	// load all cameras of framegrabber
	/*********************************************************************************************/
	std::cout << "Load all cameras" << std::endl;
	for(int i = 0; i < mFGs.size(); i++) {
		try {
			for(int i_cam = 0; i_cam < H_CAMS; i_cam++) {
				std::cout << "Load camera:" << i_cam << std::endl;
				SiSoGigECamera* cam = new SiSoGigECamera(*mFGs[i], i_cam, mNT);
				mCameras.push_back(cam);
			}
		} catch(ERR err) {
			cout << "Error allocating camera " << i << ": " << err << endl;
		} catch(int err) {
			cout << "Error " << err << endl;
		}
	}
	cout << "Loaded " << mCameras.size() << " cameras" << endl;

	// set all cameras to exp, fps of first camera

	mExp	= mCameras[0]->GetExposureTime();
	mFPS	= mCameras[0]->GetFramerate();

	SetExposure(mExp);
	SetFramerate(mFPS);
	SetBits(mBits);
}

CameraArray::CameraArray(string inConfig, unsigned int inNT, float inEXP, float inFPS, vector<int> inUsedFGs, vector<int> usedCameras) 
	: mFPS(inFPS), mExp(inEXP), mConfig(inConfig), mNT(inNT), mStatus(ACQ_IDLE),	mImagesToGrab(0), mBits(8) 
{
	int i;

	std::cout << "load all framegrabbers";
	
	i = 0;

	mFGs.resize(inUsedFGs.size());

	try {
		for(int i = 0; i < inUsedFGs.size(); i++) {
			Framegrabber* fg = new Framegrabber(inUsedFGs[i], mConfig.c_str());
			mFGs[i] = fg;
		}
	} catch(ERR err) {
		cout << "Number of Boards loaded: " << i << endl;
	} catch(int err) {
		cout << "Error " << err << endl;
	}

	std::cout << "---->   Done!" << std::endl;

	// load all cameras
	for(int i = 0; i < mFGs.size(); i++) {
		try {
			for(int i_cam = 0; i_cam < usedCameras.size(); i_cam++) {
				SiSoGigECamera* cam = new SiSoGigECamera(*mFGs[i], usedCameras[i_cam], mNT);
				mCameras.push_back(cam);
				cam->SetExposureTime(mExp);
				cam->SetFramerate(mFPS);
			}
		} catch(ERR err) {
			cout << "Error allocating camera: " << i << endl;
		} catch(int err) {
			cout << "Error " << err << endl;
		}
	}
}


CameraArray::~CameraArray() {
	for(int i = 0; i < mFGs.size(); i++) {
		delete mFGs[i];
	}
	// cameras are cleand up through framegrabber destructor
}

void	CameraArray::SetExposure(float inExp) {
	mExp = inExp;

	for(int i = 0; i < mCameras.size(); i++) {
		mCameras[i]->SetExposureTime(mExp);
	}
}

void	CameraArray::SetFramerate(float inFPS) {
	mFPS = inFPS;

	for(int i = 0; i < mCameras.size(); i++) {
		mCameras[i]->SetFramerate(mFPS);
	}
}

void	CameraArray::SetBits(unsigned int inBits) {
	mBits = inBits;

	for(int i = 0; i < mCameras.size(); i++) {
		mCameras[i]->SetBits(mBits);
	}
}

void	CameraArray::SetTriggerMode(unsigned int inMode) {
	mTriggerMode = inMode;

	for(int i = 0; i < mCameras.size(); i++) {
		mCameras[i]->SetTriggerMode(mTriggerMode);
	}
}

void	CameraArray::PrintConnectedCameras() {
	for(int i = 0; i < mCameras.size(); i++) {
		mCameras[i]->PrintInformation();
	}
}


void	CameraArray::Acquire() {
	mStatus = ACQ_CONT;

	for(int i = 0; i < mCameras.size(); i++) {
		mCameras[i]->Acquire();
	}
}

void	CameraArray::Acquire(unsigned int inN) {
	mStatus			= ACQ_SNAP;
	mImagesToGrab	= inN;

	for(int i = 0; i < mCameras.size(); i++) {
		mCameras[i]->Acquire(mImagesToGrab);
	}
}

void	CameraArray::StopAcquire() {
	mStatus = ACQ_IDLE;

	for(int i = 0; i < mCameras.size(); i++) {
		mCameras[i]->StopAcquire();
	}
}

void	CameraArray::Wait() {
	for(int i = 0; i < mCameras.size(); i++) {
		mCameras[i]->Wait();
	}
}

void	CameraArray::WaitToImage(unsigned int inImg) {
	for(int i = 0; i < mCameras.size(); i++) {
		mCameras[i]->WaitToImage(inImg);
	}
}

unsigned int CameraArray::GetStatus() {
	unsigned int out;

	for(int i = 0; i < mCameras.size(); i++) {
		out |= mCameras[i]->GetAcqStatus();
	}

	return out;
}

Mat CameraArray::GetImageFromBuffer(unsigned int inCam, unsigned int inImgIdx) {
	return mCameras[inCam]->GetImageFromBuffer(inImgIdx);
}


}
