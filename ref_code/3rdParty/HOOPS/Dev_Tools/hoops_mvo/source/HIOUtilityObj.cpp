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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HIOUtilityObj.cpp,v 1.35 2010-08-16 17:01:02 jason Exp $
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "HBaseView.h"
#include "HBaseModel.h"
#include "HIOUtilityObj.h"
#include "HUtilitySparseShell.h"
#include "varray.h"
#include "HUtilityLocaleString.h"

// HOOPS/3dGS includes
#include "hc.h"
#include "hic.h"
#include "HDB.h"

#include "HUtilityGeometryCreation.h"


#define ASSERT(x) 

// Whether to export the color interpolated geometry by faking it with a texture
//#define HU3D_COLOR_INTERPOLATION_NOT_VIA_TEXTURE

#define HOBJ_RED_GRAYNESS					0.3125f
#define HOBJ_GREEN_GRAYNESS					0.5000f       /* or .59? (NTSC) */
#define HOBJ_BLUE_GRAYNESS					0.1875f       /* or .11? (NTSC) */

#define HOBJ_RGB_TO_GRAY_TRANSPARENCY(r, g, b)    \
	(HOBJ_RED_GRAYNESS*(r) + HOBJ_GREEN_GRAYNESS*(g) + HOBJ_BLUE_GRAYNESS*(b)) 

#define HOBJ_RGB_TO_GRAY_OPACITY(r, g, b)    \
	(1.0f - HOBJ_RGB_TO_GRAY_TRANSPARENCY(r, g, b))

//Please uncomment the following line if you dont want to import lines. By default lines are exported.
//#define HOBJ_EXPORT_LINES

static bool Hoops2OBJ(const wchar_t *filename, HC_KEY model_segment_key,  HOutputHandlerOptions * options);
static wchar_t texture_file_name[MVO_BUFFER_SIZE];
static char current_face_mat_name[MVO_BUFFER_SIZE];
static char current_line_mat_name[MVO_BUFFER_SIZE];

//This is the counter for number of vertices in the OBJ file. The numbering continues sequentially throughout
//the entire file. Frequently, files have multiple lists of vertex data.
//This numbering sequence continues even when vertex data is separated by other data.
// In OBJ it is also possible to have negative relative indexing.
//static int absolute_flist_len = 1;

inline
static HPoint ReadPoint(FILE * in)
{
	char line[1000];
	fgets( line, 1000, in );

	float values[3] = {0, 0, 0};
	int count = 0;

	char * tok = strtok(line, " \t");
	while(tok && count < 3){
		values[count++] = atof(tok);
		tok = strtok(0, " \t");
	}

	HPoint retval(0, 0, 0);

	switch (count){
		case 2:
			retval.y = values[1];
		case 1:
			retval.x = values[0];
			break;

		default:
			retval = HPoint(values[0], values[1], values[2]);
	}

	return retval;
}

inline
static bool ReadFaceVertexIndexes(int indexes[3], char const * const input)
{
	indexes[0] = indexes[1] = indexes[2] = 0; // initialization
	// Modified by AS: 13/01/09
	// The face list values can have negative values in OBJ files
	// Modifying the default value set to the index to zero
	if(strchr(input, '/')){
		if(strchr(input, '/') == strrchr(input, '/')){
			//  We're in the case  a/b
			sscanf(input, "%d/%d", &indexes[0], &indexes[1]);
			indexes[2] = 0;
		}
		else if(strstr(input, "//")){
			//  We're in the case  a//c
			sscanf(input, "%d//%d", &indexes[0], &indexes[2]);
			indexes[1] = 0;
		}
		else{
			//  We're in the case a/b/c
			sscanf(input, "%d/%d/%d", &indexes[0], &indexes[1], &indexes[2]);
		}
	}
	else 
	{
		//  We're in the case  a
		//
		//if (atoi(input))
		{
			sscanf(input, "%d", &indexes[0]);
			indexes[1] = indexes[2] = 0;
		}
	}

	return false;

}

class ObjFaces
{
private:
	VIntArray m_facelist;
	VIntArray m_texCoordIndexes;
	VIntArray m_Normallist;
	
	

public:
	ObjFaces(){};

	void addFace(VIntArray const & flist){
		m_facelist.AppendArray(&flist[0], flist.Count());
	}
	void addNormal(VIntArray const & nlist){
		m_Normallist.AppendArray(&nlist[0], nlist.Count());
	}

	void addTextureCoordIndexes(VIntArray const & coords){
		m_texCoordIndexes.AppendArray(&coords[0], coords.Count());
	}

	int const * faceList() const {
		return &m_facelist[0];
	}
	int const * normalList() const {
		return &m_Normallist[0];
	}

	int const * texCoordList() const {
		return &m_texCoordIndexes[0];
	}

	int faceListLength() const {
		return m_facelist.Count();
	}

	int normalListLength() const {
		return m_Normallist.Count();
	}

	int textCoordListLength() const {
		return m_texCoordIndexes.Count();
	}

	void clear() {
		m_facelist.SetCount(0);
		m_texCoordIndexes.SetCount(0);
		m_Normallist.SetCount(0);
	}

	void fill_face_list(int * new_face_list)
	{
		m_facelist.GetArrayCopy(new_face_list);
	};

	void fill_normal_list(int * new_normal_list)
	{
		m_Normallist.GetArrayCopy(new_normal_list);
	};
	void fill_texCoord_list(int * new_texCoocrd_list)
	{
		m_texCoordIndexes.GetArrayCopy(new_texCoocrd_list);
	};
};

inline
static void ReadFace(ObjFaces & faces, FILE * in, int point_count, int tex_count, int normal_count)
{
	VIntArray vertexIndexes;
	VIntArray texCoordIndexes;
	VIntArray normalIndexes;
	int indexes[3];
	vertexIndexes.Append(0); //for the face count;
	normalIndexes.Append(0);
	texCoordIndexes.Append(0);

	char line[4000];
	fgets(line, 4000, in);
	char * tok = strtok(line, " \t");

	while(tok && !((tok[0] == 9) || (tok[0] == 10) ||(tok[0] == 13)||(tok[0] == 32)))
	{
		ReadFaceVertexIndexes(indexes, tok);
		++vertexIndexes[0];
		++normalIndexes[0];
		++texCoordIndexes[0];

		if(indexes[0] < 0)
			vertexIndexes.Append(indexes[0] + point_count); //AS: 14/01/09 the face list should be in continuation with last vertex count
		if(indexes[0] > 0)
			vertexIndexes.Append(indexes[0]-1);

		if(indexes[1] < 0)
			texCoordIndexes.Append(indexes[1] + tex_count);
		if(indexes[1] > 0)
			texCoordIndexes.Append(indexes[1]-1);

		if(indexes[2] < 0)
			normalIndexes.Append(indexes[2] + normal_count);
		if(indexes[2] > 0)
			normalIndexes.Append(indexes[2]-1);


		tok = strtok(0, " \t");
	}
	if(texCoordIndexes.Count() > 1) // to be sure that this face really has texcoords
		faces.addTextureCoordIndexes(texCoordIndexes);
	
	if(normalIndexes.Count() > 1) // to be sure that this face really has normalIndexe
		faces.addNormal(normalIndexes);

	if(vertexIndexes.Count() > 1) 
		faces.addFace(vertexIndexes); 
}

inline
static void CLAMP(float & x, float const a, float const b)
{
	if(x < a){
		x = a;
		return;
	}
	if(x > b)
		x = b;
}

inline
static void LoadTexture(char * name, wchar_t * path)
{
	wchar_t ext[100] = {L""};
	HUtility::FindFileNameExtension(path, ext);
	HInputHandler * image_handler = HDB::GetHIOManager()->GetInputHandler(ext);
	if(image_handler){
		HC_KEY key, seg_key = HC_KOpen_Segment(".");
		HC_Close_Segment();
		HInputHandlerOptions options;
		H_FORMAT_TEXT image_name("image_%s", (char*)H_UTF8(name).encodedText());
		options.m_pImageName = (char const*)image_name;
		image_handler->FileInputToImageKey(path, &key, seg_key, &options);
		HC_Define_Texture(name, H_FORMAT_TEXT("source = %s", (char const*)image_name));
		HC_Set_Visibility("images = off");
	}
}

