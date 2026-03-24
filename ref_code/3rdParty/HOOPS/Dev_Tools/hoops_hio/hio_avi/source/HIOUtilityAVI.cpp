//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hio_avi/source/HIOUtilityAVI.cpp,v 1.8 2010-10-21 23:40:40 reuben Exp $
//

#include <windows.h>
#include <stdlib.h>
#include <vfw.h>
#include <float.h>

#include "HUtilityLocaleString.h"
#include "HBhvBehaviorManager.h"
#include "HBaseView.h"
#include "HBaseModel.h"
#include "HIOUtilityAVI.h"

// AVI utilities -- for creating avi files
// (c) 2002 Lucian Wischik. No restrictions on use.

// First, we'll define the WAV file format.
#include <pshpack1.h>

typedef struct{
	char id[4];         //="fmt "
	unsigned long size; //=16
	short wFormatTag;   //=WAVE_FORMAT_PCM=1
	unsigned short wChannels;       //=1 or 2 for mono or stereo
	unsigned long dwSamplesPerSec;  //=11025 or 22050 or 44100
	unsigned long dwAvgBytesPerSec; //=wBlockAlign * dwSamplesPerSec
	unsigned short wBlockAlign;     //=wChannels * (wBitsPerSample==8?1:2)
	unsigned short wBitsPerSample;  //=8 or 16, for bits per sample
} FmtChunk;

typedef struct
{
	char id[4];            //="data"
	unsigned long size;    //=datsize, size of the following array
	unsigned char data[1]; //=the raw data goes here
} DataChunk;

typedef struct
{ 
	char id[4];         //="RIFF"
	unsigned long size; //=datsize+8+16+4
	char type[4];       //="WAVE"
	FmtChunk fmt;
	DataChunk dat;
} WavChunk;

#include <poppack.h>

// This is the internal structure represented by the HAVI handle:
typedef struct
{
	IAVIFile *pfile;    // created by CreateAvi
	WAVEFORMATEX wfx;   // as given to CreateAvi (.nChanels=0 if none was given). Used when audio stream is first created.
	int period;         // specified in CreateAvi, used when the video stream is first created
	IAVIStream *as;     // audio stream, initialised when audio stream is first created
	IAVIStream *ps, *psCompressed;  // video stream, when first created
	unsigned long nframe, nsamp;    // which frame will be added next, which sample will be added next
	bool iserr;         // if true, then no function will do anything
} TAviUtil;


static TAviUtil * CreateAvi(const wchar_t *fn, int frameperiod, const WAVEFORMATEX *wfx)
{
	IAVIFile *pfile;
	AVIFileInit();
	HRESULT hr = AVIFileOpenW(&pfile, (fn), OF_WRITE|OF_CREATE, NULL);
	if (hr!=AVIERR_OK) {
		AVIFileExit();
		return NULL;
	}

	TAviUtil *au = new TAviUtil;
	au->pfile = pfile;
	if (wfx==NULL) ZeroMemory(&au->wfx,sizeof(WAVEFORMATEX)); else CopyMemory(&au->wfx,wfx,sizeof(WAVEFORMATEX));
	au->period = frameperiod;
	au->as=0; au->ps=0; au->psCompressed=0;
	au->nframe=0; au->nsamp=0;
	au->iserr=false;
	return au;
}

static HRESULT CloseAvi(TAviUtil * avi)
{
	if (avi==NULL)
		return AVIERR_BADHANDLE;
	
	TAviUtil *au = (TAviUtil*)avi;
	
	if (au->as!=0)
		AVIStreamRelease(au->as); 
	au->as=0;
	
	if (au->psCompressed!=0) 
		AVIStreamRelease(au->psCompressed); 
	au->psCompressed=0;
	
	if (au->ps!=0) 
		AVIStreamRelease(au->ps); 
	au->ps=0;
	
	if (au->pfile!=0) 
		AVIFileRelease(au->pfile); 
	au->pfile=0;

	AVIFileExit();

	delete au;

	return S_OK;
}


