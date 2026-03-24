//
// Copyright (c) 2005 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//

#pragma warning( disable : 4290 )

#include <assert.h>

#include "dwfcore/InputStream.h"
#include "dwf/package/Section.h"
#include "dwf/package/ObjectDefinition.h"
#include "dwf/package/utility/ResourceContainer.h"

#include "HW3DStream.h"

#ifdef _MSC_VER
#include "HStream.h"
#include "HStreamFileToolkit.h"
#else
#include "w3dhoops/HStream.h"
#include "w3dhoops/HStreamFileToolkit.h"
#endif

#include "HTools.h"
#include "HUtilityLocaleString.h"
#include "HW3DStreamInternal.h"


using namespace DWFCore;
using namespace DWFToolkit;


#define W3D_READ_BUFFER_SIZE 4096


class HW3DStream_Initial_View : public HTK_Camera 
{
public:
	HW3DStream_Initial_View(HW3DCamera* initial_view) : HTK_Camera(TKE_View), m_pInitialCamera(initial_view) {;}

	TK_Status Interpret(BStreamFileToolkit &tk, ID_Key key, int variant)
	{
		if(!m_pInitialCamera)
			return TK_Normal;

		m_settings[0] = m_pInitialCamera->position.x; 
		m_settings[1] = m_pInitialCamera->position.y; 
		m_settings[2] = m_pInitialCamera->position.z;

		m_settings[3] = m_pInitialCamera->target.x; 
		m_settings[4] = m_pInitialCamera->target.y; 
		m_settings[5] = m_pInitialCamera->target.z;

		m_settings[6] = m_pInitialCamera->up_vector.x; 
		m_settings[7] = m_pInitialCamera->up_vector.y; 
		m_settings[8] = m_pInitialCamera->up_vector.z;

		m_settings[9]  = m_pInitialCamera->field_width; 
		m_settings[10] = m_pInitialCamera->field_height;

		if(m_pInitialCamera->projection[0] == 'p')
			m_projection = TKO_Camera_Perspective;
		else
			m_projection = TKO_Camera_Orthographic;

		SetView("default");

		return TK_Normal;
	}


	TK_Status Execute(BStreamFileToolkit & tk) alter
	{
		TK_Status status=TK_Normal;

		if (!strcmp(GetView(),"default"))
		{
			m_pInitialCamera->is_valid = true;

			m_pInitialCamera->position.Set(m_settings[0],m_settings[1],m_settings[2]);
			m_pInitialCamera->target.Set(m_settings[3],m_settings[4],m_settings[5]);
			m_pInitialCamera->up_vector.Set(m_settings[6],m_settings[7],m_settings[8]);
			m_pInitialCamera->field_width = m_settings[9];
			m_pInitialCamera->field_height = m_settings[10];

			switch ((int) m_projection) {

				case TKO_Camera_Orthographic:	
					strcpy (m_pInitialCamera->projection, "orthographic");	
					break;
				
				case TKO_Camera_Perspective:	
					strcpy (m_pInitialCamera->projection, "perspective");	
					break;
				
				default: 
					strcpy (m_pInitialCamera->projection, "stretched"); 
					break;
			}

		}

		return (status);
	};

private:
	HW3DCamera* m_pInitialCamera;

};

// Translate all the TKE_Image's to W3DE_Image
class HW3DStream_Image_Converter : public HTK_Image
{
private:
	HW3DStream_Image_Converter(const HW3DStream_Image_Converter&);
	HW3DStream_Image_Converter& operator=(const HW3DStream_Image_Converter&);

public:

	HW3DStream_Image_Converter ()
	{ 
		m_opcode = W3DE_Image;
		m_size[0] = m_size[1] = 0; 
	}
	
	~HW3DStream_Image_Converter()
	{
		delete [] m_name;
	}

	TK_Status   Write (BStreamFileToolkit & tk) alter
	{
		auto        TK_Status       status = TK_Normal;

		switch (m_stage) {
		case 0: {
			if ((status = PutOpcode (tk)) != TK_Normal)
				return status;
			m_stage++;
				}

		case 1: {

			if (m_name_length > 0) {
				auto        unsigned char       byte = (unsigned char)m_name_length;
				// need handling for string > 255 ?
				if ((status = PutData (tk, byte)) != TK_Normal)
					return status;
			}
			m_stage++;
				}

		case 2: {
			if (m_name_length > 0) {
				if ((status = PutData (tk, m_name, m_name_length)) != TK_Normal)
					return status;
			}
			m_stage++;
				}
		case 3:
			{
				if ((status = PutData(tk, m_size[0])) != TK_Normal)
					return status;
				if ((status = PutData(tk, m_size[1])) != TK_Normal)
					return status;
				if ((status = PutData(tk, 24)) != TK_Normal)
					return status;
				m_stage++;

			}

		case 4: {
			if (Tagging (tk))
				status = Tag (tk);

			m_stage = -1;
				}   break;

		default:
			return tk.Error();
		}

		return status;
	}
};