inline
static void LoadMtlLibrary(wchar_t const * const name)
{
	FILE * in = wfopen(name, L"r");

	if(!in)
		return;

	char buffer[MVO_BUFFER_SIZE];
	fgets(buffer, MVO_BUFFER_SIZE, in);

	HC_Open_Segment("default");
	VCharArray segment_name;
	while(!feof(in)){
		char const delim[] = {" \t"};
		char const * tok = strtok(buffer, delim);
		while(tok){
			if(streq(tok, "newmtl")){
				HC_Close_Segment();
				char const * newmtl_tok = strtok(0, delim);
				if(!newmtl_tok) break;
				int len = (int)strlen(newmtl_tok);
				segment_name.EnsureSize(len);
				sscanf(newmtl_tok, "%s", (char*)segment_name);
				HC_Open_Segment(H_FORMAT_TEXT("'%s'", (char*)segment_name));
				
				
				break;
			}
			else if(strieq(tok, "Kd") || strieq(tok, "Ks") || strieq(tok, "Ka")|| strieq(tok, "Tf")){
				char * color_tok = strtok(0, delim);
				if(!color_tok) break;
				else if(streq(color_tok, "spectral")) break;
				else if(streq(color_tok, "xyz")) break;
				else {
					float r, g, b;
					r = g = b = atof(color_tok);
					color_tok = strtok(0, delim);
					if(color_tok){
						g = b = atof(color_tok);
						color_tok = strtok(0, delim);
						if(color_tok)
							b = atof(color_tok);
					}
					CLAMP(r, 0, 1);
					CLAMP(g, 0, 1);
					CLAMP(b, 0, 1);
				
					char color_name[MVO_BUFFER_SIZE];
					if(strieq(tok, "Kd"))
						HCLOCALE(sprintf(color_name, "faces = (diffuse = (r=%f g=%f b=%f))", r, g, b));
					if(strieq(tok, "Ks"))
						HCLOCALE(sprintf(color_name, "faces =(specular = (r=%f g=%f b=%f))", r, g, b));
					if(strieq(tok, "Ka"))
						HCLOCALE(sprintf(color_name, "faces =(ambient light = (r=%f g=%f b=%f))", r, g, b));
					if(strieq(tok, "Tf"))
						HCLOCALE(sprintf(color_name, "faces = (transmission = (r=%f g=%f b=%f))", r, g, b));
					HC_Set_Color(color_name);

				}
				break;
			}
			else if(streq(tok, "map_Kd")){
				char const * filename_tok = strtok(0, delim);
				if(!filename_tok) break;
				char image_name[MVO_BUFFER_SIZE]= {""};
				sscanf(filename_tok, "%s", image_name);
				wchar_t image_path[MVO_BUFFER_SIZE]= {L""};
				wcscpy(image_path, name);
				wchar_t * file = wcsrchr(image_path, L'/');
				if(!file)
					file = wcsrchr(image_path, L'\\');
				++file;
				wcscpy(file, (wchar_t*)H_WCS(image_name).encodedText());

				char texture_name[MVO_BUFFER_SIZE] = "";
				char name[MVO_BUFFER_SIZE] = "";
				sprintf(texture_name, "%s",(char const*)segment_name);

				bool alreadythere = false;
				HC_Begin_Texture_Search ();
					while (HC_Find_Texture (name)) 
					{
						if(streq(name, texture_name))
							alreadythere = true;
					}
				HC_End_Texture_Search ();

				if(!alreadythere)
					LoadTexture(segment_name, image_path);

				HC_Set_Color(H_FORMAT_TEXT("faces = %s", (char const*)segment_name));
				break;
			}

			else if(streq(tok, "refl")){
				strtok(NULL, " \t");
				strtok(NULL, " \t");
				char const * filename_tok = strtok(0, delim);
				if(!filename_tok) break;
				char image_name[MVO_BUFFER_SIZE]= {""};
				sscanf(filename_tok, "%s", image_name);
				wchar_t image_path[MVO_BUFFER_SIZE]= {L""};
				wcscpy(image_path, name);
				wchar_t * file = wcsrchr(image_path, L'/');
				if(!file)
					file = wcsrchr(image_path, L'\\');
				++file;
				wcscpy(file, (wchar_t*)H_WCS(image_name).encodedText());

			
				char name[MVO_BUFFER_SIZE] = "";
				char texture_name[MVO_BUFFER_SIZE] = "";
				sprintf(texture_name, "%s",(char const*)segment_name);
				
				bool alreadythere = false;
	
				HC_Begin_Texture_Search () ;
				while (HC_Find_Texture (name)) 
				{
					if(streq(name, texture_name))
						alreadythere = true;
				}
				HC_End_Texture_Search ();

				if(!alreadythere)
					LoadTexture(segment_name, image_path);

				if(!streq(texture_name, "")) 
					HC_Set_Color(H_FORMAT_TEXT("faces = ( mirror = (r=0.5 g=0.5 b=0.5),environment = %s)",texture_name));
				
				break;
			}

			//tok = strtok(buffer, " \t");
			tok = strtok(NULL, " \t");  //AS: 12/01/09
		}
		fgets(buffer, MVO_BUFFER_SIZE, in);
	}
	HC_Close_Segment();
}

static bool AddShellThroughUtility(VArray<HPoint> &points, VArray<HPoint> &normals, VFloatArray &texcoords, ObjFaces &faces )
{
	HPoint * new_vertex = 0;
	int * new_face_list = 0;
	HPoint * new_normals = 0;
	int * new_normal_list = 0;
	int * new_texCoord_list = 0;
	float * texCoordarray = 0;

	new_vertex = new HPoint[points.Count()];
	points.GetArrayCopy(new_vertex);
	
	new_face_list = new int[faces.faceListLength()];
	faces.fill_face_list(new_face_list);

	if(faces.normalListLength() == faces.faceListLength() )
	{
		new_normals = new HPoint[normals.Count()];
		normals.GetArrayCopy(new_normals);

		new_normal_list = new int[faces.normalListLength()];
		faces.fill_normal_list(new_normal_list);
	}

	if(faces.textCoordListLength() == faces.faceListLength())
	{
		new_texCoord_list = new int[faces.textCoordListLength()];
		faces.fill_texCoord_list(new_texCoord_list);

		texCoordarray = new float[texcoords.Count()];
		texcoords.GetArrayCopy(texCoordarray);
		
	}

	HUtilityGeometryCreation::CreateShellWithFaceSpecificVertexAttributes(
		(HPoint*) new_vertex, faces.faceListLength(), new_face_list,
		new_normals, new_normal_list,
		0,0,
		0,0,
 		texCoordarray, new_texCoord_list, 2);

	

	if(new_vertex)
		delete [] new_vertex;
	if(new_face_list)
		delete [] new_face_list;
	if(new_normals)
		delete [] new_normals;
	if(new_normal_list)
		delete [] new_normal_list;
	if(new_texCoord_list)
		delete [] new_texCoord_list;
	if(texCoordarray)
		delete [] texCoordarray;

	return true;
};