static HRESULT SetAviVideoCompression(TAviUtil * avi, HBITMAP hbm, AVICOMPRESSOPTIONS *opts, bool ShowDialog, HWND hparent)
{
	if (avi==NULL)
		return AVIERR_BADHANDLE;
	
	if (hbm==NULL)
		return AVIERR_BADPARAM;
	
	DIBSECTION dibs;
	int sbm = GetObject(hbm,sizeof(dibs),&dibs);
	if (sbm!=sizeof(DIBSECTION))
		return AVIERR_BADPARAM;
	
	TAviUtil *au = (TAviUtil*)avi;
	if (au->iserr)
		return AVIERR_ERROR;
	
	if (au->psCompressed!=0)
		return AVIERR_COMPRESSOR;
	//
	if (au->ps==0) // create the stream, if it wasn't there before
	{ 
		AVISTREAMINFO strhdr; ZeroMemory(&strhdr,sizeof(strhdr));
		strhdr.fccType = streamtypeVIDEO;// stream type
		strhdr.fccHandler = 0; 
		strhdr.dwScale = au->period;
		strhdr.dwRate = 1000;
		strhdr.dwSuggestedBufferSize  = dibs.dsBmih.biSizeImage;
		SetRect(&strhdr.rcFrame, 0, 0, dibs.dsBmih.biWidth, dibs.dsBmih.biHeight);
		HRESULT hr=AVIFileCreateStream(au->pfile, &au->ps, &strhdr);
		if (hr!=AVIERR_OK){
			au->iserr=true;
			return hr;
		}
	}
	//
	if (au->psCompressed==0) // set the compression, prompting dialog if necessary
	{
		AVICOMPRESSOPTIONS myopts;
		ZeroMemory(&myopts, sizeof(myopts));

		AVICOMPRESSOPTIONS *aopts;
		if (opts != NULL)
			aopts = opts;
		else
			aopts = &myopts;

		if (ShowDialog){
			BOOL res = (BOOL)AVISaveOptions(hparent,0,1,&au->ps, &aopts);
			if (!res) {
				AVISaveOptionsFree(1, &aopts); 
				au->iserr=true; 
				return AVIERR_USERABORT;
			}
		}
		else {
			aopts->fccHandler = mmioFOURCC('D','I','B',' ');
			aopts->dwFlags = AVICOMPRESSF_VALID;
		}

		HRESULT hr = AVIMakeCompressedStream(&au->psCompressed, au->ps, aopts, NULL);
		AVISaveOptionsFree(1, &aopts);
		if (hr != AVIERR_OK) {
			au->iserr = true;
			return hr;
		}

		DIBSECTION dibs;
		GetObject(hbm,sizeof(dibs),&dibs);
		hr = AVIStreamSetFormat(au->psCompressed, 0, &dibs.dsBmih, dibs.dsBmih.biSize + dibs.dsBmih.biClrUsed * sizeof(RGBQUAD));
		if (hr != AVIERR_OK) {
			au->iserr = true;
			return hr;
		}
	}
	//
	return AVIERR_OK;
}


