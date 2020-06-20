# KEngine
My own personal graphics engine. I got inspiration from my graphics class, and I plan on expanding on what I learned in that class to make a fast and fairly efficient graphics engine.

## General pipeline: 
### Credit goes towards https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Introduction for help

1. Vertex specification
	1. Basically creating the vertices
	2. This is also where the vertex normals, coords, materials etc. are created
2. Vertex shader
	1. This is where the vertex are transformed from a model space into screen space, i.e. where they will show up on the final screen. This is where transformations and perspective projections happen.
3. Tessellation
	1. This is something else, I'll tackle this later. Basically, this will split triangles into more triangles to create more complicated meshes. I don't think I will be using this right now.
4. Geometry shader
	1. Here the vertices and vertex normals will be combined into triangle polygons, and will be added to the geometry queue
7. Rasterization (Pixel shading)
	1. This finds out which pixels will actually be drawn. These places will be referred to as "fragments." They hold more info than just their x and y, for example they have texture coordinates and perhaps vertex normals for lighting.
		1. Fragments that aren't going to be drawn (i.e those behind other fragments) will be discarded
	2. Here I will use multithreading to draw multiple vertices at once
		1. I will decide on where to actually split later
		2. I wil also decide whether multiple threads should work on one triangle at once
8. Fragment shader
	1. This will fill in the fragments with the proper colors
9. Per-sample operations
	1. So like super-sampling and anti-aliasing
10. The framebuffer
	1. This isn't really a part of the pipeline, but now is when the framebuffer will actually be drawn

## General ideas:

There will be queues for each, or at least most, steps for the pipeline. That will make handling much easier.

## General structures:

- Vertex matrix (matrix)
	- This will be where vertices are added to initially, and where they are transformed.
- Vertex normal matrix (matrix)
	- This will be where vertex normals are added to initially, and where they are transformed.
- Vertex texture coord array (array)
	- This will be where vertex texture coords are accessed. They won't be transformed at all.
- System stack (stack)
	- This is where the cstack will be stored. This is the transformation matrix that will be applied to the vertex matrix, along with the vertex normal matrix
- Geometry queue (queue)
	- This will be where polygons/lines will be added. They will be then read in rasterization and put onto the fragment buffer
- Fragment buffer (2D buffer)
	- This will be where the fragments are stored. The structure should be SCREEN_WIDTH by SCREEN_HEIGHT large
- Pixel buffer (2D array)
	- This is where the final pixel structures will be stored. The structure should be SCREEN_WIDTH by SCREEN_HEIGHT large
	- This structure will also be altered when per-sampling operations occur
- Material list (hash table)
	- This will be where each material loaded will be placed. They will be hashed using their names, at least for now
- Light list (queue)
	- This will be where each light will be stored. Each light will be iterated through when doing lighting
- Texture list (hash table)
	- This is where each loaded texture will be stored. They will too be accessed by their name. 

## Planned Architecture of the program:

- Constants & other basic stuff (KEngine.h)
- Structures
	- Vertex (vertex.h, vertex.c)
		- Material (material.h, material.c)
			- Textures (texture.h, texture.c)
	- Geometry (geo.h)
		- Including polygons and lines
	- Matrix (matrix.h)
		- Matrix handling functions (matrix.c)
		- Matrix mathematical functions (matrix_op.c)
			- These functions will either work on other matrixes or on individual vertices
	- Fragment (fragment.h, fragment.c)
	- Queue (queue.h, queue.c)
- Functions
	- Basic math functions (gmath.h, gmath.c)
		- So like lerp, finding surface normal, normalizing, etc.
	- Lighting functions (light.h)
		- These lighting/shading functions will probably happen on a per-pixel basis during the fragment shader phase
		- Phong reflection calculations (phong_ref.c)
		- Blinn-phong reflection calculations (blinn_ref.c)
		- Phong shading (phong_sh.c)
		- Gouraud shading (gouraud_sh.c)
		- Flat shading (flat_sh.c)
		- Wireframe shading (wireframe_sh.c)
	- Parsing files (parse.h)
		- Parsing obj files (parse_obj.c)
			- Input an obj file, return a bunch of vertices
		- Reading png files (png_read.c)
			- This will mainly be used in tandem with parse_obj.c in order to read in textures
		- Maybe I'll allow for different files to be parsed later, but for now obj files are the easiest and most useful
	- Simple shapes (shape.h)
		- Sphere (sphere.c)
			- Create a bunch of vertices to add to the vertex shading pipeline
		- Box (box.c)
		- More if I feel like it
	- Rasterization function (rasterize.c)
		- Take in a polygon/line and the fragment array, and alter the fragment array based on the polygon/line
			- By alter, I mean change the array in the places where the polygon/line will actually be rendered. If the polygon/line is not going to be rendered because it's behind something, the fragment array won't change.
	- Shading (shade.h)
		- Vertex shading (vshade.c)
			- Take in a vertex, do some shading and transformations on it, and add that vertex to the geometry shader
		- Geometry shading (gshade.c)
			- Take in two or three vertices at a time (depending on whether you're drawing a line or not) and output line or polygon structures. If the polygons aren't going to be rendered because they're not facing the right way or they are off screen, discard them at this step.
			- I think I will also add a way to turn polygons that are partially off screen into multiple polygons that are on screen
		- Fragment shading (fshade.c)
			- Take in a list of fragments (a SCREEN_WIDTH by SCREEN_HEIGHT sized block of data I think) and return a buffer of pixels
	- Post-processing (process.h)
		- Multisample anti-aliasing (mxaa.c)
			- Take in a screen buffer, and output another one of a smaller size (i.e. make it more clear)
		- Maybe I'll add more if I feel like it
	- Final drawing (draw.h)
		- Writing to a png file (png_write.c)
			- Take in a buffer of pixels, and write to a png file