HFileInputResult HIOUtilityObj::FileInputByKey(const wchar_t *FileName, HC_KEY key, HInputHandlerOptions * options) 
{
	// OBJ uses a Cartesian, right-handed, 3-dimensional coordinate system. 
	HC_Open_Segment_By_Key(key);
		HC_Set_Handedness("Right");
	HC_Close_Segment();

	if(!FileName) return InputBadFileName;
	if(key == INVALID_KEY) return InputFail;

	VCharArray line(MVO_BUFFER_SIZE), tok(MVO_BUFFER_SIZE);
	VArray<HPoint> points;
	VFloatArray texCoords; //Texture Coordinates
	VArray<HPoint> normals;

	HUtilitySparseShell im(false, false);
	ObjFaces faces;
	char material_name[MVO_BUFFER_SIZE] = {"default"};

	SetStartingInput(FileName);

	FILE * f = wfopen(FileName,L"r");  // open the file as ASCII
	if (f == NULL) 
		return InputBadFileName;

	fseek(f, 0, SEEK_END);
	long const file_size = ftell(f);
	fseek(f, 0, SEEK_SET);

	float start_time;
	HC_Show_Time(&start_time);

	int reports = 0;

	HCLOCALE(

	fscanf( f, "%s", (char*)tok );
	while( !feof( f ) )
	{
		long const position = ftell(f);
		float const percent_complete = position / (float)file_size;
		if(reports++ % 1000 == 0)
			ReportInputPercentProgress(percent_complete);

		if( streq( tok, "v" ) )
		{
			//it's a vertex
			HPoint point = ReadPoint(f);
			points.Append(point);
		}
		else if( streq( tok, "vt" ) )
		{
			//it's a texture coordinate
			HPoint point = ReadPoint(f);
			texCoords.Append(point.x);
			texCoords.Append(point.y);
		}
		else if( streq( tok, "vn" ) )
		{
			//it's a Normal
			HPoint point = ReadPoint(f);
			normals.Append(point);		
		}
		else if( streq( tok, "f" ) )
		{
			//It's a face
			//AS: 14/01/09 To count the verices, used in creating face list
			ReadFace(faces, f, points.Count(), texCoords.Count()*0.5,normals.Count());
		}
		else if( streq( tok, "usemtl" ) )
		{
			//it's a material name

			//insert the geometry for the last material
			HC_Open_Segment_By_Key(key);{
				HC_Open_Segment(H_FORMAT_TEXT("`%s`", material_name));{
					if(faces.faceListLength()){
						AddShellThroughUtility(points, normals, texCoords, faces);
						faces.clear();
					}
				}HC_Close_Segment();
			}HC_Close_Segment();

			faces.clear();

			//set the new material name
			fgets(line, MVO_BUFFER_SIZE, f);
			sscanf(line, "%s", material_name);
		}
		else if( streq( tok, "mtllib" ) ){
			//It's a material library... load it...
			fgets(line, MVO_BUFFER_SIZE, f);
			char library_name[MVO_BUFFER_SIZE]= {""};
			sscanf(line, "%s", library_name);
			wchar_t library_path[MVO_BUFFER_SIZE]= {L""};
			wcscpy(library_path, FileName);
			wchar_t * file = wcsrchr(library_path, L'/');
			if(!file)
				file = wcsrchr(library_path, L'\\');
			++file;
			wcscpy(file, (wchar_t*)H_WCS(library_name).encodedText());

			HC_Open_Segment_By_Key(key);{
				LoadMtlLibrary(library_path);
			}HC_Close_Segment();
		}
		else
			fgets(line, MVO_BUFFER_SIZE, f);
		fscanf( f, "%s", (char*)tok );
	}

	); //HCLOCALE

	HC_Open_Segment_By_Key(key);{
		HC_Set_Color("white");
		HC_Open_Segment(H_FORMAT_TEXT("'%s'", material_name));
		{
			AddShellThroughUtility(points,normals, texCoords, faces);	
			faces.clear();
		}
		HC_Close_Segment();
	}HC_Close_Segment();

	fclose(f);

	float end_time;
	HC_Show_Time(&end_time);
	float total_time = end_time - start_time;
	ReportInputInformation(H_FORMAT_TEXT("Time elapsed while loading: %0.2f seconds.", total_time));
	ReportInputPercentProgress(1.0);
	SetFinishedInput();

	return InputOK;
}

HFileOutputResult HIOUtilityObj::FileOutputByKey(const wchar_t * FileName, HC_KEY key, HOutputHandlerOptions * options) 
{

	SetStartingOutput();

	bool result = Hoops2OBJ(FileName, key, options);

	SetFinishedOutput();

	if(result) 
		return OutputOK;
	else
	{
		ReportOutputInformation("Unknown error while reading .obj file. Could not load file");
		return OutputFail;
	}
}

static bool export_line_curve (HC_KEY curve_key, FILE* fhandle, float h_net_matrix[4][4], HC_KEY orig_geom_key = INVALID_KEY)
{
	int n_pts = 0;
	float *points = 0;
	int i;

	HC_Compute_Polyline_From_Curve_Size(curve_key, "", &n_pts);
	if( n_pts < 1 )
		return false;

	points = new float[n_pts*3];
	HC_Compute_Polyline_From_Curve(curve_key, "", &n_pts, points);
	HC_Compute_Transformed_Points (n_pts, points, &h_net_matrix[0][0], points);
	for(i = 0; i < n_pts; i++)
		fprintf(fhandle, "v %f %f %f\n", points[i*3], points[i*3+1], points[i*3+2]);

	fprintf(fhandle, "\n\n");

	fprintf(fhandle, "%c ", 'l');
	for(i = 0; i < n_pts; i++)
		fprintf(fhandle, "%d ", i-(n_pts));

	fprintf(fhandle, "\n\n");

	//	absolute_flist_len = absolute_flist_len+n_pts;
	H_SAFE_DELETE_ARRAY(points);
	return true;


}
static bool export_point(HC_KEY line_key, FILE* fhandle, float h_net_matrix[4][4], HC_KEY orig_geom_key = INVALID_KEY)
{
	float points[3];
	HC_Show_Marker(line_key, &points[0], &points[1], &points[2]);
	HC_Compute_Transformed_Points (1, points, &h_net_matrix[0][0], points);
	fprintf(fhandle, "v %f %f %f\n", points[0], points[1], points[2]);
	fprintf(fhandle, "\n");
	fprintf(fhandle, "p %d ", -1);
	fprintf(fhandle, "\n\n");
	//	absolute_flist_len = absolute_flist_len+1;

	return true;
}

static bool export_line(HC_KEY line_key, FILE* fhandle, float h_net_matrix[4][4], HC_KEY orig_geom_key = INVALID_KEY)
{
	float points[6];
	int i;
	HC_Show_Line (line_key, &points[0], &points[1], &points[2],
		&points[3], &points[4], &points[5]);
	HC_Compute_Transformed_Points (2, points, &h_net_matrix[0][0], points);
	for(i = 0; i < 2; i++)
		fprintf(fhandle, "v %f %f %f\n", points[i*3], points[i*3+1], points[i*3+2]);

	fprintf(fhandle, "\n");

	fprintf(fhandle, "%c ", 'l');
	for(i = 0; i < 2; i++)
		fprintf(fhandle, "%d ", i-(2));

	fprintf(fhandle, "\n\n");
	//	absolute_flist_len = absolute_flist_len+2;

	return true;
}

static bool export_polyline(HC_KEY polyline_key, FILE* fhandle, float h_net_matrix[4][4], HC_KEY orig_geom_key = INVALID_KEY)
{
	// show the line details
	int n_pts = 0;
	float *points = 0;
	int i;

	HC_Show_Polyline_Count(polyline_key, &n_pts);

	points = new float[n_pts*3];
	HC_Show_Polyline( polyline_key, &n_pts, points);
	HC_Compute_Transformed_Points (n_pts, points, &h_net_matrix[0][0], points);
	for(i = 0; i < n_pts; i++)
		fprintf(fhandle, "v %f %f %f\n", points[i*3], points[i*3+1], points[i*3+2]);

	fprintf(fhandle, "\n\n");

	fprintf(fhandle, "%c ", 'l');
	for(i = 0; i < n_pts; i++)
		fprintf(fhandle, "%d ", i-(n_pts));

	fprintf(fhandle, "\n\n");

	H_SAFE_DELETE_ARRAY(points);
	//absolute_flist_len = absolute_flist_len+n_pts;

	return true;
}

