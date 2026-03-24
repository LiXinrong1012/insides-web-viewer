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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/OpcodeHandlers.cpp,v 1.25 2011-01-14 21:25:30 heppe Exp $
//

#include "StdAfx.h"
#include "OpcodeHandlers.h"
#include "CSolidHoopsView.h"
#include "HMarkupManager.h"
#include "HStreamFileToolkit.h"
#include "BOpcodeHandler.h"

class Internal_Segment_Processor;
class CSolidHoopsView;
class HBaseView;

static const char * DEFAULT = "default";

class TK_My_Views : public BBaseOpcodeHandler 
{
private:
	HMarkupManager *m_markupMan;
	HTK_Camera * m_presetView;
	TK_Thumbnail * m_presetThumb;
	int m_stage, m_i, m_subStage, m_count;
	char *m_names, *m_tok, *m_save;
	bool m_hasImg;

public:
	TK_My_Views(HMarkupManager * m);
	~TK_My_Views();

	TK_Status   Interpret(BStreamFileToolkit &tk, ID_Key key, int variant) {return TK_Normal;};
	TK_Status   Execute (BStreamFileToolkit & tk) {return TK_Normal;};
	TK_Status	Write (BStreamFileToolkit & tk);
	TK_Status	Read (BStreamFileToolkit & tk) {return TK_Normal;};
	void	Reset ();
};


class TK_My_Markup : public BBaseOpcodeHandler 
{
private:
	HBaseView * m_pView;
	Internal_Segment_Processor * m_markupSeg;
	HC_KEY m_CurrentLayer;
	int m_stage;
	bool m_markupsRestored;

public:
	TK_My_Markup(HBaseView * v);
	~TK_My_Markup();

	TK_Status   Interpret(BStreamFileToolkit &tk, ID_Key key, int variant) {return TK_Normal;};
	TK_Status   Execute (BStreamFileToolkit & tk);
	TK_Status	Write (BStreamFileToolkit & tk);
	TK_Status	Read (BStreamFileToolkit & tk) {return TK_Normal;};
	void	Reset ();
	bool	restored() const {return m_markupsRestored;};
};


class TK_My_Initial_View : public HTK_Camera 
{
private:
	CSolidHoopsView	*m_pCView;
	int m_stage;

public:
	TK_My_Initial_View(CSolidHoopsView * pView);

	TK_Status   Interpret(BStreamFileToolkit &tk, ID_Key key, int variant);
	TK_Status   Execute (BStreamFileToolkit & tk);
	void	Reset ();
};


/**************************************************************************************************
 *
 *     PartviewerHSFExtrascode will read/write TK_My_Initial_View, TK_My_Markup and TK_My_Views
 *
 *************************************************************************************************/


PartviewerHSFExtras::PartviewerHSFExtras(CSolidHoopsView * pView, bool save_markup)
	: BBaseOpcodeHandler(TKE_Pseudo_Handler)
	, m_miv(0)
	, m_mm(0)
	, m_mvs(0)
	, m_pView(pView)
	, m_saveMarkup(save_markup)
{
	m_miv = new TK_My_Initial_View(pView);
	m_mm = new TK_My_Markup(pView->GetHoopsView());
	m_mvs = new TK_My_Views(pView->GetHoopsView()->GetMarkupManager());
}

PartviewerHSFExtras::~PartviewerHSFExtras()
{
	delete m_miv;
	delete m_mm;
	delete m_mvs;
}

void PartviewerHSFExtras::Reset()
{
	m_miv->Reset();
	m_mm->Reset();
	m_mvs->Reset();
	BBaseOpcodeHandler::Reset();
}

TK_Status PartviewerHSFExtras::Interpret(BStreamFileToolkit &tk, ID_Key key, int variant)
{
	HMarkupManager *markupMan = m_pView->GetHoopsView()->GetMarkupManager();

	if(markupMan->FindLayer(DEFAULT) == INVALID_KEY){
		TK_Status status = m_miv->Interpret(tk, key, variant);
		if(status != TK_Normal)
			return status;
	}

	return TK_Normal;
}

