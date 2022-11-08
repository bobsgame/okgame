#pragma once
#include "oktypes.h"
class Logger;



	class OKTexture
	{



	public:
		static shared_ptr<OKTexture>lastBoundTexture;

		static shared_ptr<OKTexture>getLastBoundTexture();


	private:
		int glTargetType = 0;
		GLuint textureID = 0;

		int imageHeight = 0;
		int imageWidth = 0;

		int texWidth = 0;
		int texHeight = 0;

		//The ratio of the width of the image to the texture
		float widthRatio = 0;

		// The ratio of the height of the image to the texture
		float heightRatio = 0;

		bool alpha = false;

	
		// The name the texture has in the cache
		string cacheName = "";



	public:

		OKTexture(const string &ref, GLuint textureID);


		bool hasAlpha();


		void setAlpha(bool alpha);


		//Clear the binding of the texture
		static void bindNone();


		//Clear caching of the last bound texture so that an external texture binder can play with the context before returning control to slick.
		static void unbind();

		void bind();

		//Set the height of the image
		void setImageHeight(int height);


		//Set the width of the image
		void setImageWidth(int width);

		int getImageHeight();

		int getImageWidth();

		float getHeightRatio();


		float getWidthRatio();

		int getTextureHeight();

		int getTextureWidth();

		void setTextureHeight(int texHeight);

		void setTextureWidth(int texWidth);

		

	private:
		//Set the height of the texture. This will update the ratio also.
		void setHeightRatio();


		//Set the width of the texture. This will update the ratio also.
		void setWidthRatio();

	public:
		void release();

		GLuint getTextureID();

		void setTextureID(GLuint textureID);


	public:
		shared_ptr<ByteArray> getTextureData();
	};
