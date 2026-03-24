// base_stream_2d.cpp : Defines the entry point for the console application.
//


#include "BStream.h"
#include "BOpcodeShell.h"
#include <stdio.h>

#define WIDTH 128
#define HEIGHT 128
#define countof(x) (int)(sizeof(x)/sizeof(x[0]))


class HPoint 
{ 
public:
    float        x;	
    float        y;	
    float        z;	
    inline void Set(float X,float Y,float Z=0.0) { x=X,y=Y,z=Z; }

}; 
const float PI=3.1415926f;

float pts[15];



static void CreateRectangle( float x0, float y0, float x1, float y1)
{
    pts[0] = x0;   pts[1] = y0;   pts[2] = 0.0F;
    pts[3] = x0;   pts[4] = y1;   pts[5] = 0.0F;
    pts[6] = x1;   pts[7] = y1;   pts[8] = 0.0F;
    pts[9] = x1;   pts[10]= y0;   pts[11]= 0.0F;
    pts[12]= x0;   pts[13]= y0;   pts[14]= 0.0F;
}

static void WriteObject(BBaseOpcodeHandler * handler, BStreamFileToolkit * tk, FILE * fp,
                        char * buffer, int size) 
{
    TK_Status status;

    // ask the toolkit to write out the object; the toolkit will write out as much as
    // the current buffer can hold
    status = handler->Write(*tk);

    // if there is still more data left to write; we have to loop through 
    // generating and writing buffers of data until we're done
    while (status == TK_Pending) 
    {
        // due to compression, preparing a new buffer might immediately fill that buffer
        // so we need an extra check to possibly export that buffer and prepare a new buffer
        while (status == TK_Pending) 
        {
            // ask the toolkit how much of the buffer is currently filled
            // this will normally be the same as the buffer size that we passed in
            int count = tk->CurrentBufferLength();

            // write the current out to our file since this example deals with 
            // exporting a file; however, instead of writing to a file, the buffer of
            // data could be sent to an application data-structure, or transmitted
            // over a network ('streamed'), etc...
            fwrite(buffer, sizeof (char), count, fp);

            // tell the toolkit where it can resume writing data; in this case, we
            // can reuse the same buffer once we're done with it
            status = tk->PrepareBuffer(buffer, size);
        }

        // ask the toolkit to continue trying to write out the object's data
        status = handler->Write(*tk);
    }
}

static void CreateSphere(float *center, float radius, int numsides, 
    int *pcount_out, float **points_out, int *flistlen_out, int **faces_out )
{
    int i, j, htile, wtile, pts_cnt, flist_cnt;
    float theta, phi, dt, dp, x, y, z;
    HPoint *points;
    int *faces;

    htile = numsides/2;
    wtile = numsides;
    pts_cnt = htile*wtile;
    points = new HPoint[ pts_cnt ];
    // faces need wtile + 1 numbers to specify each sphere end cap
    // and 5*numsides numbers for each strip between the end caps.
    // There will be numsides/2-1 of these strips.
    flist_cnt = (wtile+1)*2 + 5*(htile-1)*wtile;
    faces = new int[ flist_cnt ];

    dt = 2.0f * PI / wtile;
    dp = 1.0f * PI / (htile+1);
    phi = dp;
    for( i = 0 ; i < htile ; i++ ) {
        theta = 0;
        for( j = 0 ; j < wtile ; j++ ) {
            x = radius * (float)cos(theta) * (float)sin(phi);
            y = radius * (float)cos(phi);
            z = radius * (float)sin(theta) * (float)sin(phi);
            points[ i*wtile + j ].Set( center[0] + x, center[1] + y, center[2] + z );
            theta += dt;
        }
        phi += dp;
    }

    // set the number of points in the end caps of the sphere in the connectivity list
    faces[5*(htile-1)*wtile] = wtile;
    faces[5*(htile-1)*wtile+wtile+1] = wtile;
    for (i = 0; i < (htile-1); i++)
    {
        for (j = 0; j < wtile; j++)
        {
            // generate the connectivity list for the side quads of the cylinder
            faces[(i*wtile + j)*5] = 4; // number of points in this polygon
            faces[(i*wtile + j)*5+1]=i*wtile + j;
            faces[(i*wtile + j)*5+2]=i*wtile + (j+1)%wtile; //next point along circle; wrap at numsides
            faces[(i*wtile + j)*5+3]=(i+1)*wtile + (j+1)%wtile;  // correcsponding point at top of cylinder
            faces[(i*wtile + j)*5+4]=(i+1)*wtile + j; //next point along circle; wrap at numsides
        }
    }
    for (j = 0; j < wtile; j++)
    {
        // generate the connectivity list for the ends of the cylinder
        faces[(htile-1)*wtile*5 + j + 1]= (wtile - j - 1);
        faces[(htile-1)*wtile*5 + j + 1 + wtile + 1]= wtile*(htile-1) + j;
    }
    *pcount_out = pts_cnt;
    *points_out = (float *)points;
    *flistlen_out = flist_cnt;
    *faces_out = (int *)faces;
}

class TK_My_Lod_Shell: public TK_Shell
{
public:
    TK_My_Lod_Shell():TK_Shell() { };
    ~TK_My_Lod_Shell(){ Reset(); };

    TK_Status Interpret (BStreamFileToolkit & tk, long key, int lod) alter 
    {
        TK_Status status = TK_Normal;
        HPoint center;
        float radius = 1.0f;
        float bbox[6];
        float *points, *normals, *indices;
        int p_count, f_count, flist_length, *flist, i;
        bool is_firstpass;

        /* Take the write options in toolkit and from them compute an initial value for 
         * this opcode's suboption */
        is_firstpass = (lod==2);
        InitSubop( tk, lod, is_firstpass );
		/* Turn off default tristrip option if your database does not have good tristrips that you'd 
		 * like to use as the face list */
        SetSubop( ~TKSH_TRISTRIPS & GetSubop() );
        SetLodLevel( lod );
        SetKey( tk, key );

        if( key == 13)
            center.Set(0.0f,0.0f,0.0f);
        else
            center.Set(3.0f,0.0f,0.0f);

        // This is where the bounding box of the shell needs to be determined.  The 
        // bounding box is used for the local vertex compression.  In this example, we set it to the bounding
        // box of the sphere we're creating.
        bbox[0] = center.x - 1.0f;
        bbox[1] = center.y - 1.0f;
        bbox[2] = center.z - 1.0f;
        bbox[3] = center.x + 1.0f;
        bbox[4] = center.y + 1.0f;
        bbox[5] = center.z + 1.0f;
        SetBounding( bbox );

        // if the level=0, then we're exporting the original shell if we're spitting out the full resolution version
        if (GetLodLevel() == 0) {
            // This is where you will go out to your gfx database and get the data defining the shell.
            // We're using a simple sphere generator to create a point cloud and some connectivity
            CreateSphere((float *)&center, radius, 30, &p_count, &points, &flist_length, &flist);
            SetPoints(p_count, points);
            SetFaces(flist_length, flist);

            normals = new float[ 3 * p_count ];
            for ( i = 0 ; i < p_count * 3 ; i += 3) {
                normals[ i + 0 ] = points[ i + 0 ] - center.x;
                normals[ i + 1 ] = points[ i + 1 ] - center.y;
                normals[ i + 2 ] = points[ i + 2 ] - center.z;
            }
            SetVertexNormals( normals );
            delete [] normals;

            // now let's do the same for the face level coloring
            f_count = (flist_length - 2*30 - 2)/5 + 2;
            indices = new float[ f_count ];
            for ( i = 0 ; i < f_count ; i++ ) {
                indices[i] = (float)(i%4);
            }
            SetFaceIndices( indices );
            delete [] indices;
            delete [] points;
            delete [] flist;
        }
        else if (GetLodLevel() == 1) {
            // create a LOD version of the sphere where numsides=12
            CreateSphere((float *)&center, radius, 12, &p_count, &points, &flist_length, &flist);
            SetPoints(p_count, points);
            SetFaces(flist_length, flist);
            delete [] points;
            delete [] flist;
        }
        else {
            // LOD2 is a collection of non-shells consisting of exactly one circle
            TK_Circle *circhandler;

            circhandler = new TK_Circle( TKE_Circle );
            circhandler = (TK_Circle *)circhandler;
            circhandler->SetStart( center.x + radius, center.y, center.z );
            circhandler->SetMiddle( center.x - radius, center.y, center.z );
            circhandler->SetEnd( center.x, center.y + radius, center.z );
            AppendObject( tk, circhandler );
        }
        return status;
    }

