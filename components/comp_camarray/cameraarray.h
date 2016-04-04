// Code to grab images from several SiSo framegrabber
// HCI 2013, W.Mischler
// wolfgang.mischler@iwr.uni-heidelberg.de
#ifndef _CAMERARRAY_H_
#define _CAMERARRAY_H_


#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>
#include <opencv/cxcore.h>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>

// SiSo stuff

#include "fgrab_struct.h"
#include "fgrab_prototyp.h"
#include "fgrab_define.h"
#include "gbe.h"
#include "gbe_error.h"

// opencv stuff

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace std;
using namespace cv;

namespace camerarray {

class calibration;

const int	H_CAMS	= 4;
	
enum ERR {
	ERROR_FG_INIT			= 1,
	ERROR_FG_ONLYONECAM,
	ERROR_FG_NOCAM,
	ERROR_FG_CAM,
	ERROR_FG_CAMCONNECT,
	ERROR_CAM_BITSNOTSUPPORTED,
	ERROR_CAM_ALLOCBUFFER,
	ERROR_CAM_FORMAT,
	ERROR_CAM_ACQRUNNING,
	ERROR_CAM_LOADFILEFAILED
};

enum {
	ACQ_IDLE		= 0,
	ACQ_SNAP,
	ACQ_CONT
};


//
//
// Class for Framegrabber
//
//

class SiSoGigECamera;

class Framegrabber {
public:
				Framegrabber(int inBoardNumber, string inConfig);
				~Framegrabber();

		int		GetParameter(int inParameter, int inPort);
		void	SetParameter(int inParameter, int inPort, int inValue);

				friend class SiSoGigECamera;
private:
				Framegrabber();

				Fg_Struct*					mHandle;
				struct BoardHandle*			mGBEHandle;
				string						mConfig;
				vector<SiSoGigECamera*>		mCams;
				unsigned int				mBoardNumber;
};


//
//
// Abstract Class for singleCamera
//
//

class Camera {
public:
			Mat						GetSnapshot();
			virtual Mat				GetImageFromBuffer(unsigned int inPos) = 0;

			virtual void			Acquire() = 0;							//	non blocking
			virtual void			Acquire(unsigned int inN) = 0;			//	non blocking
			virtual void			StopAcquire() = 0;
			void					Wait();
			virtual void			WaitToImage(unsigned int inPos) = 0;	//	block

			virtual unsigned int	GetAcqStatus() = 0;
			virtual unsigned int	GetCurrentImage() = 0;
			virtual unsigned int	GetCamNumber() {return(mCamNumber);};
			virtual			 int	GetBits()		{ return mBits; };

protected:
			Camera() : mCurrentImage(0), mAcqStatus(ACQ_IDLE), mImToGrab(0), mCamNumber(0), mAcquiredImages(0), mBits(8) {};
			~Camera() {};
			
			int						mCamNumber;

			unsigned int			mCurrentImage;
			unsigned int			mAcquiredImages;
			// acq
			unsigned int			mAcqStatus;
			unsigned int			mImToGrab;

			unsigned int			mBits;

private:
};



//
//
//		FileStream Camera
//
//


class FileStreamCamera : public Camera{
public:
									FileStreamCamera(const string& inConfig, unsigned int inCamNum = 0);
	

			virtual Mat				GetImageFromBuffer(unsigned int inPos);

			virtual void			Acquire();							//	non blocking
			virtual void			Acquire(unsigned int inN);			//	non blocking
			virtual void			StopAcquire();
			virtual void			WaitToImage(unsigned int inPos);	//	block

					void			ResetStreamPosition() { mCurrentImage = 0; mAcquiredImages = 0;};

			virtual unsigned int	GetAcqStatus();
			virtual unsigned int	GetCurrentImage();

			virtual unsigned int	GetCamNumber() {return(mVirtualCamNum);};

					void			SetVirtualCamNumber(unsigned int inNum) { mVirtualCamNum = inNum; };
			static	bool			readStringList( const string& filename, vector<string>& l, int& image, int& max);

protected:

private:
			FileStreamCamera()  {};
			~FileStreamCamera() {};

	string			mConfig;
	unsigned int	mVirtualCamNum;

	vector<string>	mFiles;

	int				mMaxFrame;
	int				mStartFrame;	
};


//
//
//	Class for calibrated SiSoGigECamera camera
//
//

class SiSoGigECamera : public Camera{
public:
			SiSoGigECamera(Framegrabber& inFG, int inCamNumber, int inNT);
			~SiSoGigECamera();