static HRESULT AddAviFrame(TAviUtil * avi, HBITMAP hbm)
{
	if (avi==NULL) 
		return AVIERR_BADHANDLE;
	
	if (hbm==NULL) 
		return AVIERR_BADPARAM;
	
	DIBSECTION dibs; 
	int sbm = GetObject(hbm,sizeof(dibs),&dibs);
	if (sbm!=sizeof(DIBSECTION)) 
		return AVIERR_BADPARAM;

	TAviUtil *au = (TAviUtil*)avi;

	if (au->iserr) 
		return AVIERR_ERROR;
	//
	if (au->ps==0) // create the stream, if it wasn't there before
	{ 
		AVISTREAMINFO strhdr; ZeroMemory(&strhdr,sizeof(strhdr));
		strhdr.fccType = streamtypeVIDEO;// stream type
		strhdr.fccHandler = 0; 
		strhdr.dwScale = au->period;
		strhdr.dwRate = 1000;
		strhdr.dwSuggestedBufferSize  = dibs.dsBmih.biSizeImage;
		SetRect(&strhdr.rcFrame, 0, 0, dibs.dsBmih.biWidth, dibs.dsBmih.biHeight);
		HRESULT hr=AVIFileCreateStream(au->pfile, &au->ps, &strhdr);
		if (hr!=AVIERR_OK) {
			au->iserr=true; 
			return hr;
		}
	}
	//
	// create an empty compression, if the user hasn't set any
	if (au->psCompressed==0)
	{
		AVICOMPRESSOPTIONS opts; ZeroMemory(&opts,sizeof(opts));
		opts.fccHandler=mmioFOURCC('D','I','B',' '); 
		HRESULT hr = AVIMakeCompressedStream(&au->psCompressed, au->ps, &opts, NULL);
		if (hr != AVIERR_OK) {
			au->iserr=true;
			return hr;
		}
		hr = AVIStreamSetFormat(au->psCompressed, 0, &dibs.dsBmih, dibs.dsBmih.biSize+dibs.dsBmih.biClrUsed*sizeof(RGBQUAD));
		if (hr!=AVIERR_OK) {
			au->iserr=true;
			return hr;
		}
	}
	//
	//Now we can add the frame
	HRESULT hr = AVIStreamWrite(au->psCompressed, au->nframe, 1, dibs.dsBm.bmBits, dibs.dsBmih.biSizeImage, AVIIF_KEYFRAME, NULL, NULL);
	if (hr!=AVIERR_OK) {
		au->iserr=true; 
		return hr;
	}
	au->nframe++; 
	return S_OK;
}

#if 0
static HRESULT AddAviAudio(TAviUtil * avi, void *dat, unsigned long numbytes)
{ if (avi==NULL) return AVIERR_BADHANDLE;
if (dat==NULL || numbytes==0) return AVIERR_BADPARAM;
TAviUtil *au = (TAviUtil*)avi;
if (au->iserr) return AVIERR_ERROR;
if (au->wfx.nChannels==0) return AVIERR_BADFORMAT;
unsigned long numsamps = numbytes*8 / au->wfx.wBitsPerSample;
if ((numsamps*au->wfx.wBitsPerSample/8)!=numbytes) return AVIERR_BADPARAM;
//
if (au->as==0) // create the stream if necessary
{ AVISTREAMINFO ahdr; ZeroMemory(&ahdr,sizeof(ahdr));
ahdr.fccType=streamtypeAUDIO;
ahdr.dwScale=au->wfx.nBlockAlign;
ahdr.dwRate=au->wfx.nSamplesPerSec*au->wfx.nBlockAlign; 
ahdr.dwSampleSize=au->wfx.nBlockAlign;
ahdr.dwQuality=(DWORD)-1;
HRESULT hr = AVIFileCreateStream(au->pfile, &au->as, &ahdr);
if (hr!=AVIERR_OK) {au->iserr=true; return hr;}
hr = AVIStreamSetFormat(au->as,0,&au->wfx,sizeof(WAVEFORMATEX));
if (hr!=AVIERR_OK) {au->iserr=true; return hr;}
}
//
// now we can write the data
HRESULT hr = AVIStreamWrite(au->as,au->nsamp,numsamps,dat,numbytes,0,NULL,NULL);
if (hr!=AVIERR_OK) {au->iserr=true; return hr;}
au->nsamp+=numsamps; return S_OK;
}