    /* Here we clean up the mess we might have made with non-shell LODs. */
    void Reset() {
        BBaseOpcodeHandler *handler;
        while((handler = PopObject()) != NULL) {
            delete handler;
        }
        TK_Shell::Reset();
    }
};


class TK_My_Shell: public TK_Shell
{
public:
    TK_My_Shell():TK_Shell() { };
    ~TK_My_Shell(){ Reset(); };

    /* Normally you would use the given key to go look up this shell from some
     * graphics database or another (possibly but not necessarily HOOPS/3dgs).
     * for the purposes of this demo, however, we just create the data on the spot
     * with hard-code. */
    TK_Status Interpret (BStreamFileToolkit & tk, ID_Key key, int lod) alter 
    {
        TK_Status status = TK_Normal;
        const float points[8][3] = {
            {    0,    0, 0 },
            {    0,    1, 0 },
            {    1,    1, 0 },
            {    1,    0, 0 },
            { 0.2f, 0.2f, 0 },
            { 0.2f, 0.8f, 0 },
            { 0.8f, 0.8f, 0 },
            { 0.8f, 0.2f, 0 }
        };
        const int faces[] = { 4, 0, 1, 2, 3, -4, 4, 5, 6, 7 };
        int index;
        bool is_firstpass = tk.KeyToIndex( key, index ) == TK_NotFound;

        InitSubop( tk, lod, is_firstpass );
        SetSubop( GetSubop() & ~TKSH_TRISTRIPS );

        //allocate and initialize the vertices
        SetPoints( countof(points), (const float *)points );
        //allocate and initialize the face indices
        SetFaces( countof(faces), faces );
        //simply reuse the world space coordinates as texture coordinates
        SetVertexParameters( (const float *)points ); 
        return status;
    }

    void Reset() {
        TK_Shell::Reset();
    }
};  // end declaration and definition of TK_My_Shell 

class TK_My_Cube_Shell: public TK_Shell
{
public:
    TK_My_Cube_Shell():TK_Shell() { };
    ~TK_My_Cube_Shell(){ Reset(); };

    /* Normally you would use the given key to go look up this shell from some
     * graphics database or another (possibly but not necessarily HOOPS/3dgs).
     * for the purposes of this demo, however, we just create the data on the spot
     * with hard-code. */
    TK_Status Interpret (BStreamFileToolkit & tk, ID_Key key, int lod) alter 
    {
        TK_Status status = TK_Normal;

        const float shell_points[8][3] = {
            { 0, 0, 0 },
            { 2, 0, 0 },
            { 2, 2, 0 },
            { 0, 2, 0 },
            { 0, 0, 2 },
            { 2, 0, 2 },
            { 2, 2, 2 },
            { 0, 2, 2 }
        };
       // const float shell_points[]= { , , ,, , , };
        const int shell_faces[] = { 4,0, 1, 2, 3, 4, 1, 5, 6, 2, 4, 5, 4, 7, 6, 4, 4, 0, 3, 7, 4, 3, 2, 6, 7, 4, 0, 4, 5, 1};
 
	//	const int faces[] = { 4, 0, 1, 2, 3, -4, 4, 5, 6, 7 };
        int index;
        bool is_firstpass = tk.KeyToIndex( key, index ) == TK_NotFound;

        InitSubop( tk, lod, is_firstpass );
        SetSubop( GetSubop() & ~TKSH_TRISTRIPS );

        //allocate and initialize the vertices
        SetPoints( countof(shell_points), (const float *)shell_points );
        //allocate and initialize the face indices
        SetFaces( countof(shell_faces), shell_faces );
        //simply reuse the world space coordinates as texture coordinates
        SetVertexParameters( (const float *)shell_points ); 

		const float face_color_idxs[] = { 0, 1, 2, 3, 3, 1 };
		SetFaceIndices(face_color_idxs);

        return status;
    }

    void Reset() {
        TK_Shell::Reset();
    }
};  // end declaration and definition of TK_My_Shell 

// This rather simplistic function simply creates a checkerboard pattern.  In any 
// real application, this kind of function would load a real image -- either from
// a file or from a graphics database.
void create_checkerboard( TK_Image *image, int width, int height, char *name )
{
    unsigned char *ptr;
    int i, j, black;

	image->SetPosition( 0, 0, 0 );
    image->SetSize( width, height );
    image->SetBytes( 3*width*height );
    ptr = (unsigned char *)image->GetBytes( );
    image->SetFormat( TKO_Image_RGB );
    image->SetFormat( image->GetFormat() | TKO_Image_Is_Named ); //xxx
    image->SetName( name );
    image->SetCompression( TKO_Compression_None ); //xxx
    for( j = 0 ; j < height ; j++ ) {
        for( i = 0 ; i < width ; i++ ) {
            //bitwise XOR the low bit of row/column divided by sixteen
            black = ((i / 16) & 0x1) ^ ((j / 16) & 0x1);
            if( black )
                ptr[0] = ptr[1] = ptr[2] = 128;
            else
                ptr[0] = ptr[1] = ptr[2] = 255;
            ptr += 3;
        }
    }
} // end function create_checkerboard