static bool export_mesh(HC_KEY mesh_key, FILE* fhandle, float h_net_matrix[4][4], HC_KEY orig_geom_key = INVALID_KEY)
{
	float *points		= 0;
	float *normals		= 0;

	// show the mesh details - U3D needs everything as triangles
	int i, n_rows, n_cols, n_quads;
	int n_pts, n_tex_dim;

	HC_Show_Mesh_Size (mesh_key, &n_rows, &n_cols);
	if( (n_rows < 1) || (n_cols < 1) )
		return false;
	n_pts	= n_rows * n_cols;
	points	= new float [3*n_pts];
	HC_Show_Mesh(mesh_key, &n_rows, &n_cols, points);

	n_quads = (n_rows-1)*(n_cols-1);

	if(n_quads < 1)
		return false;

	// allocate array to hold quad indices
	int *quad_idxs = new int[n_quads*4];

	HC_Show_Mesh(mesh_key, &n_rows, &n_cols, points);

	HC_Compute_Transformed_Points (n_pts, points, &h_net_matrix[0][0], points);
	for(i = 0; i < n_pts; i++)
		fprintf(fhandle, "v %f %f %f\n", points[i*3], points[i*3+1], points[i*3+2]);
	fprintf(fhandle, "\n");

	// check to see if we have got vertex normals here.
	int n_normals = HC_Show_Existence_By_Key (mesh_key, "vertex normals");
	//if(  n_normals != n_pts )		// We don't yet handle a partial mesh with vertex normals.
	//	n_normals = 0;

	if(n_normals > 0)
	{
		normals = new float[n_pts*3];
		HC_MShow_Net_Vertex_Normals(mesh_key, 0, n_pts, normals);

		// Set normals
		for (i = 0; i < n_normals; i++)
		{
			for(int i = 0; i < n_pts; i++)
				fprintf(fhandle, "vn %f %f %f\n", normals[i*3], normals[i*3+1], normals[i*3+2]);
		}

		H_SAFE_DELETE_ARRAY(normals);
	}

	HC_MShow_Vertex_Parameter_Size(mesh_key, &n_tex_dim);

	if( n_tex_dim > 0 )
	{
		float *tex_coords = new float[ n_pts * n_tex_dim];
		HC_MShow_Vertex_Parameters(mesh_key, 0, n_pts, &n_tex_dim, tex_coords);

		for(int i = 0; i < n_pts; i++)
			fprintf(fhandle, "vt %f %f %f\n", tex_coords[i*3], tex_coords[i*3+1], tex_coords[i*3+2]);
		fprintf(fhandle, "\n");

		H_SAFE_DELETE_ARRAY(tex_coords);
	}

	//n_tex_dim = 0;

	// Why like this? OBJ has face syntax like this 
	// f  v1/vt1/vn1   v2/vt2/vn2   v3/vt3/vn3 . . .
	// v =  vertex index, vt  = Texture vertex index, vn = normal index
	if((n_normals>0) && (n_tex_dim>0))
	{
		// convert the mesh into quads array.
		int k = 0;
		int g = 0;
		for(int r = 0; r < n_rows-1; r++)
		{
			for(int c = 0; c < n_cols-1; c++)
			{
				quad_idxs[k] = (r*n_cols) + c;			k++;
				quad_idxs[k] = (r*n_cols) + c + 1;		k++;
				quad_idxs[k] = (r+1)*n_cols + c + 1;	k++;
				quad_idxs[k] = (r+1)*n_cols + c;		k++;

				fprintf(fhandle, "%c ", 'f');
				for(int i = 0; i < 4; i++, g++)
					fprintf(fhandle, "%d/%d/%d ", quad_idxs[g]-(n_pts), quad_idxs[g]-(n_pts), quad_idxs[g]-(n_pts));
				fprintf(fhandle, "\n");
			}
		}
	}
	else if ((n_normals == 0) && (n_tex_dim == 0))
	{
		// convert the mesh into quads array.
		int k = 0;
		int g = 0;
		for(int r = 0; r < n_rows-1; r++)
		{
			for(int c = 0; c < n_cols-1; c++)
			{
				quad_idxs[k] = (r*n_cols) + c;			k++;
				quad_idxs[k] = (r*n_cols) + c + 1;		k++;
				quad_idxs[k] = (r+1)*n_cols + c + 1;	k++;
				quad_idxs[k] = (r+1)*n_cols + c;		k++;

				fprintf(fhandle, "%c ", 'f');
				for(int i = 0; i < 4; i++, g++)
					fprintf(fhandle, "%d ", quad_idxs[g]-(n_pts));
				fprintf(fhandle, "\n");
			}
		}
	}
	else if((n_normals == 0))
	{
		// convert the mesh into quads array.
		int k = 0;
		int g = 0;
		for(int r = 0; r < n_rows-1; r++)
		{
			for(int c = 0; c < n_cols-1; c++)
			{
				quad_idxs[k] = (r*n_cols) + c;			k++;
				quad_idxs[k] = (r*n_cols) + c + 1;		k++;
				quad_idxs[k] = (r+1)*n_cols + c + 1;	k++;
				quad_idxs[k] = (r+1)*n_cols + c;		k++;

				fprintf(fhandle, "%c ", 'f');
				for(int i = 0; i < 4; i++, g++)
					fprintf(fhandle, "%d/%d ", quad_idxs[g]-(n_pts), quad_idxs[g]-(n_pts));
				fprintf(fhandle, "\n");
			}
		}
	}
	else if((n_tex_dim == 0))
	{
		// convert the mesh into quads array.
		int k = 0;
		int g = 0;
		for(int r = 0; r < n_rows-1; r++)
		{
			for(int c = 0; c < n_cols-1; c++)
			{
				quad_idxs[k] = (r*n_cols) + c;			k++;
				quad_idxs[k] = (r*n_cols) + c + 1;		k++;
				quad_idxs[k] = (r+1)*n_cols + c + 1;	k++;
				quad_idxs[k] = (r+1)*n_cols + c;		k++;

				fprintf(fhandle, "%c ", 'f');
				for(int i = 0; i < 4; i++, g++)
					fprintf(fhandle, "%d//%d ", quad_idxs[g]-(n_pts), quad_idxs[g]-(n_pts));
				fprintf(fhandle, "\n");
			}
		}
	}
	H_SAFE_DELETE_ARRAY(points);
	H_SAFE_DELETE_ARRAY(quad_idxs);

	//	absolute_flist_len = absolute_flist_len+n_pts;

	return true;
}

static bool export_polygon(HC_KEY polygon_key, FILE* fhandle, float h_net_matrix[4][4], HC_KEY orig_geom_key = INVALID_KEY)
{
	int n_pts	= 0;
	float *points	= 0;
	int i;

	HC_Show_Polygon_Count(polygon_key, &n_pts);
	ASSERT( n_pts > 0);

	points = new float[n_pts*3];
	HC_Show_Polygon( polygon_key, &n_pts, points);
	HC_Compute_Transformed_Points (n_pts, points, &h_net_matrix[0][0], points);
	for(i = 0; i < n_pts; i++)
		fprintf(fhandle, "v %f %f %f\n", points[i*3], points[i*3+1], points[i*3+2]);

	fprintf(fhandle, "\n");

	// In Hoops fr polygon there is implicit connectivity but not in OBJ
	fprintf(fhandle, "%c ", 'f');
	for(i = 0; i < n_pts; i++)
		fprintf(fhandle, "%d ", i-(n_pts));

	fprintf(fhandle, "\n\n");

	//absolute_flist_len = absolute_flist_len+n_pts;

	H_SAFE_DELETE_ARRAY(points);

	return true;
}