TK_Status PartviewerHSFExtras::Execute(BStreamFileToolkit &tk)
{
	TK_Status status;

	if(!m_mm->restored()){
		status = m_miv->Execute(tk);
		if(status != TK_Normal)
			return status;
	}

	status = m_mm->Execute(tk);
	if(status != TK_Normal)
		return status;

	return TK_Normal;
}

TK_Status PartviewerHSFExtras::Read(BStreamFileToolkit &tk)
{
	return m_miv->Read(tk);
}

TK_Status PartviewerHSFExtras::Write(BStreamFileToolkit &tk)
{
	HMarkupManager *markupMan = m_pView->GetHoopsView()->GetMarkupManager();

	switch(m_stage){
		default:
			return TK_Error;

		case 0:{ /* Write the markup segment */
			if(m_saveMarkup){
				TK_Status status = m_mm->Write(tk);
				if(status != TK_Normal)
					return status;
			}
			++m_stage;
		}

		case 1:{ /* Write the initial view */
			if(markupMan->FindLayer(DEFAULT) == INVALID_KEY){
				TK_Status status = m_miv->Write(tk);
				if(status != TK_Normal)
					return status;
			}
			++m_stage;
		}

		case 2:{ /* Write the views */
			if(strlen(markupMan->GetLayerNames())){
				TK_Status status = m_mvs->Write(tk);
				if(status != TK_Normal)
					return status;
			}
			++m_stage;
		}

		case 3:{
			m_stage = -1;
		}
	}
	return TK_Normal;
}


/**************************************************************************************************
 *
 *     HTK_PartviewerMaterialHandler
 *
 *************************************************************************************************/

TK_Status HTK_PartviewerMaterialHandler::Read (BStreamFileToolkit & tk) {
	m_pView->InitMaterialLibrary();
	if (!m_pView->m_bMaterialLibraryInitialized) {
		HDB::ReportError ("Prior to reading files with references to materials,\n"
						  "please specify a path to a valid materials library.\n"
						  "See the \"Tools  |  Options  |  File\" dialog", 3);
		return tk.Error ("Failed to find valid material library. Aborting file read.");
	}
	return HTK_Material_Composite::Read (tk);
}


/**************************************************************************************************
 *
 *     TK_My_Initial_View will read/write the camera currently set in the scene key
 *
 *************************************************************************************************/

TK_My_Initial_View::TK_My_Initial_View(CSolidHoopsView * pView)
	: HTK_Camera(TKE_View)
	, m_pCView(pView)
	, m_stage(0)
{
}

void TK_My_Initial_View::Reset()
{
	m_stage = 0;
	HTK_Camera::Reset();
}

TK_Status TK_My_Initial_View::Interpret(BStreamFileToolkit &tk, ID_Key key, int variant)
{
	HCamera cam;

	m_pCView->GetHoopsView()->GetCamera(&cam);

	SetPosition(&cam.position.x);
	SetTarget(&cam.target.x);
	SetUpVector(&cam.up_vector.x);
	SetField(cam.field_width, cam.field_height);
	m_settings[11] = m_settings[12] = 0;

	if(strstr(cam.projection, "perspective")){
		m_projection = TKO_Camera_Perspective;
	}
	else if(strstr(cam.projection, "orthographic")){
		m_projection = TKO_Camera_Orthographic;
	}
	else if(strstr(cam.projection, "stretched")){
		m_projection = TKO_Camera_Stretched;
	}
	else
		return TK_Error;

	if(strstr(cam.projection, "oblique")){
		m_projection |= TKO_Camera_Oblique_Mask;
		char* ctmp = strstr(cam.projection, "(");
		if(2 != sscanf(++ctmp, "%f, %f", &m_settings[11], &m_settings[12]))
			return TK_Error;
	}

	SetView(DEFAULT);

	return TK_Normal;
}


