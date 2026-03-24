#include "HIOUtilitySpheres.h"
#include "HBaseView.h"
#include "HBaseModel.h"
#include "HStream.h"
#include "HBhvUtility.h"


class TK_MVO_Initial_View : public HTK_Camera 
{
public:
	TK_MVO_Initial_View(HBaseView* view) : HTK_Camera(TKE_View) { m_pHBaseView = view; }

	TK_Status Interpret(BStreamFileToolkit &tk, ID_Key key, int variant) alter{

		HPoint pos, tar, up;
		float fieldx=0, fieldy=0;
		char proj[256];

		m_pHBaseView->GetCamera(&pos,&tar,&up,fieldx,fieldy,proj);

		m_settings[0] = pos.x; m_settings[1] = pos.y; m_settings[2] = pos.z;
		m_settings[3] = tar.x; m_settings[4] = tar.y; m_settings[5] = tar.z;
		m_settings[6] = up.x ; m_settings[7] = up.y ; m_settings[8] = up.z;
		m_settings[9] = fieldx ; m_settings[10] = fieldy;

		switch ((int) proj[0]) {
			case 'o': m_projection = TKO_Camera_Orthographic; break;
			case 'p': m_projection = TKO_Camera_Perspective; break;
			case 's': m_projection = TKO_Camera_Stretched; break;
			default: m_projection = TKO_Camera_Stretched; break;
		}

		SetView("default");

		return TK_Normal;
	}

	TK_Status Execute(BStreamFileToolkit & tk) alter{

		TK_Status status=TK_Normal;

		HPoint pos, tar, up;
		float fieldx, fieldy;

		pos.Set(m_settings[0],m_settings[1],m_settings[2]);
		tar.Set(m_settings[3],m_settings[4],m_settings[5]);
		up.Set(m_settings[6],m_settings[7],m_settings[8]);
		fieldx = m_settings[9];
		fieldy = m_settings[10];

		char proj[16];

		switch ((int) m_projection) {
			case TKO_Camera_Orthographic:	strcpy (proj, "o");	break;
			case TKO_Camera_Perspective:	strcpy (proj, "p");	break;
			default: strcpy (proj, "s"); break;
		}


		if (!strcmp(GetView(),"default"))
		{
			m_pHBaseView->SetCamera(pos,tar,up,fieldx,fieldy,proj);
			m_pHBaseView->CameraPositionChanged();
		}

		return (status);
	};

private:
	HBaseView* m_pHBaseView;

};


	

HFileInputResult HIOUtilitySpheres::FileInputByKey(const __wchar_t * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	if(!FileName) return InputBadFileName;	
	if(!key) return InputFail;

	HStreamFileToolkit * tk = new HStreamFileToolkit();

	if(options && options->m_pHBaseView) 
	{
		tk->SetOpcodeHandler (TKE_View, new TK_MVO_Initial_View(options->m_pHBaseView));
		tk->SetPrewalkHandler(new TK_MVO_Initial_View(options->m_pHBaseView));
		HBhvUtility::SetupAnimationReadFromHSF(tk, options->m_pHBaseView->GetModel());
		HBhvUtility::SetupAnimationWriteFromHSF(tk, options->m_pHBaseView->GetModel());
	}

	SetStartingInput();

	HC_Open_Segment_By_Key(key);    
		TK_Status status = HTK_Read_Stream_File (FileName, tk); 
	HC_Close_Segment();

	delete tk;

	SetFinishedInput();

	HFileInputResult result = InputOK;

	//TODO report something for InputBadFileName
	if (status == TK_Error)
		result = InputFail;
	else if (status == TK_Version)
		result = InputVersionMismatch;

	return result;
}

HFileOutputResult HIOUtilitySpheres::FileOutputByKey(const __wchar_t * FileName, HC_KEY key, HOutputHandlerOptions * options)
{
	if(!FileName) return OutputBadFileName;
	if(!key) return OutputFail;

	HStreamFileToolkit * tk = 0L;

	SetStartingOutput();

	tk = options->m_pHBaseView->GetModel()->GetStreamFileTK();

	TK_Status	status;

	if(tk) 
	{
		// let's restart the toolkit so that we clear out all the 
		// temporary internal HoopsStream datastructures
		tk->Restart();
		HC_Open_Segment_By_Key(key);
			status = HTK_Write_Stream_File (FileName, tk);
		HC_Close_Segment();
	}
	else
	{
		HStreamFileToolkit * tk = new HStreamFileToolkit();

		HC_Open_Segment_By_Key(key);
			status = HTK_Write_Stream_File (FileName, tk);
		HC_Close_Segment();
		delete tk;
	}


	//TODO report something for InputBadFileName
	HFileOutputResult result = OutputOK;

	if (status == TK_Error)
		result = OutputFail;

	SetFinishedOutput();

	return result;
}