static bool export_shell(HC_KEY shell_key, FILE* fhandle, float h_net_matrix[4][4], HC_KEY orig_geom_key = INVALID_KEY)
{
	float *points		= 0;
	float *normals		= 0;
	int   *flist		= 0;

	int n_pts, flist_len, n_tex_dim;

	////char family_name[MVO_BUFFER_SIZE];
	////char data[MVO_BUFFER_SIZE];

	//// We are trying to text as shell by getting the outline of the text. It is possible only if the font is oulieable.
	//bool key_is_of_text = false;
	//char type[MVO_BUFFER_SIZE];
	//HC_Show_Key_Type(shell_key, type);
	//if( streq(type, "text"))
	//{
	//	key_is_of_text = true;
	//	HC_Show_One_Net_Text_Font ("name", family_name);
	//	HC_Show_Font_Info ("/driver", family_name, "outlineable", data);
	//	if(data)
	//	{
	//		HC_Compute_Text_Outline_Size_By (shell_key, &n_pts, &flist_len);
	//	}
	//	else
	//		key_is_of_text = false;
	//}
	//else
	/*if(key_is_of_text == true)
	HC_Compute_Text_Outline_By_Key (shell_key, &n_pts, points, &flist_len, flist);
	else*/

	HC_Show_Shell_Size(shell_key, &n_pts, &flist_len);

	if( n_pts < 1 )
		return false;

	points		= new float [3*n_pts];
	flist       = new int[flist_len];

	HC_Show_Shell(shell_key, &n_pts, points, &flist_len, flist);

	HC_Compute_Transformed_Points (n_pts, points, &h_net_matrix[0][0], points);
	for(int i = 0; i < n_pts; i++)
		fprintf(fhandle, "v %f %f %f\n", points[i*3], points[i*3+1], points[i*3+2]);

	fprintf(fhandle, "\n");

	// check to see if we have got vertex normals here. If there are vertex normals set get it. It is possible that
	// not all the vertex has normals so get the net normals. If the number of veretx normals dont even export net normals. 
	int n_normals = HC_Show_Existence_By_Key (shell_key, "vertex normals");
	//n_normals = 0;
	if(n_normals > 0)
	{
		normals = new float[n_pts*3];
		HC_MShow_Net_Vertex_Normals(shell_key, 0, n_pts, normals);

		// Set normals
		for (int i = 0; i < n_normals; i++)
		{			
			fprintf(fhandle, "vn %f %f %f\n", normals[i*3], normals[i*3+1], normals[i*3+2]);
		}
		H_SAFE_DELETE_ARRAY(normals);
	}
	fprintf(fhandle, "\n\n");

	HC_MShow_Vertex_Parameter_Size(shell_key, &n_tex_dim);

	if( n_tex_dim > 0 )
	{
		float *tex_coords = new float[ n_pts * n_tex_dim];
		HC_MShow_Vertex_Parameters(shell_key, 0, n_pts, &n_tex_dim, tex_coords);

		//AS: 15/01/09 Modified because there was problem of saving file from Obj to Obj, in that case the texture dimentions of shell
		// was 2.
		// At first time from saving Obj from hsf it is 3
		// when we load this obj and save it as obj the texture dimentions comes as 2
		if(n_tex_dim == 3)
		{
			for(int i = 0; i < n_pts; i++)
			{
				fprintf(fhandle, "vt %f %f %f\n", tex_coords[i*3], tex_coords[i*3+1], tex_coords[i*3+2]); //AS:
			}
		}
		if(n_tex_dim == 2)
		{
			for(int i = 0; i < n_pts; i++)
			{
				fprintf(fhandle, "vt %f %f %f\n", tex_coords[i*2], tex_coords[i*2+1], 0.00f); //AS:
			}
		}
		H_SAFE_DELETE_ARRAY(tex_coords);
	}



	// Why like this? OBJ has face syntax like this 
	// f  v1/vt1/vn1   v2/vt2/vn2   v3/vt3/vn3 . . .
	// v =  vertex index, vt  = Texture vertex index, vn = normal index
	if((n_normals>0) && (n_tex_dim>0))
	{
		int j = 0;
		for(int i = 0; i < flist_len;)
		{
			fprintf(fhandle, "%c ", 'f');
			j = flist[i];
			i++;
			while(j)
			{
				fprintf(fhandle, "%d/%d/%d ", (flist[i]-(n_pts)), (flist[i]-(n_pts)), (flist[i]-(n_pts)));
				j--;
				i++;
			}
			fprintf(fhandle, "\n");
		}
	}
	else if ((n_normals == 0) && (n_tex_dim == 0))
	{
		int j = 0;
		for(int i = 0; i < flist_len;)
		{
			fprintf(fhandle, "%c ", 'f');
			j = flist[i];
			i++;
			while(j)
			{
				fprintf(fhandle, "%d ", (flist[i]-(n_pts)));
				j--;
				i++;
			}
			fprintf(fhandle, "\n");
		}
	}
	else if((n_normals == 0))
	{
		int j = 0;
		for(int i = 0; i < flist_len;)
		{
			fprintf(fhandle, "%c ", 'f');
			j = flist[i];
			i++;
			while(j)
			{
				fprintf(fhandle, "%d/%d ", (flist[i]-(n_pts)), (flist[i]-(n_pts)));
				j--;
				i++;
			}
			fprintf(fhandle, "\n");
		}
	}
	else if((n_tex_dim == 0))
	{
		int j = 0;
		for(int i = 0; i < flist_len;)
		{
			fprintf(fhandle, "%c ", 'f');
			j = flist[i];
			i++;
			while(j)
			{
				fprintf(fhandle, "%d//%d ", (flist[i]-(n_pts)), (flist[i]-(n_pts)));
				j--;
				i++;
			}
			fprintf(fhandle, "\n");
		}
	}
	//	absolute_flist_len = absolute_flist_len + n_pts;
	fprintf(fhandle, "\n\n");

	H_SAFE_DELETE_ARRAY(points);
	H_SAFE_DELETE_ARRAY(flist);

	return true;
}

// Creates a OBJ texture object based on the texture attributes present in 
// the HOOPS segment.
bool get_texture_for_segment(FILE *fhandle_mtl, HC_KEY segment_key, const char * h_texture_name, VArray<HC_KEY>& segment_path, bool is_environ_map)
{
	// create a unique name for texture
	char texture_name[MVO_BUFFER_SIZE];
	sprintf(texture_name, "%s.tiff", h_texture_name);

	int path_count = segment_path.Count();
	HC_KEY * path_array = (HC_KEY*)(&segment_path.GetData(0));

	HC_Open_Segment_By_Key(segment_key);

	// get the texture definition
	char tex_def[MVO_BUFFER_SIZE];
	HC_KEY image_key = INVALID_KEY;

	HC_PShow_Net_Texture(path_count, path_array, h_texture_name, tex_def, &image_key);

	if(image_key == INVALID_KEY)
		return false;

	// Create a bmp file in which all the texture data is stored. We will create the bmp file with the same name 
	// as that of obj file and in the same directory.

	wchar_t *path = texture_file_name;
	wchar_t *end;
	for(end=path; *end; )
		end++;
	path = end;

	while(*--path != L'\\' && *path != L'/')
	{
		*path = L'\0';
	}
	wcscat(texture_file_name, (wchar_t*)H_WCS(texture_name).encodedText());

	if(is_environ_map == false)
		fprintf(fhandle_mtl, "map_Kd %s\n\n", texture_name);
	else
		fprintf(fhandle_mtl, "refl -type sphere %s\n\n", texture_name);

	char output[MVO_BUFFER_SIZE];

	HC_PShow_One_Net_Texture(path_count, path_array, h_texture_name, "tiling", output);
	if(streq(output,"clamp")) 
		fprintf(fhandle_mtl, "%s", "clamp on");

	HC_Close_Segment();
	HOutputHandler* image_hanlder = HDB::GetHIOManager()->GetOutputHandler("tiff");
	HFileOutputResult result = image_hanlder->FileOutputFromImageKey(texture_file_name, image_key, 0);
	if(result == OutputOK )
		return true;
	else 
		return false;
}

// Creates a U3D texture object based on the color map. This texture can be used 
// to fake the color interpolation/color index interpolation. 
// Inserts this texture in the texture palette and return the ID
// segment_key: HOOPS segment key for which the texture is to be created
// nTextureID: returned id of texture
// bHasDiffuseColor: returns true if there is a diffuse color (modulated to texture)
// diffuseColor: the diffuse color
bool get_interpolation_texture_for_segment(FILE *fhandle_mtl, HC_KEY segment_key, const char * h_texture_name,
										   VArray<HC_KEY>& segment_path)
{

	// create a unique name for texture
	char texture_name[MVO_BUFFER_SIZE];
	sprintf(texture_name, "%s.bmp", h_texture_name);

	int path_count = segment_path.Count();
	HC_KEY * path_array = (HC_KEY*)(&segment_path.GetData(0));

	HC_Open_Segment_By_Key(segment_key);
	HC_KEY image_key = INVALID_KEY;

	// Create a bmp file in which all the texture data is stored. We will create the bmp file with the same name 
	// as that of obj file and in the same directory.

	wchar_t *path = texture_file_name;
	wchar_t *end;
	for(end=path; *end; )
		end++;
	path = end;

	while(*--path != L'\\' && *path != L'/')
	{
		*path = L'\0';
	}
	wcscat(texture_file_name, (wchar_t*)H_WCS(texture_name).encodedText());

	fprintf(fhandle_mtl, "map_Kd %s\n\n", texture_name);

	// get the texture definition
	int n_colors;
	HC_PShow_Net_Color_Map_Count(path_count, path_array, &n_colors);

	if(n_colors < 1)
	{
		// HOOPS has a default colormap of length 10 and I don't think users 
		// are allowed to set a colormap of 0 length. So, I can't imagine why would 
		// anyone land up here. Anyway... - Rajesh B (14-Feb-07)
		HC_Close_Segment();
		return false;
	}

	// create an image from the colormap.
	int n_tex_components = 3;
	int height = 1;
	int width = n_colors;
	unsigned char *pixels = new unsigned char[width*height*n_tex_components];;
	float * h_colors = new float[n_colors*3];
	char color_space[MVO_BUFFER_SIZE];

	HC_PShow_Net_Color_Map_By_Value(path_count, path_array, color_space, &n_colors, h_colors);
	bool is_rgb = (strieq(color_space, "rgb" ));
	if(!is_rgb)
	{
		for(int i = 0; i < n_colors; i++)
			HC_Compute_Color_By_Value(color_space, &h_colors[i*3], "rgb", &h_colors[i*3]);
	}

	for(int i = 0; i < n_colors; i++)
	{
		pixels[(i*3)]     = (unsigned char)((255.99f) * h_colors[(i*3)]  );
		pixels[(i*3)+1]   = (unsigned char)((255.99f) * h_colors[(i*3)+1]);
		pixels[(i*3)+2]   = (unsigned char)((255.99f) * h_colors[(i*3)+2]);
	}

	HC_Open_Segment ("?include library/image");
	image_key = HC_KInsert_Image (0.0, 0.0, 0.0, "rgb", 100, 100, (void *)pixels);
	HC_Close_Segment();

	HC_Close_Segment();
	delete[] pixels;

	HOutputHandler* image_hanlder = HDB::GetHIOManager()->GetOutputHandler("bmp");
	HFileOutputResult result = image_hanlder->FileOutputFromImageKey(texture_file_name, image_key, 0);
	if(result == OutputOK )
		return true;
	else 
		return false;
}