int main() 
{
    // create a new file toolkit object
    BStreamFileToolkit *mytoolkit = new BStreamFileToolkit;

    char mybuffer[4096];
    int size=4096;
    int count;


    FILE *flptr;

    // open a binary file called 'base_stream_2D.hsf' for writing
    flptr=fopen("base_stream_all.hsf", "wb");

    // tell the toolkit where to begin writing data; the size of the 'utility' buffer
    // can be anything; for this example, we use a 4k buffer
    mytoolkit->PrepareBuffer(mybuffer, size);

	//BBaseOpcodeHandler *handler;
	TK_Open_Segment				*open_seg_handler;
    TK_Point					*point_handler;
    TK_Polypoint				*line_handler;
    TK_Camera					*view_handler;
    TK_Color_RGB				*rgb_color_handler;
    TK_Visibility				*vis_handler;
	TK_Color					*color_handler;
	TK_Area_Light				*area_light_handler; 
	TK_Circle					*circle_handler;
	TK_Clip_Region				*clip_region_handler;
	TK_Close_Segment			*close_seg_handler ; 
//	TK_Color::channel			*color_channel_handler;
	TK_Color_By_Index			*color_Index_handler;
	TK_Color_Map				*color_map_handler;
	TK_Compression				*compression_handler;   
	TK_Cutting_Plane			*cutting_plane_handler;
	TK_Cylinder					*cylinder_handler;
	TK_Ellipse					*ellipse_handler;
	TK_Enumerated				*enumerated_handler;
	TK_Grid						*grid_handler;
	TK_Header					*header_handler;
	TK_Heuristics				*heuristic_handler;  
	TK_Image					*image_handler;
	TK_Line						*l_line_handler;
	TK_Line_Style				*line_style_handler;
	TK_Matrix					*matrix_handler;
	TK_NURBS_Curve				*nurbs_curve_handler;
	TK_NURBS_Surface			*nurbs_surface_handler;
	TK_PolyCylinder				*polycylinder_handler;
//	TK_PolyPolypoint			*polypolypoint_handler;
	TK_Referenced_Segment		*referenced_segment_handler;
	TK_Rendering_Options		*rendering_options_handler;
	TK_Selectability			*selectability_handler;
	TK_Shell					*shell_handler;
	TK_Size						*size_handler;
	TK_Spot_Light				*spot_light_handler;
	TK_Terminator				*terminator_handler;
	TK_Text						*text_handler;
	TK_Text_Font				*text_font_handler;
	TK_Texture					*texture_handler;
	TK_User_Options				*user_options_handler;
	TK_User_Value				*user_value_handler;
	TK_Sphere					*sphere_handler;
	TK_Window					*window_handler;
	TK_Named                    *named_handler;

// create a TK_Header object and export it's associated HSF objects,
    // which include the TKE_Comment and TKE_File_Info objects
    // TK_Header automatically formats the TKE_Comment to contain file version 
    // information.  
    header_handler = new TK_Header();
    WriteObject(header_handler, mytoolkit, flptr, mybuffer, size);
    delete header_handler;

	 // create a TK_Camera object to export a TKE_View opcode; this defines an initial
    // camera used to view the scene-graph contained in the file
    view_handler = new TK_Camera (TKE_View);
    //many apps have chosen to make the name "default" have special meaning -- that
    //it be used as the initial view.
    view_handler->SetView("default");
    view_handler->SetProjection(TKO_Camera_Perspective);
    view_handler->SetPosition(3.0, 0.0, -15.0);
    view_handler->SetTarget(3.0, 0.0, 0.0);
    view_handler->SetUpVector(1.0, 1.0, 0.0);
    view_handler->SetField(7.0, 7.0);
    WriteObject(view_handler, mytoolkit, flptr, mybuffer, size);
    delete view_handler;

    // export a TKE_Start_Compression object
    compression_handler = new TK_Compression(TKE_Start_Compression);
   // WriteObject(compression_handler, mytoolkit, flptr, mybuffer, size);
    delete compression_handler;


	
	// export a TKE_Open_Segment objec; the TK_Open_Segment opcode handler
    // automatically supports this opcode, so it does not need to be passed
    // into the constructor

    open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Cylinder");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_cylinder[] = { 0.1f, 0, 0 ,0,
								0, 0.1f, 0, 0,
								0, 0, 0.1f, 0,
							   -1, 0.66f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_cylinder);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		
////
		window_handler = new TK_Window();
		window_handler->SetWindow (-1.0, 1.0, -1.0, 1.0);
		WriteObject(window_handler, mytoolkit, flptr, mybuffer, size);
		delete window_handler;	

		enumerated_handler= new TK_Enumerated(TKE_Window_Pattern);
		enumerated_handler->SetIndex(5); 
		WriteObject(enumerated_handler, mytoolkit, flptr, mybuffer, size);
		delete enumerated_handler;	

		enumerated_handler= new TK_Enumerated(TKE_Window_Frame);
		enumerated_handler->SetIndex(1); 
		WriteObject(enumerated_handler, mytoolkit, flptr, mybuffer, size);
		delete enumerated_handler;	
///
		// export a TKE_Polyline object
		float cyl_axis[]={1.0, 0.0, 0.0, 0.0, 1.0, 0.0};
		float cyl_radius = 1.0;
		cylinder_handler = new TK_Cylinder();
        cylinder_handler->SetAxis (cyl_axis);
        cylinder_handler->SetRadius (cyl_radius);
        cylinder_handler->SetCaps (3);
		WriteObject(cylinder_handler, mytoolkit, flptr, mybuffer, size);
		delete cylinder_handler;

	// export a TKE_Close_Segment object; the TK_Close_Segment opcode handler
    // automatically supports this opcode, so it does not need to be passed
    // into the constructor
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

/////
    open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Polygon");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

			float mm_grid[] = {    0.1f, 0, 0 ,0,
								   0, 0.1f, 0, 0,
								   0, 0, 0.1f, 0,
								 -1, 3.25f, 0, 1 };

			matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
			matrix_handler->SetMatrix(mm_grid);
			WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
			matrix_handler->Reset();		

			// export a TKE_Polyline object
			HPoint grid_center;  						
			float ref1[]= {1.0f, 0.0f, 0.0f};
			float ref2[]= {0.0f, 0.4f, 0.0f};
			int c1 = 100; 
			int c2  = 200;
			grid_center.Set(0.0f,0.0f,0.0f);
			grid_handler = new TK_Grid(); 
			grid_handler-> SetOrigin(grid_center.x, grid_center.y, grid_center.z);
			grid_handler-> SetRef1 (ref1);
			grid_handler-> SetRef2 (ref2);
			grid_handler-> SetType(2);
			grid_handler-> SetCounts (c1, c2);
			WriteObject(grid_handler, mytoolkit, flptr, mybuffer, size);
			delete grid_handler;

	// export a TKE_Close_Segment object; the TK_Close_Segment opcode handler
    // automatically supports this opcode, so it does not need to be passed
    // into the constructor
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;
//////
	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Nurbs_Curve");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_nurbs_curve[] = {  0.1f, 0, 0 ,0,
									0, 0.1f, 0, 0,
									0, 0, 0.1f, 0,
									1,1.25f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_nurbs_curve);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

		// export a TKE_Polyline object

		int degree = 2;
		int control_count = 4;
		float nurb_points[] = {0, 0, 0, 3, 0, 0, 0, 3, 0, 3, 3, 0};  
		float weights[] =  {1, 1, 1};
		float knots[]= {1, 0.333333f, 0.333333f};
		float start = 0.1f; 
		float end=0.95f;
		nurbs_curve_handler = new TK_NURBS_Curve();
		nurbs_curve_handler->SetCurve (degree, control_count, nurb_points, 0, 0, 0, 1);
		nurbs_curve_handler->SetOptions(4);
		WriteObject(nurbs_curve_handler, mytoolkit, flptr, mybuffer, size);
		delete nurbs_curve_handler;

		user_options_handler= new TK_User_Options;
		user_options_handler->SetOptions("Company = TechSoft");
		WriteObject(user_options_handler, mytoolkit, flptr, mybuffer, size);
		delete user_options_handler;
			
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Nurbs_Surface");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_nurbs_surface[] = {  0.1f, 0, 0 ,0,
										0, 0.1f, 0, 0,
										0, 0, 0.1f, 0,
										1,1.25f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_nurbs_surface);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

		// export a TKE_Polyline object

		int sur_degree = 2;
		int sur_control_count = 4;
		float nurb_sur_points[] = {0,-4, 0, 4, -4, 0, 0, 4, 0, 0, 4, 0.25};  