TK_Status TK_My_Initial_View::Execute(BStreamFileToolkit &tk)
{
	HPoint const pos(m_settings[0], m_settings[1], m_settings[2]);
	HPoint const tar(m_settings[3], m_settings[4], m_settings[5]);
	HPoint const up(m_settings[6], m_settings[7], m_settings[8]);

	float const fieldx = m_settings[9];
	float const fieldy = m_settings[10];

	float const oblique_y = m_settings[11];
	float const oblique_x = m_settings[12];

	char proj[MVO_BUFFER_SIZE] = {"trash"};

	unsigned char const projection = m_projection & ~TKO_Camera_Thumbnail;

	if ((projection & ~TKO_Camera_Oblique_Mask) == TKO_Camera_Perspective){
		if(oblique_x || oblique_y)
			sprintf(proj, "oblique perspective=(%f, %f)", oblique_y, oblique_x);
		else
			sprintf(proj,"perspective");
	}
	else if ((projection & ~TKO_Camera_Oblique_Mask) == TKO_Camera_Orthographic){
		if(oblique_x || oblique_y)
			sprintf(proj, "oblique orthographic = (%f, %f)", oblique_y, oblique_x);
		else
			sprintf(proj,"orthographic");
	}
	else{
		if(oblique_x || oblique_y)
			sprintf(proj, "oblique stretched = (%f, %f)", oblique_y, oblique_x);
		else
			sprintf(proj, "stretched");
	}

	HCamera dft;

	if (!streq(GetView(), DEFAULT)){
		m_pCView->GetHoopsView()->GetCamera(&dft);
	}

	m_pCView->GetHoopsView()->SetCamera(pos,tar,up,fieldx,fieldy,proj);
	m_pCView->GetHoopsView()->CameraPositionChanged(true);
	m_pCView->m_has_initial_view = true;
	m_pCView->GetHoopsView()->HasInitialView(true);

	if (streq(GetView(), DEFAULT)){
		float const x = (float)fabs(up.x);
		float const y = (float)fabs(up.y);
		float const z = (float)fabs(up.z);

		HPoint top, front;

		if (x > y && x > z){
			if (up.x > 0)
				top.Set(1,0,0);
			else
				top.Set(-1,0,0);
		}
		else if (y > x && y > z){
			if (up.y > 0)
				top.Set(0,1,0);
			else
				top.Set(0,-1,0);
		}
		else if (z > x && z > y){
			if (up.z > 0)
				top.Set(0,0,1);
			else
				top.Set(0,0,-1);
		}

		if (top.x)
			front.Set(0,1,0);
		else if (top.y)
			front.Set(0,0,1);
		else if (top.z)
			front.Set(1,0,0);

		HPoint front_old, top_old;
		m_pCView->GetHoopsView()->GetViewAxis(&front_old, &top_old);
		if (!top.Equal(top_old))
			m_pCView->GetHoopsView()->SetViewAxis(&front, &top);
	}

	if (!streq(GetView(), DEFAULT)){
		m_pCView->GetHoopsView()->GetMarkupManager()->OpenLayer(GetView());
		m_pCView->GetHoopsView()->SetCamera(dft);
	}

	// We do this so that we have fonts which are off appropriate size for the model
	m_pCView->SetSceneFont( CAppSettings::FontName, CAppSettings::FontSize, CAppSettings::FontUnits);

	return TK_Normal;
}


/**************************************************************************************************
 *
 *     END TK_My_Initial_View
 *
 *************************************************************************************************/



/**************************************************************************************************
 *
 *     TK_My_Markup will read/write the markup segment managed by HMarkupManager
 *
 *************************************************************************************************/

TK_My_Markup::TK_My_Markup(HBaseView * v)
	: BBaseOpcodeHandler(TKE_Pseudo_Handler)
	, m_pView(v)
	, m_markupSeg(0)
	, m_CurrentLayer(INVALID_KEY)
	, m_stage(0)
	, m_markupsRestored(false)
{
}

TK_My_Markup::~TK_My_Markup()
{
	delete m_markupSeg;
}