static bool get_material_for_line(HC_KEY segment_key, FILE* fhandle_mtl, VArray<HC_KEY>& segment_path)
{
	// get the various color attributes associated with faces in this segment
	//	float materialOpacity = 1.0f;
	char color_space[MVO_BUFFER_SIZE];
	float rgb[3];
	char color_type[128];

	HC_Open_Segment_By_Key(segment_key);

	char material_name[MVO_BUFFER_SIZE];
	sprintf(material_name, "line_material_%p", (void*)segment_key);
	int path_count = segment_path.Count();
	HC_KEY * path_array = (HC_KEY*)(&segment_path.GetData(0));

	fprintf(fhandle_mtl, "newmtl %s\n", material_name);

	// TODO: Use Compute_Color if the color_space is not RGB
	HC_PShow_One_Net_Color_By_Value(path_count, path_array, "ambient", 
		color_space, &rgb[0], &rgb[1], &rgb[2] );
	fprintf(fhandle_mtl, "Ka %f %f %f\n", rgb[0], rgb[1], rgb[2]);

	/*
	// we could have either a diffuse color or a texture
	// TODO: Ofcourse, we could have both, but let's put if off for a while
	if( HC_Show_Existence("color=(faces=diffuse)"))
	{
	// hmmm, do we have a color or a texture? Let's see how hard is this to figure out.
	char diffuse_face_color[MVO_BUFFER_SIZE];
	HC_Show_One_Color("faces=diffuse", diffuse_face_color );

	// TODO: This won't handle complex color viz. "greenish fruit" or diffuse2 channel
	if(HC_Compute_Color(diffuse_face_color, "RGB", rgb))
	materialDiffuse.Set(rgb[0], rgb[1], rgb[2]);
	else
	{
	materialDiffuse.Set(1.0f, 1.0f, 1.0f);

	bool has_diffuse_color = false;
	get_texture_for_segment(segment_key, &textureID, has_diffuse_color, rgb);
	if( has_diffuse_color )
	materialDiffuse.Set(rgb[0], rgb[1], rgb[2]);
	}
	}
	*/
	// TODO: I am not handling following
	// 1. Multiple texture channels. Only texture channel 0 will be exported
	// 2. (Faces=(diffuse=blue, red brick)) - In such case the attenuation color
	//		on texture0 (i.e. red) will only be used. diffuse color (blue) will be ignored
	// 3. Multiple texture channels and blending
	// 4. Blending of any texture channels with interpolation texture

	// do we want interpolation texture
	char texture_component[MVO_BUFFER_SIZE];
	char rgb_info[MVO_BUFFER_SIZE];

	HPoint * color_map = (HPoint*)0;
	HC_PShow_Net_Explicit_Color( path_count, path_array, "lines", "diffuse color", 
		rgb, texture_component, rgb_info );
	bool set_diffuse = true;
	if(streq(rgb_info, "findex")){
		int count; 
		int findex = (int)rgb[0];
		HC_PShow_Net_Color_Map_Count(path_count, path_array, &count);
		if(!color_map){
			color_map = new HPoint[count];
			HC_PShow_Net_Color_Map_By_Value(path_count, path_array, color_type, &count, color_map);
		}
		rgb[0] = color_map[findex].x;
		rgb[1] = color_map[findex].y;
		rgb[2] = color_map[findex].z;
	} 
	else if(streq(rgb_info, "ignore color")){
		set_diffuse = false;
	}
	fprintf(fhandle_mtl, "Kd %f %f %f\n", rgb[0], rgb[1], rgb[2]);

	HC_PShow_Net_Explicit_Color( path_count, path_array, "lines", "specular", 
		rgb, texture_component, rgb_info );

	bool set_specular = true;
	if(streq(rgb_info, "findex")){
		int count; 
		int findex = (int)rgb[0];
		HC_PShow_Net_Color_Map_Count(path_count, path_array, &count);
		if(!color_map){
			color_map = new HPoint[count];
			HC_PShow_Net_Color_Map_By_Value(path_count, path_array, color_type, &count, color_map);
		}				
		rgb[0] = color_map[findex].x;
		rgb[1] = color_map[findex].y;
		rgb[2] = color_map[findex].z;
	}
	else if(streq(rgb_info, "ignore color")){
		set_specular = false;
	}
	fprintf(fhandle_mtl, "Ks %f %f %f\n", rgb[0], rgb[1], rgb[2]);

	HC_PShow_Net_Explicit_Color( path_count, path_array, "lines", "transmission", 
		rgb, texture_component, rgb_info );

	bool set_transmission = true;
	if(streq(rgb_info, "findex")){
		int count; 
		int findex = (int) rgb[0];
		HC_PShow_Net_Color_Map_Count(path_count, path_array, &count);
		if(!color_map){
			color_map = new HPoint[count];
			HC_PShow_Net_Color_Map_By_Value(path_count, path_array, color_type, &count, color_map);
		}
		rgb[0] = color_map[findex].x;
		rgb[1] = color_map[findex].y;
		rgb[2] = color_map[findex].z;
	}
	else if(streq(rgb_info, "ignore color")){
		set_transmission = false;
	}
	fprintf(fhandle_mtl, "Tf %f %f %f\n", rgb[0], rgb[1], rgb[2]);
	fprintf(fhandle_mtl, "\n");

	if(color_map)
		delete [] color_map;

	HC_Close_Segment();

	return true;
}