//		float u_Knots = {0, 0, 1.33333, 1.33333};
//		float v_Knots = {0, 0, 1.28864, 1.28864};
	  	nurbs_surface_handler = new TK_NURBS_Surface();
		nurbs_surface_handler->SetSurface (1, 1, 2, 2, nurb_sur_points, 0, 0, 0);
		nurbs_surface_handler->SetOptions(4);
		WriteObject(nurbs_surface_handler, mytoolkit, flptr, mybuffer, size);
		delete nurbs_surface_handler;
	
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;
///
	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("MESH");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_nurbs_mesh[] = {  0.1f, 0, 0 ,0,
									0, 0.1f, 0, 0,
									0, 0, 0.1f, 0,
									1,1.25f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_nurbs_mesh);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

		// export a TKE_Polyline object

	//	int degree = 2;
	//	int control_count = 4;
	//	float nurb_points[] = {0, 0, 0, 3, 0, 0, 0, 3, 0, 3, 3, 0};  
	//	float weights[] =  {1, 1, 1};
	//	float knots[]= {1, 0.333333f, 0.333333f};
//		float start = 0.1f; 
//		float end=0.95f;
		nurbs_curve_handler = new TK_NURBS_Curve();
		nurbs_curve_handler->SetCurve (degree, control_count, nurb_points, 0, 0, 0, 1);
		WriteObject(nurbs_curve_handler, mytoolkit, flptr, mybuffer, size);
		delete nurbs_curve_handler;
	
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;
////
	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("?style library/style_test");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		rgb_color_handler = new TK_Color_RGB();
		rgb_color_handler->SetGeometry(1);
		rgb_color_handler->SetRGB(1.0, 0.0, 0.0);
		WriteObject(rgb_color_handler, mytoolkit, flptr, mybuffer, size);
		delete rgb_color_handler;	
	
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("PolyCylinder");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_polycylinder[] = { 0.1f, 0, 0 ,0,
									0, 0.1f, 0, 0,
									0, 0, 0.1f, 0,
									1,0.25f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_polycylinder);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

	
		referenced_segment_handler = new TK_Referenced_Segment(TKE_Style_Segment);
		referenced_segment_handler->SetSegment("?style library/style_test");
		WriteObject(referenced_segment_handler, mytoolkit, flptr, mybuffer, size);
		referenced_segment_handler->Reset();
		
		
		// export a TKE_Polyline object
		float polycil_pts[]={0, 0, 0, 1, 1, 1, 2, 2, 2 };
		float radii[]={1.0,2.0,3.0};
		float normal[3]={0,0,1.0};
		polycylinder_handler= new TK_PolyCylinder();
		polycylinder_handler->SetPoints(3, polycil_pts);
		polycylinder_handler->SetRadii (3, radii);
//		polycylinder_handler->SetCaps (3);
		polycylinder_handler->SetEndNormal(1,normal);
		WriteObject(polycylinder_handler, mytoolkit, flptr, mybuffer, size);
		delete polycylinder_handler;
	
		rendering_options_handler= new TK_Rendering_Options;
		rendering_options_handler->SetMask(2,2); 
		rendering_options_handler->SetHlrOptions(2);
		rendering_options_handler->SetSimpleShadow(2);
		WriteObject(rendering_options_handler, mytoolkit, flptr, mybuffer, size);
		delete rendering_options_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Area_light");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_area_light[] = {  0.1f, 0, 0 ,0,
									0, 0.1f, 0, 0,
									0, 0, 0.1f, 0,
									2,1.75f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_area_light);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		
		
		float area_light_pts[]={-1.0, -1.0, 0, 1.0, -1.0, 0, 0.25, 0, 0};
		area_light_handler = new TK_Area_Light();
		area_light_handler->SetPoints(3, area_light_pts);
		area_light_handler->SetOptions (0); 
		WriteObject(area_light_handler, mytoolkit, flptr, mybuffer, size);
		delete area_light_handler;	
	
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Shell");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_shell[] = {  0.1f, 0, 0 ,0,
								0, 0.1f, 0, 0,
								0, 0, 0.1f, 0,
								1,2.25f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_shell);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		
	
		shell_handler = new TK_My_Cube_Shell;
        shell_handler->Interpret(*mytoolkit, 13, 0);
        WriteObject(shell_handler, mytoolkit, flptr, mybuffer, size);
        delete shell_handler;

		float shell_colormap[]={1.0f,0.0f,1.0f,0.5f,0.3f,0.8f,0.2f,0.4f,0.7f,0.8f,0.8f,0.0f};
		color_map_handler = new TK_Color_Map;
		color_map_handler->SetValues(4, shell_colormap);
		WriteObject(color_map_handler, mytoolkit, flptr, mybuffer, size);
		delete color_map_handler;

		color_Index_handler = new TK_Color_By_Index(TKE_Color_By_Index);
		color_Index_handler->SetGeometry (TKO_Geo_Face);
		
		for(int i=0; i<=4; i++)
		{
		   color_Index_handler->SetIndex((int)shell_colormap[i]);
		}
		WriteObject(color_Index_handler, mytoolkit, flptr, mybuffer, size);
		delete color_Index_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Text");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_text[] = {    0.1f, 0, 0 ,0,
								0, 0.1f, 0, 0,
								0, 0, 0.1f, 0,
								-1,2.25f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_text);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

		// export a TKE_Polyline object
	//	HPoint text_center;
	//	float ellipse_major[]= {1.0, 0.0, 0.0};
	//	float ellipse_minor[]= {0.0, 0.4, 0.0};
		char string[]="abcd";
		float text_center[] = {0.0f,0.8f,0.0f};
		text_handler= new TK_Text(TKE_Text);
		text_handler->SetString(string);
		text_handler->SetPosition(text_center);
	//	text_handler->SetEncoding();
		WriteObject(text_handler, mytoolkit, flptr, mybuffer, size);
		delete text_handler;

		float text_spacing = 2;
		size_handler= new TK_Size(TKE_Text_Spacing);
		size_handler->SetSize(text_spacing); 
		WriteObject(size_handler, mytoolkit, flptr, mybuffer, size);
		delete size_handler;

		enumerated_handler= new TK_Enumerated(TKE_Text_Alignment);
		enumerated_handler->SetIndex(1); 
		WriteObject(enumerated_handler, mytoolkit, flptr, mybuffer, size);
		delete enumerated_handler;

		float text_path[]={0,1,0};
		point_handler = new  TK_Point(TKE_Text_Path);
		point_handler->SetPoint(text_path);
		WriteObject(point_handler, mytoolkit, flptr, mybuffer, size);
		delete point_handler;


		text_font_handler= new TK_Text_Font();
		text_font_handler->SetMask (TKO_Font_Bold );
		text_font_handler->SetValue(TKO_Font_Underline);
		text_font_handler->SetNames ("arial");
		text_font_handler->SetSize (0.065f);
		text_font_handler->SetSizeUnits (TKO_Font_Size_Object);