void TK_My_Markup::Reset()
{
	m_CurrentLayer = INVALID_KEY;
	delete m_markupSeg;
	m_markupSeg = 0;
	m_stage = 0;
	BBaseOpcodeHandler::Reset();
}

TK_Status TK_My_Markup::Execute(BStreamFileToolkit &tk)
{
	HMarkupManager *markupMan = m_pView->GetMarkupManager();

	HC_Open_Segment_By_Key(m_pView->GetModelKey());{
		if(HC_QShow_Existence("markup", "self")){
			char markup[MVO_BUFFER_SIZE] = {"trash"};
			HC_KEY k = HC_KCreate_Segment("markup");
			HC_Show_Segment(k, markup);
			HC_Open_Segment_By_Key(m_pView->GetOverwriteKey());{
				HC_Delete_Segment("markup");
				HC_Move_Segment(markup, "markup");
				markupMan->ReInit(m_pView);
			}HC_Close_Segment();
			m_markupsRestored = true;
		}
	}HC_Close_Segment();


	if(markupMan->FindLayer(DEFAULT) != INVALID_KEY)
		markupMan->OpenLayer(DEFAULT);

	return TK_Normal;
}


TK_Status TK_My_Markup::Write(BStreamFileToolkit &tk) 
{
	HMarkupManager *markupMan = m_pView->GetMarkupManager();
	switch(m_stage){
		default:
			return TK_Error;

		case 0:{
			if(strlen(markupMan->GetLayerNames()) > 0){
				HC_KEY odl = markupMan->FindLayer(DEFAULT);
				m_CurrentLayer = markupMan->GetCurrentLayerKey();
				if(m_CurrentLayer == INVALID_KEY){
					if(odl != INVALID_KEY)
						markupMan->DeleteLayer(odl);
					markupMan->OpenLayer(DEFAULT);
				}
				else if(odl != m_CurrentLayer){
						markupMan->CopyLayer(m_CurrentLayer, DEFAULT);
				}
				markupMan->DisableCurrentLayer();
				HC_KEY k = markupMan->GetMarkupKey();
				m_markupSeg = new Internal_Segment_Processor(k, "markup");
				m_markupSeg->SetRoot(k);
			}
			++m_stage;
		}

		case 1:{
			if(m_markupSeg){
				TK_Status status = m_markupSeg->Write(tk);
				if(status != TK_Normal)
					return status;
			}
			++m_stage;
		}

		case 2:{
			if(m_markupSeg){
				if(m_CurrentLayer != INVALID_KEY)
					markupMan->OpenLayer(m_CurrentLayer, false);
				else
					markupMan->DisableCurrentLayer();
			}
			++m_stage;
		}

		case 3:{
			m_stage = -1;
		}
	}
	return TK_Normal;
}

/**************************************************************************************************
 *
 *     END TK_My_Markup
 *
 *************************************************************************************************/



/**************************************************************************************************
 *
 *     TK_My_Views will read/write the views/thumbnails stored in the markup segment
 *
 *************************************************************************************************/


TK_My_Views::TK_My_Views(HMarkupManager * m)
	: BBaseOpcodeHandler(TKE_Pseudo_Handler)
	, m_markupMan(m)
	, m_presetView(0)
	, m_presetThumb(0)
	, m_stage(0)
	, m_i(0)
	, m_subStage(0)
	, m_count(0)
	, m_names(0)
	, m_tok(0)
{
	m_presetView = new HTK_Camera(TKE_View);
	m_presetThumb = new TK_Thumbnail();
}


TK_My_Views::~TK_My_Views()
{
	delete m_presetView;
	delete m_presetThumb;
	if(m_names)
		free(m_names);
}


void TK_My_Views::Reset()
{
	m_stage = 0;
	m_i = 0;
	m_count = 0;
	if(m_names)
		free(m_names);
	m_names = 0;
	m_tok = 0;
	m_subStage = 0;

	m_presetView->Reset();
	m_presetThumb->Reset();
	BBaseOpcodeHandler::Reset();
}