static void eliminate_special_chars(wchar_t* zString)
{
	wchar_t* pIn = (wchar_t*)zString;

	while (*pIn != 0)
	{
		if (*pIn == L',')
			*pIn = L' ';
		else if (*pIn == L'\'')
			*pIn = L' ';
		else if (*pIn == L'\"')
			*pIn = L' ';
		else if (*pIn == L'/')
			*pIn = L' ';
		pIn++;
	}
}


void process_content_definition_node( DWFContent* pContent, BStreamFileToolkit* pTk, bool importMetaData ) 
{	
	DWFInstance::tMap::Iterator* piInstance = pContent->getInstances();

	for (; piInstance->valid(); piInstance->next())
	{
		DWFToolkit::DWFInstance * val = piInstance->value();
		DWFToolkit::DWFRenderable* renderedElm = val->getRenderedElement();

		int nodeId = val->getNodeID();
		HC_KEY seg_key = -1;
		pTk->IndexToKey(nodeId, seg_key);
		if( seg_key != INVALID_KEY )
		{
			// get the entity names and setthem as user data on HOOPS segment
			HC_Open_Segment_By_Key(seg_key);

			DWFString obj_str = val->id();
			DWFString obj_opt;
			obj_opt.append(L"object_id=");
			obj_opt.append(obj_str);
			wchar_t * name_obj_opt = new wchar_t[obj_opt.chars()+1];
			wcscpy(name_obj_opt, obj_opt);
			eliminate_special_chars(name_obj_opt);
			HC_Set_User_Options(H_ASCII_TEXT(name_obj_opt));
			H_SAFE_DELETE_ARRAY(name_obj_opt);

			if(importMetaData)
			{
				// insert the label as "_name" user option
				DWFCore::DWFString label = renderedElm->getLabel();
				if( label != L"" )
				{
					DWFString user_opts;
					user_opts.append(L" _name = ");
					user_opts.append(label);
					// remove unacceptable characters
					wchar_t * name_usr_opt = new wchar_t[user_opts.chars()+1];
					wcscpy(name_usr_opt, user_opts);
					eliminate_special_chars(name_usr_opt);
					HC_Set_User_Options(H_ASCII_TEXT(name_usr_opt));

					H_SAFE_DELETE_ARRAY( name_usr_opt );
					
				}

				// Set extra properties attached to label
				DWFPropertyContainer* pContainer = renderedElm;
				DWFProperty::tIterator* piProperty = pContainer->getPropertiesInOrder();
				if (piProperty)
				{
					for (; piProperty->valid(); piProperty->next())
					{
						DWFProperty* pProperty = piProperty->get();
						DWFString user_props;
						user_props.append(pProperty->name());
						user_props.append(L" = ");
						user_props.append(pProperty->value());

						// For category: Mustafa B
						if(pProperty->category() != 0)
						{
							user_props.append(L" category = ");
							user_props.append( pProperty->category());
						}

						wchar_t * h_user_props = new wchar_t[user_props.chars()+1];
						wcscpy(h_user_props, user_props);
						eliminate_special_chars(h_user_props);
						HC_Set_User_Options(H_ASCII_TEXT(h_user_props));

						H_SAFE_DELETE_ARRAY( h_user_props );
						
					}
					DWFCORE_FREE_OBJECT( piProperty );
				}
			}
			HC_Close_Segment();
		}
	}
	DWFCORE_FREE_OBJECT( piInstance );
}
								