//		text_font_handler->SetRotation (float r)();
//		text_font_handler->SetSlant (float s)
//		text_font_handler->SetWidthScale (float s
//		text_font_handler->SetExtraSpace (float s)
//		text_font_handler->SetTransforms (int t);
		WriteObject(text_font_handler, mytoolkit, flptr, mybuffer, size);
		delete text_font_handler;
	
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;


    open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Polygon");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_polygon[] = { 0.1f, 0, 0 ,0,
								0, 0.1f, 0, 0,
								0, 0, 0.1f, 0,
								-2,2.25f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_polygon);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

		// export a TKE_Polyline object
		float polygon_pts[]={-1.0, -1.0, 0, 1.0, -1.0, 0, 0.25, 0, 0, 1.0, 1.0, 0,-1.0, 1.0, 0,-0.25, 0, 0};
		line_handler= new TK_Polypoint(TKE_Polygon);
		line_handler->SetPoints(6, polygon_pts);
		WriteObject(line_handler, mytoolkit, flptr, mybuffer, size);
		delete line_handler;

		float edge_weight = 5.0;
		size_handler= new TK_Size(TKE_Edge_Weight);
		size_handler->SetSize(edge_weight); 
		WriteObject(size_handler, mytoolkit, flptr, mybuffer, size);
		delete size_handler;

		int edge_pattern = 1;
		named_handler= new TK_Named(TKE_Edge_Pattern);
		named_handler->SetIndex(edge_pattern); 
		WriteObject(named_handler, mytoolkit, flptr, mybuffer, size);
		delete named_handler;
		
		enumerated_handler= new TK_Enumerated(TKE_Face_Pattern);
		enumerated_handler->SetIndex(5); 
		WriteObject(enumerated_handler, mytoolkit, flptr, mybuffer, size);
		delete enumerated_handler;	

		enumerated_handler= new TK_Enumerated(TKE_Handedness);
		enumerated_handler->SetIndex(1); 
		WriteObject(enumerated_handler, mytoolkit, flptr, mybuffer, size);
		delete enumerated_handler;

		int user_value = 24;
		user_value_handler= new TK_User_Value();
		user_value_handler->SetValue (user_value); 
		WriteObject(user_value_handler, mytoolkit, flptr, mybuffer, size);
		delete user_value_handler;

		selectability_handler= new TK_Selectability;
		selectability_handler->SetGeometry (TKO_Geo_Face );
		selectability_handler->SetDown (TKO_Geo_Face);
	//	selectability_handler->SetUp ("Geometry = Nurbs Curve,Modelling matrix = Set");
	//	selectability_handler->SetGeometry ("Geometry = Nurbs Curve,Modelling matrix = Set");
		WriteObject(selectability_handler, mytoolkit, flptr, mybuffer, size);
		delete selectability_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("PolyPolyline");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_PolyPolyline[] = { 0.1f, 0, 0 ,0,
								0, 0.1f, 0, 0,
								0, 0, 0.1f, 0,
								-1,2.25f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_PolyPolyline);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		
