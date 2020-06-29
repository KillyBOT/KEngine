#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>

#include "KEngine.h"
#include "parse.h"

extern int SCREEN_HEIGHT_FINAL;
extern int SCREEN_WIDTH_FINAL;

extern JSAMPLE * jpg_buffer;

GLOBAL(void) write_jpg_file(char* filename){

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	char finalFilename[512];
	strcpy(finalFilename,"../");
	strcat(finalFilename,filename);

	printf("%s\n", finalFilename);

	FILE *f;
	JSAMPROW row_pointer[1];
	int row_stride;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	if( (f = fopen(filename,"wb")) == NULL )
		abort_("Could not open jpeg file %s",filename);

	jpeg_stdio_dest(&cinfo, f);

	cinfo.image_width = SCREEN_WIDTH_FINAL;
	cinfo.image_height = SCREEN_HEIGHT_FINAL;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 8, TRUE);
	jpeg_start_compress(&cinfo, TRUE);

	row_stride = SCREEN_WIDTH_FINAL * 3;

	while(cinfo.next_scanline < cinfo.image_height){
		row_pointer[0] = &jpg_buffer[cinfo.next_scanline * row_stride];
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);

	fclose(f);

	jpeg_destroy_compress(&cinfo);


}