static bool process_object_definition_node( DWFObjectDefinition* pDef, 
										    DWFDefinedObjectInstance* pInst,
										    BStreamFileToolkit* pTk, bool importMetaData)
{
	// get the HOOPS segment corresponding this object
	DWFString index_str = pInst->node();
	wchar_t const *w_index_str = index_str;
	wchar_t *end_ptr_w_i_s = const_cast<wchar_t *>(w_index_str + wcslen(w_index_str));
	int index = (int)wcstol(w_index_str, &end_ptr_w_i_s, 10);
	HC_KEY seg_key = -1;
	pTk->IndexToKey(index, seg_key);

	if( seg_key != -1 )
	{
		// get the object definition properties and set them as user data on HOOPS segment
		HC_Open_Segment_By_Key(seg_key);

		DWFString obj_str = pInst->object();
		DWFString obj_opt;
		obj_opt.append(L"object_id=");
		obj_opt.append(obj_str);
		wchar_t * name_obj_opt = new wchar_t[obj_opt.chars()+1];
		wcscpy(name_obj_opt, obj_opt);
		eliminate_special_chars(name_obj_opt);
		HC_Set_User_Options(H_ASCII_TEXT(name_obj_opt));
		H_SAFE_DELETE_ARRAY(name_obj_opt);

		if(importMetaData)
		{
			DWFProperty* pProp = NULL;
			DWFPropertyContainer* pInstProps = pDef->getInstanceProperties( *pInst );
			DWFProperty::tMap::Iterator* piProp = pInstProps->getProperties();
			if (piProp)
			{
				for (;piProp->valid(); piProp->next())
				{
					DWFString user_opts;
					pProp = piProp->value();

					user_opts.append( pProp->name() );
					user_opts.append( L" = " );
					user_opts.append( pProp->value() );

					//For Category: Mustafa B
					if(pProp->category() != 0)
					{
						user_opts.append( L" category = ");
						user_opts.append( pProp->category());
					}

					// remove unacceptable characters
					wchar_t * h_user_opts = new wchar_t[user_opts.chars()+1];
					wcscpy(h_user_opts, user_opts);
					eliminate_special_chars(h_user_opts);

					// ignore category, type and units for now
					HC_Set_User_Options(H_ASCII_TEXT(h_user_opts));

					delete[] h_user_opts;

					// we have got an _name property, rename the current segment name to it
					// NOTE: This would have been a nice feature, but it seems that HOOPS quite often 
					// doesn't like the names given to the parts (special characters?) - Rajesh B (28-Nov-05)
					//if(pProp->name() == L"_name")
					//	rename_segment(seg_key, H_ASCII_TEXT(pProp->value()));
				}
				DWFCORE_FREE_OBJECT( piProp );
			}
			DWFCORE_FREE_OBJECT( pInstProps );
		}
		HC_Close_Segment();
	}

	DWFDefinedObjectInstance::tMap::Iterator* piChildren = pInst->resolvedChildren();

	if (piChildren)
	{
		for (;piChildren->valid(); piChildren->next())
		{
			process_object_definition_node( pDef, piChildren->value(), pTk, importMetaData );
		}
		DWFCORE_FREE_OBJECT( piChildren);
	}

	return true;
}

bool HW3D_STREAM_API HW3D_Read_W3D_File(DWFInputStream* input_stream, 
										DWFSection * pModelSection, 
										HW3DCamera* ret_initial_camera,
										bool importMetaData) 
{
	HStreamFileToolkit tk;
	char buffer[W3D_READ_BUFFER_SIZE];
	TK_Status status;

	if(ret_initial_camera) 
	{
		ret_initial_camera->is_valid = false;
		tk.SetOpcodeHandler (TKE_View, new HW3DStream_Initial_View(ret_initial_camera));
		tk.SetPrewalkHandler(new HW3DStream_Initial_View(ret_initial_camera));
	}

	while(input_stream->available())
	{
		int amount_read = input_stream->read( buffer, W3D_READ_BUFFER_SIZE );
		status = tk.ParseBuffer (buffer, amount_read);

		// if (status == TK_Version)
		// version mismatched
		assert(status != TK_Error);
	}

	// process the object definitions if we have been given the model section
	if(pModelSection)
	{
		// get the object definition
		DWFResourceContainer::ResourceIterator* piObjDefs = pModelSection->findResourcesByRole( DWFXML::kzRole_ObjectDefinition );
		if (piObjDefs)
		{
			if(piObjDefs->valid())
			{
				DWFObjectDefinition* pDef = pModelSection->getObjectDefinition();
				if (pDef)
				{
					DWFDefinedObjectInstance::tList oRootInstances;
					pDef->getRootInstances( oRootInstances );

					DWFDefinedObjectInstance* pInst = NULL;
					DWFDefinedObjectInstance::tList::const_iterator iInst = oRootInstances.begin();
					for (; iInst != oRootInstances.end(); iInst++)
					{
						pInst = *iInst;
						process_object_definition_node( pDef, pInst, &tk, importMetaData );
					}

					DWFCORE_FREE_OBJECT( pDef );
				}
			}
			DWFCORE_FREE_OBJECT( piObjDefs );
		}

                
         DWFContent::tIterator* piContent = pModelSection->getContentDefinition();
         if (piContent)
         {
			 for (; piContent->valid(); piContent->next())
             {
                DWFContent* pSectionContent = piContent->get();
				process_content_definition_node( pSectionContent, &tk, importMetaData ); 
             }
             DWFCORE_FREE_OBJECT( piContent );
         }
	}
	
	return true;
}