/*
		// export a TKE_Polyline object
		float mm_PolyPolyline_pts[]={-2.0, -2.0, 0, 2.0, -2.0, 0, 2.25, 0, 0, 2.0, 2.0, 0,-2.0, 2.0, 0,-2.25, 0, 0};
		polypolypoint_handler= new TK_PolyPolypoint(TKE_PolyPolyline);
		polypolypoint_handler->SetPoints (6, polygon_pts);
		polypolypoint_handler->SetLengths  (6, polygon_pts);
		WriteObject(polypolypoint_handler, mytoolkit, flptr, mybuffer, size);
		delete polypolypoint_handler;
*/
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

    open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Ellipse");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_ellipse[] = {  0.1f,  0,  0, 0,
								0,  0.1f,  0, 0,
								0,  0,0.1f, 0,
							   -2, 1.66f,  0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_ellipse);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		
			
		// export a TKE_Ellipse object
		HPoint ellipse_center;
		float ellipse_major[]= {1.0f, 0.0f, 0.0f};
		float ellipse_minor[]= {0.0f, 0.4f, 0.0f};
		ellipse_center.Set(0.0f,0.0f,0.0f);
		ellipse_handler = new TK_Ellipse(TKE_Ellipse); 
        ellipse_handler-> SetCenter(ellipse_center.x, ellipse_center.y, ellipse_center.z);
		ellipse_handler-> SetMajor (ellipse_major);
		ellipse_handler-> SetMinor (ellipse_minor);
		WriteObject(ellipse_handler, mytoolkit, flptr, mybuffer, size);
		delete ellipse_handler;

	
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Styled_line");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_styled_line[] = {  0.1f,  0,  0, 0,
									0,  0.1f,  0, 0,
									0,  0,0.1f, 0,
								   -2, 2.66f,  0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_styled_line);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		
					
	    line_style_handler = new TK_Line_Style; 
        line_style_handler-> SetName ("my_style");
		line_style_handler-> SetDefinition ("dash");
		WriteObject(line_style_handler, mytoolkit, flptr, mybuffer, size);
		delete line_style_handler;

		float line_style_pts[]={-1.0, 0.0, 0.0, 5.0, 0.0, 0.0};
		l_line_handler = new TK_Line;
		l_line_handler->SetPoints(line_style_pts);
		WriteObject(l_line_handler, mytoolkit, flptr, mybuffer, size);
		delete l_line_handler;

		named_handler= new TK_Named(TKE_Line_Pattern);
		named_handler->SetName("my_style");
		named_handler->SetIndex(11); 
		WriteObject(named_handler, mytoolkit, flptr, mybuffer, size);
		delete named_handler;

		int line_pattern = 11;
		named_handler= new TK_Named(TKE_Line_Pattern);
		named_handler->SetIndex(line_pattern); 
		WriteObject(named_handler, mytoolkit, flptr, mybuffer, size);
		delete named_handler;
	
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Elliptical Arc");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_elliptical_arc[] = {  0.1f,  0,  0, 0,
										0,  0.1f,  0, 0,
										0,   0, 0.1f, 0,
									   -1,  1.25f,  0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_elliptical_arc);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		
			
		// export a TKE_Ellipse object
	//	HPoint ellipse_center;
	//	float ellipse_major[]= {1.0, 0.0, 0.0};
	//	float ellipse_minor[]= {0.0, 0.4, 0.0};
	//	ellipse_center.Set(0.0f,0.0f,0.0f);
		ellipse_handler = new TK_Ellipse(TKE_Elliptical_Arc); 
        ellipse_handler-> SetCenter(ellipse_center.x, ellipse_center.y, ellipse_center.z);
		ellipse_handler-> SetMajor (ellipse_major);
		ellipse_handler-> SetMinor (ellipse_minor);
		ellipse_handler-> SetLimits (0,0.5);
		WriteObject(ellipse_handler, mytoolkit, flptr, mybuffer, size);
		delete ellipse_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Spot light");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

			float mm_spot_light[] = {   0.1f, 0, 0 ,0,
										0, 0.1f, 0, 0,
										0, 0, 0.1f, 0,
									    1,0.25f, 0, 1};

			matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
			matrix_handler->SetMatrix(mm_spot_light);
			WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
			matrix_handler->Reset();		
		
			HPoint light_sphere_center; 					
			float light_sphere_radius = 1.5f;
			light_sphere_center.Set(0.0f,0.0f,0.0f);
			sphere_handler = new TK_Sphere();
			sphere_handler->SetCenter ( light_sphere_center.x, light_sphere_center.y, light_sphere_center.z );
			sphere_handler->SetRadius(light_sphere_radius);
			sphere_handler->SetAxis (1,0,0);
			WriteObject(sphere_handler, mytoolkit, flptr, mybuffer, size);
			delete sphere_handler;

			float spot_light_pts[]={3,0,0};
			float target_path[]= {0,0,0};
			spot_light_handler = new TK_Spot_Light();
			spot_light_handler->SetPosition(spot_light_pts);
			spot_light_handler->SetTarget(target_path);
			spot_light_handler->SetOptions(01); 
			spot_light_handler->SetConcentration(2);
			spot_light_handler->SetInner(45.0);
			spot_light_handler->SetOuter(90.0);

			WriteObject(spot_light_handler, mytoolkit, flptr, mybuffer, size);
			delete spot_light_handler;	

			color_handler = new TK_Color;
			color_handler->SetGeometry( TKO_Geo_Light  );
			color_handler->SetChannels( 1 << TKO_Channel_Diffuse ); //xxx
			color_handler->	SetDiffuse (1.0,0.0,0.0  );
			WriteObject(color_handler, mytoolkit, flptr, mybuffer, size);
			delete color_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;
	
	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Circular Chord");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_circ_chord[] = { 0.1f, 0, 0 ,0,
								0, 0.1f, 0, 0,
								0, 0, 0.1f, 0,
							   -2, 2.66f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_circ_chord);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

		// export a TKE_Polyline object
		HPoint center;
		float radius = 1.0f;
		center.Set(0.0f,0.0f,0.0f);
		circle_handler = new TK_Circle(TKE_Circular_Chord);
        circle_handler->SetStart( center.x + radius, center.y, center.z );
        circle_handler->SetMiddle( center.x - radius, center.y, center.z );
        circle_handler->SetEnd( center.x, center.y + radius, center.z );
		WriteObject(circle_handler, mytoolkit, flptr, mybuffer, size);
		delete circle_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Sphere");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_sphere[] = { 0.1f, 0, 0 ,0,
								0, 0.1f, 0, 0,
								0, 0, 0.1f, 0,
							   -1, 1.66f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_sphere);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

		// export a TKE_Polyline object
		HPoint sphere_center; 					
		float sphere_radius = 1.5f;
		sphere_center.Set(0.0f,0.0f,0.0f);
		sphere_handler = new TK_Sphere();
        sphere_handler->SetCenter ( sphere_center.x, sphere_center.y, sphere_center.z );
        sphere_handler->SetRadius(sphere_radius);
        sphere_handler->SetAxis (1,0,0);
		WriteObject(sphere_handler, mytoolkit, flptr, mybuffer, size);
		delete sphere_handler;

		float clip_pts[]={0, 0, 0, 1, 0, 0, 0, 1, 0 };
		clip_region_handler = new TK_Clip_Region();
		clip_region_handler->SetPoints (3,clip_pts );
		WriteObject(clip_region_handler, mytoolkit, flptr, mybuffer, size);
		delete clip_region_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Local light");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

			float mm_local_light[] = {   0.1f, 0, 0 ,0,
										0, 0.1f, 0, 0,
										0, 0, 0.1f, 0,
									    1,0.25f, 0, 1};

			matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
			matrix_handler->SetMatrix(mm_local_light);
		//	WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
			matrix_handler->Reset();		
			
			float local_light_pts[]={2,0,0};
			point_handler = new  TK_Point(TKE_Local_Light);
			point_handler->SetPoint(local_light_pts);
			WriteObject(point_handler, mytoolkit, flptr, mybuffer, size);
			delete point_handler;	
	
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;
	

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Circular Wedge");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_circ_wedge[] = { 0.1f, 0, 0 ,0,
								0, 0.1f, 0, 0,
								0, 0, 0.1f, 0,
							    0, 0.25f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_circ_wedge);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

		// export a TKE_Polyline object
	//	HPoint center;
	//	float radius = 1.0f;
	//	center.Set(0.0f,0.0f,0.0f);
		circle_handler = new TK_Circle( TKE_Circular_Wedge );
        circle_handler->SetStart( center.x + radius, center.y, center.z );
        circle_handler->SetMiddle( center.x - radius, center.y, center.z );
        circle_handler->SetEnd( center.x, center.y + radius, center.z );
		WriteObject(circle_handler, mytoolkit, flptr, mybuffer, size);
		delete circle_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;


    open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Circular Arc");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_circ_arc[] = { 0.1f, 0, 0 ,0,
								0, 0.1f, 0, 0,
								0, 0, 0.1f, 0,
							   -1, 1.0f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_circ_arc);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

		// export a TKE_Polyline object
	//	HPoint center;
	//	float radius = 1.0f;
	//	center.Set(0.0f,0.0f,0.0f);
		circle_handler = new TK_Circle( TKE_Circular_Arc );
        circle_handler->SetStart( center.x + radius, center.y, center.z );
        circle_handler->SetMiddle( center.x - radius, center.y, center.z );
        circle_handler->SetEnd( center.x, center.y + radius, center.z );
		WriteObject(circle_handler, mytoolkit, flptr, mybuffer, size);
		delete circle_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	
    open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Circle");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_circle[] = {  0.1f, 0, 0 ,0,
							   0, 0.1f, 0, 0,
							   0, 0, 0.1f, 0,
							  -1, 0.66f, 0,1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_circle);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		

		// export a TKE_Polyline object
		HPoint cricle_center;
	//	float radius = 1.0f;
		cricle_center.Set(3.0f,3.0f,3.0f);
		circle_handler = new TK_Circle( TKE_Circle );
        circle_handler->SetStart( cricle_center.x + radius, cricle_center.y, cricle_center.z );
        circle_handler->SetMiddle( cricle_center.x - radius, cricle_center.y, cricle_center.z );
        circle_handler->SetEnd( cricle_center.x, cricle_center.y + radius, cricle_center.z );
		WriteObject(circle_handler, mytoolkit, flptr, mybuffer, size);
		delete circle_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Distant light");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

			float mm_distant_light[] = {   0.1f, 0, 0 ,0,
											0, 0.1f, 0, 0,
											0, 0, 0.1f, 0,
											2,2.25f, 0, 1};

			matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
			matrix_handler->SetMatrix(mm_distant_light);
		//	WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
			matrix_handler->Reset();		
			
			float distant_light_pts[]={-5,0,0};
			point_handler = new  TK_Point(TKE_Distant_Light);
			point_handler->SetPoint(distant_light_pts);
			WriteObject(point_handler, mytoolkit, flptr, mybuffer, size);
			delete point_handler;	
	
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;
	
    open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Polyline");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

			float mm_polyline[] = {0.1f, 0, 0 ,0,
								   0, 0.1f, 0, 0,
								   0, 0, 0.1f, 0,
								  -1, 0.36f, 0, 1};

			matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
			matrix_handler->SetMatrix(mm_polyline);
			WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
			matrix_handler->Reset();		

			// export a TKE_Polyline object
			float pts[]={-1 ,-1, 0, 1,-1, 0, 0.25, 0, 0, 1, 1, 0, -1, 1, 0, -0.25, 0, 0};
			line_handler= new TK_Polypoint(TKE_Polyline);
			line_handler->SetPoints(6, pts);
			WriteObject(line_handler, mytoolkit, flptr, mybuffer, size);
			delete line_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Line");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

			float mm_line[] = {0.1f, 0, 0, 0,
							   0, 0.1f, 0, 0,
							   0, 0, 0.1f, 0,
							  -0.5f, 0.66f, 0, 1};

			matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
			matrix_handler->SetMatrix(mm_line);
			WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
			matrix_handler->Reset();		

			// export a TKE_line object
			float line_pts[]={-1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
			l_line_handler = new TK_Line;
			l_line_handler->SetPoints(line_pts);
			WriteObject(l_line_handler, mytoolkit, flptr, mybuffer, size);
			delete l_line_handler;

			// Set the line pattern 
			int line_style_pattern = 3;
			named_handler= new TK_Named(TKE_Line_Pattern);
			named_handler->SetIndex(line_style_pattern); 
			WriteObject(named_handler, mytoolkit, flptr, mybuffer, size);
			delete named_handler;
					
			float line_weight = 3.5;
			size_handler= new TK_Size(TKE_Line_Weight);
			size_handler->SetSize(line_weight); 
			WriteObject(size_handler, mytoolkit, flptr, mybuffer, size);
			delete size_handler;
    
  
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

	open_seg_handler= new TK_Open_Segment;
	open_seg_handler->SetSegment("Marker");
	WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
	delete open_seg_handler;

		float mm_marker[] =  { 0.1f, 0, 0, 0,
							   0, 0.1f, 0, 0,
							   0, 0, 0.1f, 0,
							  -1, 1.2f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_marker);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();	

		// export a TKE_Marker object
		point_handler = new TK_Point(TKE_Marker);
		point_handler->SetPoint(0.0, 0.0, 0.0);
		WriteObject(point_handler, mytoolkit, flptr, mybuffer, size);
		delete point_handler;

		float marker_size = 1;
		size_handler= new TK_Size(TKE_Marker_Size);
		size_handler->SetSize(marker_size); 
		WriteObject(size_handler, mytoolkit, flptr, mybuffer, size);
		delete size_handler;

		vis_handler = new TK_Visibility();
		vis_handler->SetGeometry (TKO_Geo_Marker|TKO_Geo_Line);
		vis_handler->SetValue (TKO_Geo_Marker|TKO_Geo_Line);
		WriteObject(vis_handler, mytoolkit, flptr, mybuffer, size);
		delete vis_handler;

		rgb_color_handler = new TK_Color_RGB();
		rgb_color_handler->SetGeometry (TKO_Geo_Marker|TKO_Geo_Line);
		rgb_color_handler->SetRGB(1.0,0.0,0.0);
		WriteObject(rgb_color_handler, mytoolkit, flptr, mybuffer, size);
		delete rgb_color_handler;

		named_handler= new TK_Named(TKE_Marker_Symbol);
		named_handler->SetIndex(38); 
		WriteObject(named_handler, mytoolkit, flptr, mybuffer, size);
		delete named_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

    // export TKE_Open_Segment so that the image can be in a subsegment with separate visibility settings
    // There is currently, unfortunately, no way to avoid having the image included in bounding volume
    // calculations if we put it into a subsegment like this.  The alternative, though, is to put the image
    // into a top-level directory, such as "/images" or "?Include Library".  The drawback of that approach,
    // though, is that directories such as those are difficult to clean up when the window is closed.
    open_seg_handler = new TK_Open_Segment;
    open_seg_handler->SetSegment("images");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;
    
        // use TK_Visibility to turn the visibility of images off.  This image is solely a resource for
        // textures, not something that is supposed to appear in the scene
        vis_handler = new TK_Visibility;
        vis_handler->SetGeometry( TKO_Geo_Image );
        vis_handler->SetValue( ~TKO_Geo_All_Visibles );
        WriteObject(vis_handler, mytoolkit, flptr, mybuffer, size);
        delete vis_handler;

        // as shown in this example, the function that initializes the data need not necessarily 
        // be called "interpret" 
        image_handler = new TK_Image;
        create_checkerboard( image_handler, WIDTH, HEIGHT, "checkerboard" );
        WriteObject(image_handler, mytoolkit, flptr, mybuffer, size);
        delete image_handler;

    // close the segment
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

    // put the model in a different segment
    open_seg_handler = new TK_Open_Segment;
    open_seg_handler->SetSegment("model");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_model[] = {   0.1f, 0, 0, 0,
							   0, 0.1f, 0, 0,
							   0, 0, 0.1f, 0,
							   0, 0.66f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_model);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();	

        // turn off polygon handedness since in this example we are creating a flat object that 
        // we want to be visible from both sides.
        heuristic_handler = new TK_Heuristics;
        heuristic_handler->SetMask( TKO_Heuristic_Polygon_Handedness );
        heuristic_handler->SetValue( 0 );
        WriteObject(heuristic_handler, mytoolkit, flptr, mybuffer, size);
        delete heuristic_handler;


//         LOD 0 (the base resolution) of the shell id'd by key 13
        shell_handler = new TK_My_Shell;
        shell_handler->Interpret(*mytoolkit, 13, 0);
        WriteObject(shell_handler, mytoolkit, flptr, mybuffer, size);
        delete shell_handler;

        // define a texture.  In this example, we simply provide the association between a
        // named image and a named texture resource, but TK_Texture also has settings for things
        // like tiling settings, texture matrices and alternate parameterization sources.
        // The TK_Image is required to have been written at this point
        texture_handler = new TK_Texture;
        texture_handler->SetFlags( 0 ); //xxx
        texture_handler->SetImage( "checkerboard" );
        texture_handler->SetName( "my texture checkerboard" );
        WriteObject(texture_handler, mytoolkit, flptr, mybuffer, size);
        delete texture_handler;

        // export a setting to use the texture as the diffuse color.  The TK_Texture is required to have
        // already been written at this point.  Since the texture uses all default options, however,
        // it would have been legal to use the image as a color directly, a la SetDiffuseName("checkerboard")
        color_handler = new TK_Color;
        color_handler->SetGeometry( TKO_Geo_Face );
        color_handler->SetChannels( 1 << TKO_Channel_Diffuse ); //xxx
        color_handler->SetDiffuseName( "my texture checkerboard"  );
        WriteObject(color_handler, mytoolkit, flptr, mybuffer, size);
        delete color_handler;

    // close the segment
    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

		// Defining the colormap
		float colormap[]={1.0,1.0,1.0,0.5,0.5,0.5,1.0,0.0,0.0,0.0,0.0,1.0};
		color_map_handler = new TK_Color_Map;
		color_map_handler->SetValues(4, colormap);
		WriteObject(color_map_handler, mytoolkit, flptr, mybuffer, size);
		delete color_map_handler;

	// export the TKE_Open_Segment opcode for 'object_1' 
	open_seg_handler= new TK_Open_Segment;
	open_seg_handler->SetSegment("/include_library/object_1");
	WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);

		// We could delete this handler and recreate one the next time we need it, but since
		// we're going to reuse it, we instead call its Reset method and keep it around.
		// Our derived class would overload the Reset method and do cleanup/re-initialization
		// of any custom data.
		open_seg_handler->Reset();       

		// LOD 2 of the shell id'd by key 13
		// we're going to reuse this handler so Reset it and keep it around
		shell_handler = new TK_My_Lod_Shell;
		shell_handler->Interpret(*mytoolkit, 13, 2);
		WriteObject(shell_handler, mytoolkit, flptr, mybuffer, size);

		// Tags are actually automatically generated for shells. However, if you did want to tag 
		// something, call the Tag method of the BaseOpcodeHandler class.  For example:
		// handler->Tag(*mytoolkit, 2);

		// We could delete this handler and recreate one the next time we need it, but since
		// we're going to reuse it, we instead call its Reset method and keep it around.
		// Our derived class would overload the Reset method and do cleanup/re-initialization
		// of any custom data.
		//shell_handler->Reset();    
		delete shell_handler;

		// we're going to reuse this handler so Reset it and keep it around
	close_seg_handler = new TK_Close_Segment;
	WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
	close_seg_handler->Reset();

	// export the TKE_Open_Segment opcode for 'object_2' 
	open_seg_handler->SetSegment("/include_library/object_2");
	WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
	open_seg_handler->Reset();

