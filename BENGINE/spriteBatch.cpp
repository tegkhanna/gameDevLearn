#include "spriteBatch.h"
#include<algorithm>

namespace bengine
{
	spriteBatch::spriteBatch():
	_vbo(0),
	_vao(0)
	{
	}


	spriteBatch::~spriteBatch()
	{
	}

	void spriteBatch::init()
	{
		createVertexArray();

	}

	void spriteBatch::begin(GlyphSortType sortType /*default: : GlyphSortType::TEXTURE*/)
	{
		_sortType = sortType;
		_renderBatches.clear();//assures we free at every start for preventing nonsense filling
		_glyphs.clear();
	}

	
	void spriteBatch::end()
	{
		_glyphPointers.resize(_glyphs.size());
		for (int i = 0; i < _glyphs.size(); i++)
			_glyphPointers[i] = &_glyphs[i];
		sortGlyphs();
		createRenderBatches();
	}

	void spriteBatch::sortGlyphs()
	{
		switch (_sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBtF);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFtB);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
			break;
		}
		//super easy way to sortttttt .. std::stable_sort(present in algorithm)
		//1)takes head of the array or whatever,, 2) takes last element  3)takes comparitive function to decide the sorting
	}

	void spriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const ColorRGBA8 &color)
	{
		_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
	
	}
	void spriteBatch::renderBatch()
	{
		glBindVertexArray(_vao);
		for (int i = 0; i < _renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i]._texture);//assigns texture of each batch
			glDrawArrays(GL_TRIANGLES, _renderBatches[i]._offset, _renderBatches[i]._numVertices);//draw each batch
		}
		glBindVertexArray(0);
	}

	void spriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(6 * _glyphs.size());//makes faster as we already know the size also we use resize instead of reserve so that we can treat it as an array to use subscript..prevents push back
		if (_glyphs.empty())
			return;

		int cv = 0;
		int offset = 0;
		//we do the first batch ourselves 
		_renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
		vertices[cv++] = _glyphPointers[0]->TL;//anti clock rotation from the top left
		vertices[cv++] = _glyphPointers[0]->BL;
		vertices[cv++] = _glyphPointers[0]->BR;
		vertices[cv++] = _glyphPointers[0]->BR;//next triangle(first vertice same)
		vertices[cv++] = _glyphPointers[0]->TR;
		vertices[cv++] = _glyphPointers[0]->TL;//(last vertice same)
		offset += 6;
		for (int cg = 1; cg < _glyphPointers.size(); cg++)
		{
			//we check here if the current glyph texture is similar to the previous one..if not, we then create a new batch. and if yes then we just add the number of vertices of the previous entry
			if (_glyphPointers[cg]->texture != _glyphPointers[cg - 1]->texture)
				_renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
			else
				_renderBatches.back()._numVertices += 6;

			vertices[cv++] = _glyphPointers[cg]->TL;//anti clock rotation from the top left
			vertices[cv++] = _glyphPointers[cg]->BL;
			vertices[cv++] = _glyphPointers[cg]->BR;
			vertices[cv++] = _glyphPointers[cg]->BR;//next triangle(first vertice same)
			vertices[cv++] = _glyphPointers[cg]->TR;
			vertices[cv++] = _glyphPointers[cg]->TL;//(last vertice same)
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);//bind the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);//upload to graphics card
																								//instead of simple we use a trick to save timee
																								//the avove line orphans the budder
																								//then this line binds again
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		//unbinding
		glBindBuffer(GL_ARRAY_BUFFER, 0);


	}

	void spriteBatch::createVertexArray()
	{	
		if(_vao==0)
			glGenVertexArrays(1, &_vao);
		
		glBindVertexArray(_vao);//bind vertex array to object
		
		if(_vbo==0)
			glGenBuffers(1, &_vbo);

		glBindBuffer(GL_ARRAY_BUFFER, _vao);//bind vertex buffer to object

		//tell opengl that we wanna use the first attribute array
		//we only need one array right now since we only usee posn
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//posn attrib pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//the last 0 tells the position is at the first byte(0)/
		 //instead we use offsetof for the first byte of structure

		//color attrib//1 for second attrib
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));//offset returns 8

		//UV attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);

	}

	bool spriteBatch::compareFtB(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}
	bool spriteBatch::compareBtF(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}
	bool spriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return(a->texture < b->texture);//it dows what is that it draws those batches whic are of same type in one go
	}

	

}