static bool generate_object_definitions(const BStreamFileToolkit& tk, 
										HC_KEY key, 
										DWFObjectDefinitionResource* pObjDefRes,
										DWFDefinedObjectInstance * pParent = 0
										)
{
	DWFDefinedObject* pObject = 0;
	DWFDefinedObjectInstance* pInstance = 0;

	HC_Open_Segment_By_Key(key);

		int index;
		TK_Status tk_stat = tk.KeyToIndex(key, index);
		if( tk_stat != TK_Normal )
			goto recurse_subsegments;

		// see if we have got user options set
		if ( HC_Show_Existence("user options") )
		{
			char index_str[1024];
			sprintf(index_str, "%d", index);
			pObject = DWFCORE_ALLOC_OBJECT( DWFDefinedObject );
			pInstance = pObject->instance( index_str);

			int user_options_len;
			HC_Show_User_Options_Length(&user_options_len);

			char * user_options = new char[user_options_len+1];
			HC_Show_User_Options(user_options);

			char item[8192], value[8192], token[8192];
			int pos = 0;
			while(1)
			{
				if (!HC_Parse_String(user_options, ",", pos, token))
					break;

				HC_Parse_String(token, "=", 0, item);
				HC_BOOLEAN is_value = HC_Parse_String(token, "=", 1, value);

				if(!is_value)
					pInstance->addProperty( DWFCORE_ALLOC_OBJECT(DWFProperty(item, L"", L"HOOPS User Options")), true );
				else
					pInstance->addProperty( DWFCORE_ALLOC_OBJECT(DWFProperty(item, value, L"HOOPS User Options")), true );

				pos++;
			}
			// if we haven't got a "_name" in the user options, use the segment name
			if(!strstr(user_options, "_name"))
			{
				char pathname[8192]; 
				char seg_name[4096];

				HC_Show_Segment(key, pathname);
				HC_Parse_String(pathname, "/", -1, seg_name);
				
				pInstance->addProperty( DWFCORE_ALLOC_OBJECT(DWFProperty("_name", seg_name, L"HOOPS User Options")), true );
			}
			pObjDefRes->addObject( pObject );
			pObjDefRes->addInstance( pInstance );

			if(pParent)
				pParent->addChild(pInstance);

			delete[] user_options;
		}

recurse_subsegments:
		// recurse
		char type[4096];
		HC_KEY sub_seg_key;
		HC_Begin_Contents_Search (".", "segment, includes");
		while (HC_Find_Contents (type, &sub_seg_key) ) 
		{
			if (strstr("include", type))
			{
				HC_KEY includee = HC_KShow_Include_Segment(sub_seg_key);
				generate_object_definitions(tk, includee, pObjDefRes, pInstance);
			}
			else
				generate_object_definitions(tk, sub_seg_key, pObjDefRes, pInstance);
		}
		HC_End_Contents_Search ();

	HC_Close_Segment();

	return true;
}

//Similar to HTK_Write_Stream_File, but without the Restart(), so that we can do KeyToIndex after we're done
static TK_Status write_stream_file (char const * filename, HStreamFileToolkit *tk) 
{
	char                    block[TK_DEFAULT_BUFFER_SIZE];
	int                     limit = TK_DEFAULT_BUFFER_SIZE;
	TK_Status               status = TK_Normal;
	int                     amount;

	limit = tk->GetBufferLimit();
	if ((status = tk->OpenFile (filename, true)) != TK_Normal)
		return status;

	do {
		status = tk->GenerateBuffer (block, limit, amount);
		if (status == TK_Error) {
			// whatever...
			break;
		}
		if (tk->WriteBuffer (block, amount) != TK_Normal)
			break;
	} while (status != TK_Complete);
	tk->CloseFile ();
	return status;
}


bool HW3D_STREAM_API HW3D_Write_W3D_File(char const * filename, HC_KEY key, 
										 DWFObjectDefinitionResource* pObjDefRes,
										 HW3DCamera* pInitialCamera)
{
	HStreamFileToolkit * tk = new HStreamFileToolkit();

	int tk_flags = TK_Force_Tags;
	/* Vijay C: Setting vertex to full resolution. Ideally it should be provided as option to user and set the bits/vertex resolution*/
	tk_flags |= TK_Full_Resolution_Vertices;
	tk->SetWriteFlags(tk_flags);
	//tk->SetOpcodeHandler (TKE_Image, new HW3DStream_Image_Converter);
	if(pInitialCamera) 
		tk->SetPrewalkHandler(new HW3DStream_Initial_View(pInitialCamera));


	HC_Open_Segment_By_Key(key);
		//HTK_Write_Stream_File (filename, tk);
		write_stream_file(filename, tk);
	HC_Close_Segment();

	// generate the object definition XML. The user option attributes on the segments will 
	// be exported as node properties
	if( pObjDefRes )
		generate_object_definitions(*tk, key, pObjDefRes, 0);

	delete tk;

	return true;
}