static bool get_material_for_segment(HC_KEY segment_key, FILE* fhandle_mtl, VArray<HC_KEY>& segment_path, 
									 bool want_interpolation_texture = false)
{
	// get the various color attributes associated with faces in this segment
	//	float materialOpacity = 1.0f;
	char color_space[MVO_BUFFER_SIZE];
	float rgb[3];
	char color_type[128];

	HC_Open_Segment_By_Key(segment_key);

	char material_name[MVO_BUFFER_SIZE];
	sprintf(material_name, "face_material_%p", (void*)segment_key);
	int path_count = segment_path.Count();
	HC_KEY * path_array = (HC_KEY*)(&segment_path.GetData(0));

	fprintf(fhandle_mtl, "newmtl %s\n", material_name);
	//fprintf(fhandle_mtl, "\t");

	// TODO: Use Compute_Color if the color_space is not RGB
	HC_PShow_One_Net_Color_By_Value(path_count, path_array, "ambient", 
		color_space, &rgb[0], &rgb[1], &rgb[2] );
	fprintf(fhandle_mtl, "Ka %f %f %f\n", rgb[0], rgb[1], rgb[2]);

	/*
	// we could have either a diffuse color or a texture
	// TODO: Ofcourse, we could have both, but let's put if off for a while
	if( HC_Show_Existence("color=(faces=diffuse)"))
	{
	// hmmm, do we have a color or a texture? Let's see how hard is this to figure out.
	char diffuse_face_color[MVO_BUFFER_SIZE];
	HC_Show_One_Color("faces=diffuse", diffuse_face_color );

	// TODO: This won't handle complex color viz. "greenish fruit" or diffuse2 channel
	if(HC_Compute_Color(diffuse_face_color, "RGB", rgb))
	materialDiffuse.Set(rgb[0], rgb[1], rgb[2]);
	else
	{
	materialDiffuse.Set(1.0f, 1.0f, 1.0f);

	bool has_diffuse_color = false;
	get_texture_for_segment(segment_key, &textureID, has_diffuse_color, rgb);
	if( has_diffuse_color )
	materialDiffuse.Set(rgb[0], rgb[1], rgb[2]);
	}
	}
	*/
	// TODO: I am not handling following
	// 1. Multiple texture channels. Only texture channel 0 will be exported
	// 2. (Faces=(diffuse=blue, red brick)) - In such case the attenuation color
	//		on texture0 (i.e. red) will only be used. diffuse color (blue) will be ignored
	// 3. Multiple texture channels and blending
	// 4. Blending of any texture channels with interpolation texture

	// do we want interpolation texture
	char texture_component[MVO_BUFFER_SIZE];
	char rgb_info[MVO_BUFFER_SIZE];

	HPoint * color_map = (HPoint*)0;
	HC_PShow_Net_Explicit_Color( path_count, path_array, "faces", "diffuse color", 
		rgb, texture_component, rgb_info );
	bool set_diffuse = true;
	if(streq(rgb_info, "findex")){
		int count; 
		int findex = (int)rgb[0];
		HC_PShow_Net_Color_Map_Count(path_count, path_array, &count);
		if(!color_map){
			color_map = new HPoint[count];
			HC_PShow_Net_Color_Map_By_Value(path_count, path_array, color_type, &count, color_map);
		}
		rgb[0] = color_map[findex].x;
		rgb[1] = color_map[findex].y;
		rgb[2] = color_map[findex].z;
	} 
	else if(streq(rgb_info, "ignore color")){
		set_diffuse = false;
	}
	fprintf(fhandle_mtl, "kd %f %f %f\n", rgb[0], rgb[1], rgb[2]);

	HC_PShow_Net_Explicit_Color( path_count, path_array, "faces", "specular", 
		rgb, texture_component, rgb_info );

	bool set_specular = true;
	if(streq(rgb_info, "findex")){
		int count; 
		int findex = (int)rgb[0];
		HC_PShow_Net_Color_Map_Count(path_count, path_array, &count);
		if(!color_map){
			color_map = new HPoint[count];
			HC_PShow_Net_Color_Map_By_Value(path_count, path_array, color_type, &count, color_map);
		}				
		rgb[0] = color_map[findex].x;
		rgb[1] = color_map[findex].y;
		rgb[2] = color_map[findex].z;
	}
	else if(streq(rgb_info, "ignore color")){
		set_specular = false;
	}
	fprintf(fhandle_mtl, "Ks %f %f %f\n", rgb[0], rgb[1], rgb[2]);

	HC_PShow_Net_Explicit_Color( path_count, path_array, "faces", "transmission", 
		rgb, texture_component, rgb_info );

	bool set_transmission = true;
	if(streq(rgb_info, "findex")){
		int count; 
		int findex = (int) rgb[0];
		HC_PShow_Net_Color_Map_Count(path_count, path_array, &count);
		if(!color_map){
			color_map = new HPoint[count];
			HC_PShow_Net_Color_Map_By_Value(path_count, path_array, color_type, &count, color_map);
		}
		rgb[0] = color_map[findex].x;
		rgb[1] = color_map[findex].y;
		rgb[2] = color_map[findex].z;
	}
	else if(streq(rgb_info, "ignore color")){
		set_transmission = false;
	}
	fprintf(fhandle_mtl, "Tf %f %f %f\n\n", rgb[0], rgb[1], rgb[2]);

	if(color_map)
		delete [] color_map;

	if(want_interpolation_texture)
	{
		static int interp_tex_no = 1;
		sprintf(texture_component,"interpolation_texture_%d", interp_tex_no++);
		get_interpolation_texture_for_segment(fhandle_mtl, segment_key, texture_component, segment_path);
	}
	else
	{
		bool is_environ_map = false; 
		// check if we have a environment texture
		HC_PShow_Net_Explicit_Color( path_count, path_array, "faces", "environment", 
			rgb, texture_component, rgb_info );

		if( !strieq("", texture_component) )
		{
			// we have a texture
			is_environ_map = true;
			get_texture_for_segment(fhandle_mtl, segment_key, texture_component, segment_path, is_environ_map);
		}

		// check if we have a diffuse texture set
		HC_PShow_Net_Explicit_Color( path_count, path_array, "faces", "diffuse texture = 0", 
			rgb, texture_component, rgb_info );

		if( !strieq("", texture_component) )
		{
			// we have a texture
			is_environ_map = false; 
			get_texture_for_segment(fhandle_mtl, segment_key, texture_component, segment_path, is_environ_map);
		}
	}
	HC_Close_Segment();

	return true;
}

