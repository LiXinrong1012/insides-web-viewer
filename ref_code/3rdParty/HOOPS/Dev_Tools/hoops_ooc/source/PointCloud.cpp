/*
 * Copyright (c) 2009 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: PointCloud.cpp,v 1.4 2010-05-04 22:42:42 chad Exp $
 */

#include "PointCloud.h"

#include "PointCloudCommon.h"

#include "vlist.h"

PointCloud::PointCloud ( wchar_t const * ooc_file_in ) {
	m_pcw = 0;
	m_update_data = 0;
	SetOOCFile(ooc_file_in);
}

PointCloud::PointCloud ( char const * ooc_file_in ) {
	m_pcw = 0;
	m_update_data = 0;
	SetOOCFile(ooc_file_in);
}

PointCloud::~PointCloud () {
	delete m_pcw;
}

void PointCloud::SetOOCFile ( wchar_t const * ooc_file_in ) {
	Initialize(ooc_file_in);
}

void PointCloud::SetOOCFile ( char const * ooc_file_in ) {
	Initialize(H_WCS(ooc_file_in).encodedText());
}

void PointCloud::Initialize ( wchar_t const * ooc_file_in ) {
	if (!m_pcw) {
		m_pcw = new PointCloudWorld();

		// default pre-process settings
		m_pcw->SetMaxShellSize(-1);
		m_pcw->SetMaxMemoryUsage(0);
		m_pcw->SetSubSamplePercentage(0.0);
		m_pcw->SetOverwriteExistingFiles(false);
		m_pcw->SetRandomizePoints(true);

		// default load settings
		m_pcw->SetLoadType(LOAD_TYPE_ASYNCHRONOUS);
	}
	if (ooc_file_in)
		m_pcw->Initialize(ooc_file_in);
}

/********************************************************************************/
/*					Pre-processing functions/settings							*/	
/********************************************************************************/

PointCloudStatus PointCloud::PreProcess () {
	return m_pcw->PreProcess();
}

void PointCloud::AddPointCloudFile ( wchar_t const * point_cloud_file_in ) {
	m_pcw->AddPointCloudFile(point_cloud_file_in);
}

void PointCloud::AddPointCloudFile ( char const * point_cloud_file_in ) {
	AddPointCloudFile(H_WCS(point_cloud_file_in).encodedText());
}

void PointCloud::SetMaxShellSize ( int max_shell_size_in ) {
	m_pcw->SetMaxShellSize(max_shell_size_in);
}

int PointCloud::GetMaxShellSize () {
	return m_pcw->GetMaxShellSize();
}

void PointCloud::SetMaxMemoryUsage ( size_t max_memory_usage_in ) {
	m_pcw->SetMaxMemoryUsage(max_memory_usage_in);
}

size_t PointCloud::GetMaxMemoryUsage () {
	return m_pcw->GetMaxMemoryUsage();
}

void PointCloud::SetSubSamplePercentage ( double subsample_in ) {
	m_pcw->SetSubSamplePercentage(subsample_in);
}

double PointCloud::GetSubSamplePercentage () {
	return m_pcw->GetSubSamplePercentage();
}

void PointCloud::SetCullingBoundingBox ( float const culling_bbox_in[6] ) {
	m_pcw->SetCullingBoundingBox(culling_bbox_in);
}

void PointCloud::GetCullingBoundingBox ( float alter culling_bbox_out[6] ) {
	if (m_pcw->GetHasCullingBoundingBox())
		m_pcw->GetCullingBoundingBox(culling_bbox_out);
	else
		culling_bbox_out[0] = culling_bbox_out[1] = culling_bbox_out[2] = culling_bbox_out[3] = culling_bbox_out[4] = culling_bbox_out[5] = 0.0f;
}

void PointCloud::SetOverwriteExistingFiles ( bool overwrite_in ) {
	m_pcw->SetOverwriteExistingFiles(overwrite_in);
}

bool PointCloud::GetOverwriteExistingFiles () {
	return m_pcw->GetOverwriteExistingFiles();
}

void PointCloud::SetLoggingFile ( wchar_t const * log_file_name ) {
	m_pcw->SetLoggingFile(log_file_name);
}

void PointCloud::SetLoggingFile ( char const * log_file_name ) {
	SetLoggingFile(H_WCS(log_file_name).encodedText());
}

/********************************************************************************/
/*						OOC loading functions/settings							*/
/********************************************************************************/

PointCloudStatus PointCloud::Load () {
	return m_pcw->Load();
}

void PointCloud::SetLoadType ( LoadType load_type_in ) {
	m_pcw->SetLoadType(load_type_in);
}

LoadType PointCloud::GetLoadType () {
	return m_pcw->GetLoadType();
}

void PointCloud::SetExternalUpdateData ( void * update_data_in ) {
	m_update_data = update_data_in;
}

void * PointCloud::GetExternalUpdateData () {
	return m_update_data;
}

bool PointCloud::IsUpdateNeeded () {
	return m_pcw->PleaseUpdate();
}
