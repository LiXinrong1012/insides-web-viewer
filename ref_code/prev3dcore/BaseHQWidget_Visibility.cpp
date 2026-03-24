#include "BaseHQWidget.h"


void BaseHQWidget::OnToolsVisibilityEdges()
{
	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	if (m_edges) {
		m_edges = false;
		HC_Set_Visibility ("edges = off");
	} else {
		m_edges = true;
		HC_Set_Visibility ("edges = on");
	}
	HC_Close_Segment ();
	m_pHView->Update();
}


void BaseHQWidget::OnToolsVisibilityLines()
{

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	if (m_lines){
		m_lines = false;
		HC_Set_Visibility ("lines = off");
	} else {
		m_lines = true;
		HC_Set_Visibility ("lines = on");
	}
	HC_Close_Segment ();

	m_pHView->Update();
}


void BaseHQWidget::OnToolsVisibilityFaces()
{
	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	if (m_faces) {
		m_faces = false;
		HC_Set_Visibility ("faces = off");
	} else {
		m_faces = true;
		HC_Set_Visibility ("faces = on");
	}
	HC_Close_Segment ();
	m_pHView->Update();
}


void BaseHQWidget::OnToolsVisibilityLights()
{

	HC_Open_Segment_By_Key (m_pHView->GetLightsKey());
	if (m_lights) {
		m_lights = false;
		HC_Set_Visibility ("lights = off");
	}
	else {
		m_lights = true;
		HC_Set_Visibility ("lights = (faces = on, edges = off, markers = off)");
	}
	HC_Close_Segment ();
	m_pHView->Update();
}

void BaseHQWidget::OnToolsVisibilityMarkers()
{
	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	if (m_markers) {
		m_markers = false;
		HC_Set_Visibility ("markers = off");
	} else {
		m_markers = true;
		HC_Set_Visibility ("markers = on");
	}
	HC_Close_Segment ();
	m_pHView->Update();
}


void BaseHQWidget::OnToolsVisibilityCuttingLines() 
{
	m_pHView->SetCPGeomVisibility(!m_pHView->GetCPLineVisibility(),m_pHView->GetCPFaceVisibility());
	m_pHView->Update();
}

void BaseHQWidget::OnToolsVisibilityCuttingFaces() 
{
	m_pHView->SetCPGeomVisibility(m_pHView->GetCPLineVisibility(),!m_pHView->GetCPFaceVisibility());
	m_pHView->Update();
}




void BaseHQWidget::OnToolsVisibilityAxis() 
{
	if (m_axis_on) {
		m_axis_on = false; 
		m_pHView->SetAxisMode(AxisOff);
	}else{
		m_axis_on = true;   
		m_pHView->SetAxisMode(AxisOn);
		AdjustAxisWindow();
	}

	m_pHView->Update();	
}

void BaseHQWidget::OnToolsVisibilityBoundingBox() 
{

	if (m_bounding_on) {
		m_bounding_on = false; 
	}else{
		m_bounding_on = true;   
	}

	OnOrbit();
}

void BaseHQWidget::OnToolsVisibilityLightFollows() 
{

	if (m_light_follows) {
		m_light_follows = false; 
	}else{
		m_light_follows = true;   
	}

	OnOrbit();

	m_pHView->Update();	
}

void BaseHQWidget::OnToolsVisibilityShadows() 
{

	if (m_shadows_on) {
		m_shadows_on = false; 
		m_pHView->SetShadowMode( HShadowNone );
	}else{
		m_shadows_on = true;   
		m_pHView->SetShadowMode( HShadowSoft );	
		HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
		HC_Set_Rendering_Options( "simple shadow = (resolution=64, blurring=4)" );
		HC_Close_Segment();
	}

	m_pHView->Update();	
}



void BaseHQWidget::OnToolsVisibilityCuttingPlanes() 
{
	m_pHView->SetCuttingPlanesVisibility(!m_pHView->GetCuttingPlanesVisibility());
	m_pHView->Update();
}

void BaseHQWidget::OnToolsVisibilityText() 
{
	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	if (m_text)
	{
		m_text = false;
		HC_Set_Visibility ("text = off");
	}
	else
	{
		m_text = true;
		HC_Set_Visibility ("text = on");
	}
	HC_Close_Segment ();

	m_pHView->Update();

}