#include <stdio.h>
#include <stdlib.h>

#include "PointCloud.h"
#include "OOCT.h"
#include "utf_utils.h"

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#ifdef _MSC_VER
#pragma warning(disable: 4996) // don't complain about stdio string functions
#endif

#include "getopts.c"

void load_point_cloud_list ( char const * point_cloud_list_file_name, PointCloud * pc ) {
	char buf[4096];
	FILE *fp = fopen(point_cloud_list_file_name, "r");
	
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		for ( int i = (int)(strlen(buf) - 1) ; buf[i] == '\n' || buf[i] == '\r' || buf[i] == '\t' || buf[i] == ' ' ; i-- )
			buf[i] = '\0';

		while (buf[0] == '\t' || buf[0] == ' ')
			memmove(buf, buf + 1, strlen(buf));

		char *tmp = (char *)malloc(strlen(buf) + 1);
		strcpy(tmp, buf);

		pc->AddPointCloudFile(tmp);
		
		memset(buf, 0, sizeof(buf));
		free(tmp);
	}

	fclose(fp);
}

void free_file_names ( wchar_t * filename, void * user_data ) {
	delete [] filename;
}

int main ( int argc, char ** argv ) {
	struct options opts[] = {
		{ 1, "filename", "Point cloud filename", "f", 1 },
		{ 2, "filename_list", "File containing list of point cloud filenames (one per line)", "F", 1 },
		{ 3, "max_memory_usage", "Maximum memory usage (in MB)", "m", 1 },
		{ 4, "max_shell_size", "Maximum number of points per shell", "s", 1 },
		{ 5, "subsample", "Percentage (X) of points to import (0.0 < X <= 1.0)", "p", 1 },
		{ 6, "bounding_box", "Exclude all points outside given bounding box (no spaces): (min_x,min_y,min_z,max_x,max_y,max_z)", "b", 6 },
		{ 7, "output_file", "Name of output file", "o", 1 },
		{ 8, "overwrite", "Overwrite any existing output files", "r", 0 },
		{ 9, "log_file", "Write data about processing to specified file", "l", 1 },
		{ 10, "ooct filename", "Out of core triangulated hsf filename", "t", 1 },
		{ 0, 0, 0, 0, 0 }
	};
	
	wchar_t *output_file_name = 0;
	wchar_t *log_file_name = 0;

	PointCloud pc;
	OOCT *ooct;
	
	int c;
	char *args;
	while ((c = getopts(argc, argv, opts, &args)) != 0) {
		switch (c) {
			case -2: {
				printf("\n--- Unknown Option: %s ---\n\n", args);
				return EXIT_FAILURE;
			} break;
			
			case -1: {
				printf("\n--- Unable to allocate memory from getopts(). ---\n\n");
				return EXIT_FAILURE;
			} break;
			case 10: {
				ooct = new OOCT(args);
				ooct->PreProcess();
			} break;

			case 1: {
				pc.AddPointCloudFile(args);
			} break;

			case 2: {
				load_point_cloud_list(args, &pc);
			} break;

			case 3: {
				pc.SetMaxMemoryUsage(atoi(args));
			} break;
			
			case 4: {
				pc.SetMaxShellSize(atoi(args));
			} break;

			case 5: {
				pc.SetSubSamplePercentage(atof(args));
			} break;

			case 6: {
				float culling_bbox[6];
				int result = sscanf(args, "(%f,%f,%f,%f,%f,%f)", &culling_bbox[0], &culling_bbox[1], &culling_bbox[2], &culling_bbox[3], &culling_bbox[4], &culling_bbox[5]);
				if (result != 6) {
					printf("\n--- Bounding box requires six floats (no spaces): (min_x,min_y,min_z,max_x,max_y,max_z) ---\n\n");
					return EXIT_FAILURE;
				}
				pc.SetCullingBoundingBox(culling_bbox);
			} break;

			case 7: {
				if (output_file_name)
					delete [] output_file_name;

				H_WCS wcs_string = H_WCS(H_UTF8(args));
				output_file_name = new wchar_t [wcs_string.length() + 1];
				wcscpy(output_file_name, wcs_string.encodedText());
			} break;

			case 8: {
				pc.SetOverwriteExistingFiles(true);
			} break;

			case 9: {
				if (log_file_name)
					delete [] log_file_name;

				H_WCS wcs_string = H_WCS(H_UTF8(args));
				log_file_name = new wchar_t [wcs_string.length() + 1];
				wcscpy(log_file_name, wcs_string.encodedText());
			} break;
			
			default: {
				
			} break;
		}
		
		if (args)
			free(args);
	}

	int retval = EXIT_SUCCESS;

	pc.SetOOCFile(output_file_name);
	if (log_file_name)
		pc.SetLoggingFile(log_file_name);
	
	PointCloudStatus status = pc.PreProcess();
	if (status != PRE_PROCESS_SUCCESS) {
		retval = EXIT_FAILURE;

		if (status == PRE_PROCESS_SETUP_FAILURE)
			getopts_usage(argv[0], opts);
		else
			printf("OOC file generation failed.\n");
	}

	delete [] output_file_name;
	delete [] log_file_name;
	
	return retval;
}