//		 LOD 2 of the shell id'd by key 14
		shell_handler = new TK_My_Lod_Shell;
		shell_handler->Interpret(*mytoolkit, 14, 2);
		WriteObject(shell_handler, mytoolkit, flptr, mybuffer, size);
		shell_handler->Reset();

		WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
		close_seg_handler->Reset();

	// export the TKE_Open_Segment opcode for 'part_1' 
	open_seg_handler->SetSegment("part_1");
	WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
	open_seg_handler->Reset();

		// Review the Geometry_Bits enum in BOpcodeHandler.h if
		// you want to get more granularity on the color settings of different geometry in the segment
		rgb_color_handler = new TK_Color_RGB();
		rgb_color_handler->SetGeometry(1);
		rgb_color_handler->SetRGB(1.0, 0.0, 0.0);
		WriteObject(rgb_color_handler, mytoolkit, flptr, mybuffer, size);
		delete rgb_color_handler;

		// include the 'object_1' segment
		referenced_segment_handler = new TK_Referenced_Segment(TKE_Include_Segment);
		referenced_segment_handler->SetSegment("/include_library/object_1");
		WriteObject(referenced_segment_handler, mytoolkit, flptr, mybuffer, size);
		referenced_segment_handler->Reset();

		float mm1[] =        {  0.1f, 0, 0, 0,
								0, 0.1f, 0, 0,
								0, 0, 0.1f, 0,
								0.5f, 0.66f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm1);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();

		WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
		close_seg_handler->Reset();


	// export the TKE_Open_Segment opcode for 'part_2' 
	open_seg_handler->SetSegment("part_2");
	WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
	open_seg_handler->Reset();

		// include the 'object_2' segment
		referenced_segment_handler->SetSegment("/include_library/object_2");
		WriteObject(referenced_segment_handler, mytoolkit, flptr, mybuffer, size);
		referenced_segment_handler->Reset();

		float mm2[] = { 0.1f, 0, 0, 0,
						0, 0.1f, 0, 0,
						0, 0, 0.1f, 0,
						0, 0, 0, 1};

		matrix_handler->SetMatrix(mm2);
		WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();

	WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
	close_seg_handler->Reset();

		//*********** LODS ***********
		// Notice how we're passing in the full resolution of the shell at a later point, yet the toolkit 
		// automatically associates it back to the LOD from the shell_key passed in.

		// LOD 1 of the shell id'd by key 13
		shell_handler->Interpret(*mytoolkit, 13, 1);
		WriteObject(shell_handler, mytoolkit, flptr, mybuffer, size);
		shell_handler->Reset();

		// LOD 1 of the shell id'd by key 14
		shell_handler->Interpret(*mytoolkit, 14, 1);
		WriteObject(shell_handler, mytoolkit, flptr, mybuffer, size);
		shell_handler->Reset();

		// Full resolution (LOD 0) of the shell id'd by key 13
		shell_handler->Interpret(*mytoolkit, 13, 0);
		WriteObject(shell_handler, mytoolkit, flptr, mybuffer, size);
		shell_handler->Reset();

		// Full resolution (LOD 0) of the shell id'd by key 14
		shell_handler->Interpret(*mytoolkit, 14, 0);
		WriteObject(shell_handler, mytoolkit, flptr, mybuffer, size);
		shell_handler->Reset();

		delete shell_handler;

	open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment("Cutting Plane");
    WriteObject(open_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete open_seg_handler;

		float mm_cut_palne[] = {  0.1f, 0, 0 ,0,
									0, 0.1f, 0, 0,
									0, 0, 0.1f, 0,
									-1,2.25f, 0, 1};

		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(mm_cut_palne);
	//	WriteObject(matrix_handler, mytoolkit, flptr, mybuffer, size);
		matrix_handler->Reset();		
	
		// export a TKE_Polyline object
		float cut_plane[]={-1.0, -1.0, 0, 1.0};
		cutting_plane_handler= new TK_Cutting_Plane();
		cutting_plane_handler->SetPlane(cut_plane);
		WriteObject(cutting_plane_handler, mytoolkit, flptr, mybuffer, size);
		delete cutting_plane_handler;

    close_seg_handler = new TK_Close_Segment;
    WriteObject(close_seg_handler, mytoolkit, flptr, mybuffer, size);
    delete close_seg_handler;

  // export a TKE_Termination object
    terminator_handler = new TK_Terminator(TKE_Termination);
    WriteObject(terminator_handler, mytoolkit, flptr, mybuffer, size);
    delete terminator_handler;

    // ask the toolkit how much of the final buffer is filled
    count = mytoolkit->CurrentBufferLength();

    // write out the final buffer
    fwrite(mybuffer, sizeof (char), count, flptr);

    // close the file
    fclose(flptr);

    // cleanup the toolkit object
    delete mytoolkit;
	return 0;
	
}