			void			UpdateCameraInfo();

			// acqisition
			Mat				GetSnapshot();
			Mat				GetImageFromBuffer(unsigned int inPos);

			void			Acquire();							//	non blocking
			void			Acquire(unsigned int inN);			//	non blocking
			void			StopAcquire();
			void			WaitToImage(unsigned int inPos);	//	block

			unsigned int	GetAcqStatus();
			unsigned int	GetCurrentImage();

			// getter functions

			unsigned int	GetNX()			{ return mNX; };
			unsigned int	GetNY()			{ return mNY; };
			unsigned int	GetNT()			{ return mNT; };
			unsigned int	GetOX()			{ return mOX; };
			unsigned int	GetOY()			{ return mOY; };
					 int	GetBits()		{ return mBits; };
			unsigned int	GetDataBytes()  { return mDataBytes; };
			unsigned int	GetTriggerMode(){ return mTriggerMode; };

			float			GetFramerate()		{ return mFramerate; };
			float			GetExposureTime()	{ return mExposureTime; };

			string			GetSerial() { return mSerialNumber; };
			string			GetModel()  { return mModelName; };

			// setter functions

			void			SetNXYT(unsigned int inNX, unsigned int inNY, unsigned int inNT, unsigned int inOX = 0, unsigned int inOY = 0);
			void			SetBits(unsigned int inBits);
			void			SetTriggerMode(unsigned int inMode);

			void			SetFramerate(float inFPS);
			void			SetExposureTime(float inEXP);

			void			PrintInformation();
private:
			SiSoGigECamera();
			SiSoGigECamera(const SiSoGigECamera& inCam);			

			// buffer
			void	AllocateBuffer();
			void	FreeBuffer();

			//helper
			unsigned int			GetGigE_Parameter(char* param1);
			float					GetGigE_ParameterFloat(char* param1);
			string					GetGigE_ParameterString(char* param1);
			void					SetGigE_Parameter(char* param1, int64_t ival1);
			void					SetGigE_Parameter(char* param1, float ival1);
			void					SetGigE_Parameter(char* param1, string ival1);

			Framegrabber&			mFG;
			struct CameraHandle*	mCamHandle;

			// camera paramters
			float					mExposureTime;
			float					mFramerate;
			unsigned int			mNX;
			unsigned int			mNY;
			unsigned int			mOX;
			unsigned int			mOY;
			unsigned int			mNT;
			unsigned int			mDataBytes;
			unsigned int			mTriggerMode;

			// camera info

			string					mSerialNumber;
			string					mManufacturerName;
			string					mModelName;

			// image buffer
			void*					mImageBuffer;
			unsigned int			mImageBufferHandle;
			int64_t					mBufferSize;

};


//
//
// Class for CameraArray
//
//

class CameraArray {
public:
		CameraArray(string inConfig, unsigned int inNT = 8, int NoOfFramegrabber = 0);		// load all cameras, with default settings
		CameraArray(string inConfig, unsigned int inNT, float inEXP, float inFPS, vector<int> inUsedFGs, vector<int> usedCameras);
		~CameraArray();

		unsigned int	GetNumberOfCameras() { return mCameras.size();};

		void			PrintConnectedCameras();
		void			SetFramerate(float inFPS);
		void			SetExposure(float inEXP);
		void			SetBits(unsigned int inBits);
		void			SetTriggerMode(unsigned int inMode);
		float			GetFramerate()	{ return (mFPS); };
		float			GetExposure()	{ return (mExp); };
		SiSoGigECamera*	GetCamera(unsigned int inNum) { return(mCameras[inNum]);}

		void			Acquire();
		void			Acquire(unsigned int inN);
		void			StopAcquire();
		void			Wait();
		void			WaitToImage(unsigned int inImg);
		unsigned int	GetStatus();
		Mat				GetImageFromBuffer(unsigned int inCam, unsigned int inImgIdx);

		void			saveCalibration(const string& inFileName = string());

private:
		CameraArray();


		float						mFPS;
		float						mExp;
		unsigned int				mBits;
		unsigned int				mTriggerMode;
		vector<Framegrabber*>		mFGs;
		vector<SiSoGigECamera*>		mCameras;

		string					mConfig;
		unsigned int			mNT;

		unsigned int			mStatus;
		unsigned int			mImagesToGrab;

};

}

#endif//_CAMERARRAY_H_
