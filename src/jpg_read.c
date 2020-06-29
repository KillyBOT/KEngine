#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>

#include "KEngine.h"
#include "parse.h"

extern int SCREEN_HEIGHT_FINAL;
extern int SCREEN_WIDTH_FINAL;

extern pixel_t ** inputBuffer;
extern int input_width;
extern int input_height;

GLOBAL(void) read_jpg_file(char *filename){

	if(inputBuffer != NULL){
		for(int x = 0; x < input_width; x++)
			free(inputBuffer[x]);
		free(inputBuffer);
	}

	char finalFilename[512];

	strcpy(finalFilename,"../wavefront/");
	strcat(finalFilename,filename);

	//printf("%s\n", finalFilename);

	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	byte_t * rowptr[1];
	byte_t * pData;

	FILE* f;
	int row_stride;

	if( (f = fopen(finalFilename,"rb")) == NULL )
		abort_("JPEG file %s could not be opened!",filename);

	cinfo.err = jpeg_std_error(&jerr);

	jpeg_create_decompress(&cinfo);

	jpeg_stdio_src(&cinfo,f);

	(void) jpeg_read_header(&cinfo, TRUE);

	(void) jpeg_start_decompress(&cinfo);

	input_width = cinfo.output_width;
	input_height = cinfo.output_height;
	//printf("%d %d\n", input_width, input_height);

	inputBuffer = (pixel_t**)malloc(sizeof(pixel_t*) * input_width);
	for(int x = 0; x < input_width; x++)
		inputBuffer[x] = (pixel_t*)malloc(sizeof(pixel_t) * input_height);

	pData = (byte_t*)malloc(input_width * input_height * 3);

	while(cinfo.output_scanline < cinfo.output_height){

		rowptr[0] = (byte_t*)pData + (3 * input_width * cinfo.output_scanline);

		(void) jpeg_read_scanlines(&cinfo, rowptr, 1);
	}

	for(int w = 0; w < input_width; w++){
		for(int h = 0; h < input_height; h++){
			for(int c = 0; c < 3; c++){
				inputBuffer[w][h].c[c] = pData[ (h * input_width) + w*3 + c];
			}
			inputBuffer[w][h].c[3] = 255;
		}
	}

	free(pData);

	(void) jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);

	fclose(f);
}