static HRESULT AddAviWav(TAviUtil * avi, const char *src, DWORD flags)
{ if (avi==NULL) return AVIERR_BADHANDLE;
if (flags!=SND_MEMORY && flags!=SND_FILENAME) return AVIERR_BADFLAGS;
if (src==0) return AVIERR_BADPARAM;
TAviUtil *au = (TAviUtil*)avi;
if (au->iserr) return AVIERR_ERROR;
//
char *buf=0; WavChunk *wav = (WavChunk*)src;
if (flags==SND_FILENAME)
{ HANDLE hf=CreateFile(H_TEXT(src),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
if (hf==INVALID_HANDLE_VALUE) {au->iserr=true; return AVIERR_FILEOPEN;}
DWORD size = GetFileSize(hf,NULL);
buf = new char[size];
DWORD red; ReadFile(hf,buf,size,&red,NULL);
CloseHandle(hf);
wav = (WavChunk*)buf;
}
//
// check that format doesn't clash
bool badformat=false;
if (au->wfx.nChannels==0)
{ au->wfx.wFormatTag=wav->fmt.wFormatTag;
au->wfx.cbSize=0;
au->wfx.nAvgBytesPerSec=wav->fmt.dwAvgBytesPerSec;
au->wfx.nBlockAlign=wav->fmt.wBlockAlign;
au->wfx.nChannels=wav->fmt.wChannels;
au->wfx.nSamplesPerSec=wav->fmt.dwSamplesPerSec;
au->wfx.wBitsPerSample=wav->fmt.wBitsPerSample;
}
else
{ if (au->wfx.wFormatTag!=wav->fmt.wFormatTag) badformat=true;
if (au->wfx.nAvgBytesPerSec!=wav->fmt.dwAvgBytesPerSec) badformat=true;
if (au->wfx.nBlockAlign!=wav->fmt.wBlockAlign) badformat=true;
if (au->wfx.nChannels!=wav->fmt.wChannels) badformat=true;
if (au->wfx.nSamplesPerSec!=wav->fmt.dwSamplesPerSec) badformat=true;
if (au->wfx.wBitsPerSample!=wav->fmt.wBitsPerSample) badformat=true;
}
if (badformat) {if (buf!=0) delete[] buf; return AVIERR_BADFORMAT;}
//
if (au->as==0) // create the stream if necessary
{ AVISTREAMINFO ahdr; ZeroMemory(&ahdr,sizeof(ahdr));
ahdr.fccType=streamtypeAUDIO;
ahdr.dwScale=au->wfx.nBlockAlign;
ahdr.dwRate=au->wfx.nSamplesPerSec*au->wfx.nBlockAlign; 
ahdr.dwSampleSize=au->wfx.nBlockAlign;
ahdr.dwQuality=(DWORD)-1;
HRESULT hr = AVIFileCreateStream(au->pfile, &au->as, &ahdr);
if (hr!=AVIERR_OK) {if (buf!=0) delete[] buf; au->iserr=true; return hr;}
hr = AVIStreamSetFormat(au->as,0,&au->wfx,sizeof(WAVEFORMATEX));
if (hr!=AVIERR_OK) {if (buf!=0) delete[] buf; au->iserr=true; return hr;}
}
//
// now we can write the data
unsigned long numbytes = wav->dat.size;
unsigned long numsamps = numbytes*8 / au->wfx.wBitsPerSample;
HRESULT hr = AVIStreamWrite(au->as,au->nsamp,numsamps,wav->dat.data,numbytes,0,NULL,NULL);
if (buf!=0) delete[] buf;
if (hr!=AVIERR_OK) {au->iserr=true; return hr;}
au->nsamp+=numsamps; return S_OK;
}

static unsigned int FormatAviMessage(HRESULT code, char *buf,unsigned int len)
{ const char *msg="unknown avi result code";
switch (code)
{ case S_OK: msg="Success"; break;
case AVIERR_BADFORMAT: msg="AVIERR_BADFORMAT: corrupt file or unrecognized format"; break;
case AVIERR_MEMORY: msg="AVIERR_MEMORY: insufficient memory"; break;
case AVIERR_FILEREAD: msg="AVIERR_FILEREAD: disk error while reading file"; break;
case AVIERR_FILEOPEN: msg="AVIERR_FILEOPEN: disk error while opening file"; break;
case REGDB_E_CLASSNOTREG: msg="REGDB_E_CLASSNOTREG: file type not recognised"; break;
case AVIERR_READONLY: msg="AVIERR_READONLY: file is read-only"; break;
case AVIERR_NOCOMPRESSOR: msg="AVIERR_NOCOMPRESSOR: a suitable compressor could not be found"; break;
case AVIERR_UNSUPPORTED: msg="AVIERR_UNSUPPORTED: compression is not supported for this type of data"; break;
case AVIERR_INTERNAL: msg="AVIERR_INTERNAL: internal error"; break;
case AVIERR_BADFLAGS: msg="AVIERR_BADFLAGS"; break;
case AVIERR_BADPARAM: msg="AVIERR_BADPARAM"; break;
case AVIERR_BADSIZE: msg="AVIERR_BADSIZE"; break;
case AVIERR_BADHANDLE: msg="AVIERR_BADHANDLE"; break;
case AVIERR_FILEWRITE: msg="AVIERR_FILEWRITE: disk error while writing file"; break;
case AVIERR_COMPRESSOR: msg="AVIERR_COMPRESSOR"; break;
case AVIERR_NODATA: msg="AVIERR_READONLY"; break;
case AVIERR_BUFFERTOOSMALL: msg="AVIERR_BUFFERTOOSMALL"; break;
case AVIERR_CANTCOMPRESS: msg="AVIERR_CANTCOMPRESS"; break;
case AVIERR_USERABORT: msg="AVIERR_USERABORT"; break;
case AVIERR_ERROR: msg="AVIERR_ERROR"; break;
}
unsigned int mlen=(unsigned int)strlen(msg);
if (buf==0 || len==0) return mlen;
unsigned int n=mlen; if (n+1>len) n=len-1;
strncpy(buf,msg,n); buf[n]=0;
return mlen;
}
#endif

#include "HUtilityAnnotation.h"

#define Debug_USE_WINDOW_IS_IMAGE	0x100000
#define Debug_FORCE_SOFTWARE		0x01000000
static void WriteAVI(const wchar_t *aviname, int width, int height, int resolution, int starttick, int endtick, HBaseView *pView)
{
	HBhvBehaviorManager *pBehaviorManager = pView->GetModel()->GetBhvBehaviorManager();

	HDC hdcscreen=::GetDC(0), hdc=CreateCompatibleDC(hdcscreen); ::ReleaseDC(0,hdcscreen);
	BITMAPINFO bi;
	ZeroMemory(&bi,sizeof(bi));
	BITMAPINFOHEADER &bih = bi.bmiHeader;
	bih.biSize=sizeof(bih);
	bih.biWidth=width;
	bih.biHeight=height;
	bih.biPlanes=1;
	bih.biBitCount=24;
	bih.biCompression=BI_RGB;
	bih.biSizeImage = ((bih.biWidth*bih.biBitCount/8+3)&0xFFFFFFFC)*bih.biHeight;
	bih.biXPelsPerMeter=10000;
	bih.biYPelsPerMeter=10000;
	bih.biClrUsed=0;
	bih.biClrImportant=0;

	void *bits = 0; 
	HBITMAP hbm=CreateDIBSection(hdc,(BITMAPINFO*)&bih,DIB_RGB_COLORS,&bits,NULL,NULL);
	char *avi_image = (char*)bits;

	TAviUtil * avi = CreateAvi(aviname,resolution,NULL);
	AVICOMPRESSOPTIONS opts;
	ZeroMemory(&opts, sizeof(opts));
	opts.fccHandler=mmioFOURCC('d','i','v','x');
	SetAviVideoCompression(avi,hbm,&opts,true,(HWND)pView->GetWindowHandle());

	pBehaviorManager->SetStartTime(0);
	pBehaviorManager->ScheduleAllAnimations(true);

	float startframe,endframe;
	startframe = 1.0f/pBehaviorManager->GetTicksPerSecond() * starttick;
	endframe = 1.0f/pBehaviorManager->GetTicksPerSecond() * endtick;
	int numframes = (endframe-startframe)*1000.0f/resolution;

	HC_KEY image_seg_key = INVALID_KEY, image_key = INVALID_KEY;
	HC_Open_Segment("/");{
		image_seg_key = HC_KOpen_Segment("");{
			image_key = HC_KInsert_Image(0, 0, 0, "rgba", width, height, 0);
		}HC_Close_Segment();
	}HC_Close_Segment();

	char const * hoops_image = 0;
	HC_Show_Geometry_Pointer(image_key, "rgba rasters", &hoops_image);

	/* first find out the relevant options associated with the view */
	H_FORMAT_TEXT rendering_options;    
	HC_Open_Segment_By_Key(pView->GetViewKey());{
		HRenderMode rndrmode = pView->GetRenderMode();
		if (rndrmode == HRenderHiddenLine || rndrmode == HRenderHiddenLineFast) {
			char hlr_options[200] = {""};
			HC_Show_One_Net_Rendering_Optio("hidden line removal options", hlr_options);
			rendering_options = H_FORMAT_TEXT("hsra = hidden line, hidden line removal options = (%s)", hlr_options);
		}
	}HC_Close_Segment();

	HBestImageDriver driver;
	// prepare data to render
	HC_Open_Segment(driver);{

		HC_Set_Window_Frame("off");
		HC_Set_Rendering_Options(rendering_options);

		int const res = 72;

		HC_Set_Driver_Options( H_FORMAT_TEXT(
			"isolated, "
			"no gamma correction, "
			"use window id = %s%p, "
			"subscreen = (-1, 1, -1, 1), "
			"physical size = (%f, %f), "
			"hardcopy resolution = %d",
			H_EXTRA_POINTER_FORMAT, (void*)image_key,
			2.54 * width / (float)res, 2.54 * height / (float)res,
			res));

		HPoint WindowColorTop, WindowColorBottom;
		pView->GetWindowColor(WindowColorTop, WindowColorBottom);

		HC_Set_Color(H_FORMAT_TEXT("windows=(r=%f g=%f b=%f), window contrast = (r=%f g=%f b=%f)", 
			WindowColorTop.x, WindowColorTop.y, WindowColorTop.z,
			WindowColorBottom.x, WindowColorBottom.y, WindowColorBottom.z));

		HC_Set_Window_Pattern("Down");

		HC_KEY include_key = HC_KInclude_Segment_By_Key (pView->GetSceneKey());
		HC_KEY include_key_path[] = {pView->GetIncludeLinkKey(), include_key} ;
		HUtilityAnnotation::recursive_resize(
			pView->GetModelKey(), 
			2, include_key_path, 
			driver.GetKey());
		HC_KEY markup_key;
		HC_Open_Segment_By_Key(pView->GetOverwriteKey());
			markup_key=HC_KCreate_Segment("markup");
		HC_Close_Segment();
		HUtilityAnnotation::recursive_resize(markup_key, 1, &include_key, driver.GetKey());

		for (int frame=0; frame<numframes; ++frame)
		{ // static background
			pBehaviorManager->SetCurrentTickByTime(startframe);
			startframe += (resolution/1000.0f);
			pBehaviorManager->ExecuteAnimations(pBehaviorManager->GetCurrentTick(),-1);

			HC_Control_Update(".", "redraw everything");
			HC_Update_One_Display(".");

			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					int const aindex = 3 * ((height-y-1)*width + x);
					int const hindex = 4 * (y*width + x);
					avi_image[aindex +0] = hoops_image[hindex +2];
					avi_image[aindex +1] = hoops_image[hindex +1];
					avi_image[aindex +2] = hoops_image[hindex +0];
				}
			}

			AddAviFrame(avi, hbm);

			if (frame % 5 == 0)
				pView->ForceUpdate();
		}
	}HC_Close_Segment();
	HC_Delete_Segment(driver);
	HC_Delete_By_Key(image_seg_key);

	CloseAvi(avi);
	DeleteDC(hdc);
	DeleteObject(hbm);
	HUtilityAnnotation::WindowResizeCallback (0, 0, pView);
}


HFileOutputResult HIO_API HIOUtilityAVI::FileOutputByKey(const wchar_t * FileName, HC_KEY key, HOutputHandlerOptions * options)
{
	AVIExportInfo *avioptions = (AVIExportInfo *)options->m_pExtendedData;

	if(!avioptions)
		return OutputBadOptions;

	SetStartingOutput();

	WriteAVI(FileName,options->m_Window_Width, options->m_Window_Height, avioptions->resolution, avioptions->starttick,
		avioptions->endtick, options->m_pHBaseView);

	SetFinishedOutput();

	return OutputOK;
}

#ifdef HIO_AVI
void * CreateOutput(HIOManager *manager)
{
	HIOUtilityAVI *handler = new HIOUtilityAVI();
	manager->RegisterOutputHandler("avi",handler);
	return handler;
}

void * CreateConnector(void * unused)
{
	UNREFERENCED(unused);
	return new HIOConnector();
}

void Free(HIOUtilityAVI *handler)
{ 
	if(handler) 
		delete handler; 
}

void FreeConnector(HIOConnector *connector)
{
	if(connector)
		delete connector;
}
#endif