static void export_segment(HC_KEY segment_key, FILE* fhandle, FILE* fhandle_mtl, char *face_material_name, 
						   char *line_material_name,
						   VArray<HC_KEY>& segment_path) 
{
	//char *search_types = new char[MVO_BUFFER_SIZE];
	//char *group_name = new char[MVO_BUFFER_SIZE];

	HC_KEY style_key;
	char search_types[MVO_BUFFER_SIZE];
	char group_name[MVO_BUFFER_SIZE];
	char local_face_material_name[MVO_BUFFER_SIZE];
	char local_line_material_name[MVO_BUFFER_SIZE];
	float h_net_matrix[4][4];

	// We are creating OBJ groups equivalent to our segments  
	sprintf(group_name, "segment_%p", (void*)segment_key);
	fprintf(fhandle, "g %s\n\n", group_name);
	//	delete []group_name;

	HC_Open_Segment_By_Key(segment_key);
	if(fhandle_mtl)
	{
		// Convert the color attributes
		char type[MVO_BUFFER_SIZE];
		bool has_relevant_style = false;
		strcpy(local_face_material_name, face_material_name);
		if( HC_Show_Existence("color=faces") /*|| ( *face_material_name == 0) */)
		{
			get_material_for_segment(segment_key, fhandle_mtl, segment_path);
			sprintf(local_face_material_name, "face_material_%p", (void*)segment_key);
		}
		else
		{
			HC_Begin_Contents_Search(".", "styles");
			while (HC_Find_Contents (type, &style_key))
			{
				style_key = HC_KShow_Style_Segment (style_key);
				if (HC_Show_Existence_By_Key( style_key, "color=faces")) 
				{
					has_relevant_style = true;
					break;
				}
			}
			HC_End_Contents_Search();

			if( has_relevant_style == true )
			{
				get_material_for_segment(segment_key, fhandle_mtl, segment_path);
				sprintf(local_face_material_name, "face_material_%p", (void*)segment_key);
			}
		}


		//strcpy(local_line_material_name, line_material_name);
#ifndef HOBJ_EXPORT_LINES
		strcpy(local_line_material_name, line_material_name);
		if( HC_Show_Existence("color=lines") /*|| (*line_material_name == 0)*/)
		{
			get_material_for_line(segment_key, fhandle_mtl, segment_path);
			sprintf(local_line_material_name, "line_material_%p", (void*)segment_key);
		}
		else
		{
			HC_Begin_Contents_Search(".", "styles");
			while (HC_Find_Contents (type, &style_key))
			{
				style_key = HC_KShow_Style_Segment (style_key);
				if (HC_Show_Existence_By_Key( style_key, "color=lines")) 
				{
					has_relevant_style = true;
					break;
				}
			}
			HC_End_Contents_Search();

			if( has_relevant_style == true )
			{
				get_material_for_line(segment_key, fhandle_mtl, segment_path);
				sprintf(local_line_material_name, "line_material_%p", (void*)segment_key);
			}
		}
#else
		strcpy(local_line_material_name, line_material_name);
#endif // HOBJ_EXPORT_LINES

		/*if( HC_Show_Existence("rendering options = (color index interpolation = (faces=on))")) 
		{
		get_material_for_segment(segment_key, fhandle_mtl, segment_path, true);
		sprintf(local_face_material_name, "face_material_%p", (void*)segment_key);
		}
		else
		{
		HC_Begin_Contents_Search(".", "styles");
		while (HC_Find_Contents (type, &style_key))
		{
		style_key = HC_KShow_Style_Segment (style_key);
		if (HC_Show_Existence_By_Key( style_key, "rendering options = (color index interpolation = (faces=on))")) 
		{
		has_relevant_style = true;
		break;
		}
		}
		HC_End_Contents_Search();

		if( has_relevant_style == true )
		{
		get_material_for_segment(segment_key, fhandle_mtl, segment_path, true);
		sprintf(local_face_material_name, "face_material_%p", (void*)segment_key);
		}
		}*/
	}
	//Get the net modeling matrix. As there is nothing like modelling matrix in OBJ. We will get the modelling matrix 
	//and later when we query points for different geometries we will transform those points with this modelling matrix
	int path_count = segment_path.Count();
	HC_KEY * path_array = (HC_KEY*)(&segment_path.GetData(0));
	HC_PShow_Net_Modelling_Matrix 	(path_count, path_array, &h_net_matrix[0][0]);

	HC_Close_Segment();

	// search subsegments and includes by default
	// TODO: really? What if "everything=off"
	char	line_vis[MVO_BUFFER_SIZE], face_vis[MVO_BUFFER_SIZE];

	HC_KEY	*key_path_array = (HC_KEY*)(&segment_path.GetData(0));

	HC_Open_Segment_By_Key(segment_key);
	char type[MVO_BUFFER_SIZE];
	HC_KEY	new_key;

#ifndef HOBJ_EXPORT_LINES
	HC_PShow_One_Net_Visibility(segment_path.Count(), key_path_array, "lines", line_vis);
#else
	strcpy(line_vis, "off");
#endif

	if(streq(line_vis, "on"))
	{
		strcpy(search_types,"lines, polylines, nurbs curves, circular arcs, elliptical arcs, markers, circles, ellipses");

		HC_Begin_Contents_Search (".", search_types); 
		while (HC_Find_Contents (type, &new_key)) 
		{
			if(strcmp(local_line_material_name, current_line_mat_name))
			{
				fprintf(fhandle, "usemtl %s\n\n", local_line_material_name);
				strcpy(current_line_mat_name, local_line_material_name);
			}

			// TODO: other geometry types?
			if (streq(type, "nurbs curve") || 
				streq(type, "circular arc") || 
				streq(type, "elliptical arc") ) 
			{
				export_line_curve(new_key, fhandle, h_net_matrix);
			}
			else if (streq(type, "marker")) 
			{
				export_point(new_key, fhandle, h_net_matrix);
			}
			else if (streq(type, "line")) 
			{
				export_line(new_key, fhandle, h_net_matrix);
			}
			else if (streq(type, "polyline")) 
			{
				export_polyline(new_key, fhandle, h_net_matrix);
			}

			else if (streq(type, "circle") || streq(type, "ellipse") )
			{
				export_line_curve(new_key, fhandle, h_net_matrix);
			}
		}
		HC_End_Contents_Search ();
	}

	HC_PShow_One_Net_Visibility(segment_path.Count(), key_path_array, "faces", face_vis);
	if(streq(face_vis, "on"))
	{	
		strcpy(search_types,"shells, meshes, cylinders, polycylinders, spheres, nurbs surfaces, text, polygons");

		HC_Begin_Contents_Search (".", search_types); 
		while (HC_Find_Contents (type, &new_key)) 
		{
			if(strcmp(local_face_material_name, current_face_mat_name))
			{
				fprintf(fhandle, "usemtl %s\n\n", local_face_material_name);
				strcpy(current_face_mat_name, local_face_material_name);
			}

			if (streq(type, "polygon") )
			{
				if(streq(face_vis, "on"))
					export_polygon(new_key, fhandle, h_net_matrix);
			}

			else if (streq(type, "shell")) 
			{
				export_shell(new_key, fhandle, h_net_matrix);
			}
			else if (streq(type, "mesh")) 
			{
				export_mesh(new_key, fhandle, h_net_matrix);
			}
			else if (  streq(type, "cylinder") || streq(type, "polycylinder")
				|| streq(type, "sphere")   || streq(type, "nurbs surface") ) 
			{
				HC_KEY shell_eq = HC_Generate_Shell_From_Geometry(new_key, "");
				export_shell(shell_eq, fhandle, h_net_matrix, new_key);
				HC_Delete_By_Key(shell_eq);
			}
			/*else if (streq(type, "text")) 
			{
			export_shell(new_key, fhandle, h_net_matrix);
			}*/

		}
		HC_End_Contents_Search ();
	}

	strcpy(search_types, "segments, includes");
	//char type[MVO_BUFFER_SIZE];
	//HC_KEY	new_key;
	HC_Begin_Contents_Search (".", search_types); 
	while (HC_Find_Contents (type, &new_key)) 
	{
		//delete []search_types;
		if (strstr (type, "segment")) 
		{
			segment_path.InsertAt(new_key, 0);
			export_segment(new_key, fhandle, fhandle_mtl, local_face_material_name, local_line_material_name, segment_path);
			//if(strcmp(current_mat_name, material_name))
			//{
			//	fprintf(fhandle, "usemtl %s\n\n", material_name);
			//	strcpy(current_mat_name, material_name);
			//}
			segment_path.RemoveAt(0);
		}
		else if (strstr("include", type))
		{
			// we are going to take a include route, accumulate the owner seg
			// into the path

			HC_KEY includee = HC_KShow_Include_Segment(new_key);

			segment_path.InsertAt(new_key, 0);
			segment_path.InsertAt(includee, 0);

			export_segment( includee, fhandle, fhandle_mtl, local_face_material_name, local_line_material_name, segment_path);

			// pop out the owner from the segment path
			segment_path.RemoveAt(0);
			segment_path.RemoveAt(0);
		}
	}
	HC_End_Contents_Search ();

	HC_Close_Segment();
}

//static void strRev(char *s)
//{
//	for(char *end = s + (strlen(s) - 1); (end > s) ; (*s++) ^= (*end) ^=(*s) ^= (*end--));
//}

static bool Hoops2OBJ(const wchar_t *filename, HC_KEY model_segment_key, HOutputHandlerOptions * options = 0)
{
	wchar_t file_mtl[MVO_BUFFER_SIZE];
	//	char mat_file_name[MVO_BUFFER_SIZE];
	wcscpy(file_mtl, filename);
	wcscpy(texture_file_name, filename);

	VArray<HC_KEY>	seg_path;
	FILE *fhandle = wfopen(filename, L"wt");

	if((!fhandle))
	{
		ASSERT( !"Failed to open file");
		return false;
	}

	wchar_t *path = file_mtl;
	wchar_t *end;
	//char *q = mat_file_name;

	// Create a mtl file in which all the color data is loaded. We have created the mtl file with the same name 
	// as that of obj file and in the same directory.
	/* search for end of string */
	for(end=path; *end; )
		end++;
	path = end;
	*--path = L'l'; *--path = L't'; *--path = L'm';

	FILE *fhandle_mtl = wfopen(file_mtl, L"wt");

	// OBJ uses a Cartesian, right-handed, 3-dimensional coordinate system. 
	HC_Open_Segment_By_Key(model_segment_key);
	HC_Set_Handedness("Right");
	HC_Close_Segment();

	// do we have a view for this export?
	HBaseView * pBaseView = 0;
	if(options && options->m_pHBaseView)
	{
		pBaseView = options->m_pHBaseView;
		seg_path.Append(pBaseView->GetIncludeLinkKey());
		seg_path.Append(pBaseView->GetViewKey());
	}

	// add the model key to the path array
	seg_path.InsertAt(model_segment_key, 0);

	// In the OBJ file the first step is to load the .mtl file
	while(*path != '\\' && *path != '/'){path--;}
	path++;

	if(fhandle_mtl)
		fprintf (fhandle, "mtllib %s\n\n", (char*)H_UTF8(path).encodedText());

	char face_material_name[MVO_BUFFER_SIZE];
	char line_material_name[MVO_BUFFER_SIZE];

	memset(face_material_name, 0, MVO_BUFFER_SIZE);
	memset(line_material_name, 0, MVO_BUFFER_SIZE);

	if(pBaseView)
	{

		sprintf(face_material_name, "face_material_%p", (void*)(pBaseView->GetSceneKey()));
		get_material_for_segment(pBaseView->GetSceneKey(), fhandle_mtl, seg_path);


		sprintf(line_material_name, "line_material_%p", (void*)(pBaseView->GetSceneKey()));
		get_material_for_line(pBaseView->GetSceneKey(), fhandle_mtl, seg_path);

	}

	// Export the segments and their contents.
	export_segment(model_segment_key, fhandle, fhandle_mtl, face_material_name, line_material_name, seg_path);

	fclose(fhandle);
	if(fhandle_mtl)
		fclose(fhandle_mtl);
	return true;
}
