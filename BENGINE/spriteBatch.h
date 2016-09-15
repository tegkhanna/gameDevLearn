#pragma once
#include <vector>
#include <GL\glew.h>
#include "Vertex.h"
#include<glm\glm.hpp>


namespace bengine
{
	
	enum class GlyphSortType//type to sort
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};
	


	class Glyph//texture objects
	{

		
	public:
		Glyph() {}
		Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const ColorRGBA8 &color):
			texture(texture),
			depth(depth)
		{
			

			//top left
			TL.color = color;
			TL.setPos(destRect.x, destRect.y + destRect.w);//x->x,y->y,z->width, w->height
			TL.setUV(uvRect.x, uvRect.y + uvRect.w);//again x=0,y=1,z=3,w=4

															  //bottom left
			BL.color = color;
			BL.setPos(destRect.x, destRect.y);//x->x,y->y,z->width, w->height
			BL.setUV(uvRect.x, uvRect.y);//again x=0,y=1,z=3,w=4

												   //top right
			TR.color = color;
			TR.setPos(destRect.x + destRect.z, destRect.y + destRect.w);//x->x,y->y,z->width, w->height
			TR.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);//again x=0,y=1,z=3,w=4

																		 //bottom right
			BR.color = color;
			BR.setPos(destRect.x + destRect.z, destRect.y);//x->x,y->y,z->width, w->height
			BR.setUV(uvRect.x + uvRect.z, uvRect.y);//again x=0,y=1,z=3,w=4
		}
		GLuint texture;
		float depth;

		Vertex TL;
		Vertex TR;
		Vertex BL;
		Vertex BR;

	};

	class RenderBatch // for the final rendering of the batches.. requires info abt what to reneder
	{
	public:
		RenderBatch(GLuint offset, GLuint numVertices, GLuint texture) :
		_offset(offset),
		_numVertices(numVertices),//init list
		_texture(texture)
		{

		}
		GLuint _offset;
		GLuint _numVertices;
		GLuint _texture;
	};

	class spriteBatch
	{
	public:
		spriteBatch();
		~spriteBatch();

		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const ColorRGBA8 &color);
		void renderBatch();

	private:
		void createRenderBatches();
		void sortGlyphs();

		void createVertexArray();


		static bool compareFtB(Glyph* a, Glyph* b);
		static bool compareBtF(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;
		GlyphSortType _sortType;
		std::vector<Glyph> _glyphs;
		std::vector<Glyph*> _glyphPointers;
		std::vector<RenderBatch> _renderBatches;

	};


	


}