TK_Status TK_My_Views::Write(BStreamFileToolkit &tk) 
{
	switch(m_stage){
		default:
			return TK_Error;

		case 0:{
			char * names = strdup(m_markupMan->GetLayerNames());
			char * tok = strtok(names, ";");
			while(tok){
				++m_count;
				tok = strtok(0, ";");
			}
			free(names);
			++m_stage;
		}

		case 1:{
			m_names = strdup(m_markupMan->GetLayerNames());
			m_tok = strtok_s(m_names, ";", &m_save);
			++m_stage;
		}

		case 2:{
			for(; m_i < m_count; ++m_i, m_subStage = 0, m_tok = strtok_s(0, ";", &m_save)){

				switch(m_subStage){
					default:
						return TK_Error;

					case 0:{
						HC_KEY key = m_markupMan->FindLayer(m_tok);
						if(key == INVALID_KEY)
							continue;
						++m_subStage;
					}

					case 1:{
						int width = 0, height = 0, bbp = 0;
						if(m_markupMan->GetPreviewImage(m_tok, &width, &height, &bbp, 0)){
							if(	(width > 0 && width <= 256) &&
								(height > 0 && height <= 256) &&
								(bbp == 3 || bbp == 4)){
								m_hasImg = true;
							}
						}
						else
							m_hasImg = false;
						++m_subStage;
					}

					case 2:{
						HC_KEY key = m_markupMan->FindLayer(m_tok);
						HCamera cam;
						if(!m_markupMan->GetCamera(key, cam))
							continue;

						m_presetView->Reset();
						m_presetView->SetView(m_tok);
						m_presetView->SetPosition(&cam.position.x);
						m_presetView->SetTarget(&cam.target.x);
						m_presetView->SetUpVector(&cam.up_vector.x);
						m_presetView->SetField(cam.field_width, cam.field_height);

						int flags = 0;

						if(strstr(cam.projection, "perspective")){
							flags = TKO_Camera_Perspective;
						}
						else if(strstr(cam.projection, "orthographic")){
							flags = TKO_Camera_Orthographic;
						}
						else if(strstr(cam.projection, "stretched")){
							flags = TKO_Camera_Stretched;
						}
						else
							return TK_Error;

						if(strstr(cam.projection, "oblique")){
							flags |= TKO_Camera_Oblique_Mask;
							char* ctmp = strstr(cam.projection, "(");
							float h = 0, v = 0;
							if(2 != sscanf(++ctmp, "%f, %f", &h, &v))
								return TK_Error;
							m_presetView->SetOblique(h, v);
						}

						if(m_hasImg)
							flags |= TKO_Camera_Thumbnail;

						m_presetView->SetProjection(flags);
						
						++m_subStage;
					}

					case 3:{
						if(m_hasImg){
							int width = 0, height = 0, bbp = 0;
							unsigned char const * img = 0;
							m_markupMan->GetPreviewImage(m_tok, &width, &height, &bbp, &img);

							m_presetThumb->Reset();
							m_presetThumb->SetFormat(bbp == 3 ? TKO_Thumbnail_RGB : TKO_Thumbnail_RGBA);
							m_presetThumb->SetSize(width, height);
							m_presetThumb->SetBytes(bbp * width * height, img);
						}
						++m_subStage;
					}

					case 4:{
						TK_Status status = m_presetView->Write(tk);
						if(status != TK_Normal)
							return status;
						++m_subStage;
					}

					case 5:{
						if(m_hasImg){
							TK_Status status = m_presetThumb->Write(tk);
							if(status != TK_Normal)
								return status;
						}
						++m_subStage;
					}

					case 6:{
						m_subStage = -1;
					}
				}
			}
			++m_stage;
		}

		case 3:{
			m_stage = -1;
		}
	}
	return TK_Normal;
}


/**************************************************************************************************
 *
 *     END TK_My_Views
 *
 *************************************************************************************************/
