//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;

#include "../../Utility/gl/GLUtils.h"
#include "../EnginePart.h"
#include "../rpg/event/EventData.h"
#include "CTPL-master/ctpl_stl.h"

class SpriteAnimationSequence;
class SpriteData;
class OKTexture;
//class TextureRegion;



class Sprite : public EnginePart, public std::enable_shared_from_this<Sprite>
{
public:
	static Logger log;

	sp<Event> event = nullptr;

	//static sp<ExecutorService>generatePNGExecutorService;
	static ctpl::thread_pool* generatePNGThreadPool;


	sp<IntArray> indexDataIntArray = nullptr;
	sp<ByteArray> paletteRGBByteArray = nullptr;

	sp<OKTexture> texture = nullptr;
	sp<OKTexture> shadowTexture = nullptr;

	//ArrayList<sp<TextureRegion>>* frameTextureRegionList = ms<ArrayList><sp<TextureRegion>>();

	bool useHQ2X = false;

protected:
	sp<SpriteData> data = nullptr;

	bool _isInitialized = false;

private:
	long long lastCheckedSpriteTextureTime = 0;
	bool spriteTextureInitialized = false;

public:
	long long lastSentDataRequestTime = 0;

	bool threadCreated = false;
	bool checkedIfExist = false;
	bool hasDataMD5 = false; //non-threaded boolean check to avoid locking on synchronized function

	

	bool preloadedFromData = false;

	Sprite();
	Sprite(sp<Engine> g);
	void preloadFromDataFile(string name);
	//The following method was originally marked 'synchronized':
	void initializeWithSpriteData(sp<SpriteData> spriteData);
	void sendDataRequest(const string& getSpriteName);
	void sendDataRequest(int id);

	//The following method was originally marked 'synchronized':
	bool getInitialized_S();
protected:
	//The following method was originally marked 'synchronized':
	void setInitialized_S(bool i);
public:
	void drawFrame(const string& animationName, float x0, float x1, float y0, float y1, float r = 1, float g = 1, float b = 1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	void drawFrameXYWH(const string& animationName, float x, float y, float w, float h, float r = 1, float g = 1, float b = 1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	void drawFrame(int frame, float x0, float x1, float y0, float y1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	void drawFrame(sp<OKTexture> texture, int frame, float x0, float x1, float y0, float y1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	void drawFrame(int frame, float x0, float x1, float y0, float y1, float r = 1, float g = 1, float b = 1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	void drawFrame(sp<OKTexture> texture, int frame, float x0, float x1, float y0, float y1, float r = 1, float g = 1, float b = 1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	void draw(float tx0, float tx1, float ty0, float ty1, float x0, float x1, float y0, float y1, float r = 1, float g = 1, float b = 1, float a = 1, int filter = GLUtils::FILTER_NEAREST);



public:
	void update();
	//	long lastTimeRequestedDataMD5s=0;
	//
	//	
	//	public void requestDataMD5sFromServer()
	//	{
	//
	//long long startTime = lastTimeRequestedDataMD5s;
	//long long currentTime = System::currentHighResTimer();
	//int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	//		if(ticksPassed>3000)
	//		{
	//			lastTimeRequestedDataMD5s = time;
	//
	//			//send a request to the server
	//			Main.clientTCP.sendSpriteDataRequestByName(getName());
	//			//when server sends back response, in BGClient, look up sprite asset by identifier, set textureMD5Names and build texture!!
	//		}
	//	}

	void loadTextures();
	sp<ByteArray> getReplacementRGBFromSet(u8 r, u8 g, u8 b, sp<Sprite> s, int set);
	//The following method was originally marked 'synchronized':
	sp<ByteArray> createRandomSpriteTextureByteBuffer_S(int eyeSet, int skinSet, int hairSet, int shirtSet, int pantsSet, int shoeSet, int carSet);
	//The following method was originally marked 'synchronized':
	void createSpriteTexturePNG_S();
	//The following method was originally marked 'synchronized':
	void createSpriteShadowTexturePNG_S();
	//The following method was originally marked 'synchronized':
	void releaseSpriteTexture_S();

	


	//	public static int spriteTexturesLoaded = 0;
	//	public static int spriteThreadsCreated = 0;
	//	public static int maxSpriteThreadsCreated = 0;




	//------------------------------------
	bool _texturePNGExists = false;
	mutex _texturePNGExists_Mutex;
	bool getSpritePNGFileExists_S()
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_texturePNGExists_Mutex);
		return _texturePNGExists;
	}


	void setSpritePNGFileExists_S(bool done)
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_texturePNGExists_Mutex);
		_texturePNGExists = done;
	}



	//	
	//	public void incrementSpriteTexturesLoaded()
	//	{
	//		spriteTexturesLoaded++;
	//	}
	//	
	//	public void decrementSpriteTexturesLoaded()
	//	{
	//		spriteTexturesLoaded--;
	//	}

	//	
	//	public synchronized void incrementSpritePNGThreadsCreated_S()
	//	{
	//		spriteThreadsCreated++;
	//		if(spriteThreadsCreated>maxSpriteThreadsCreated)maxSpriteThreadsCreated=spriteThreadsCreated;
	//	}
	//
	//	
	//	public synchronized void decrementSpritePNGThreadsCreated_S()
	//	{
	//		spriteThreadsCreated--;
	//	}

	int getNumberOfAnimations();
	sp<SpriteAnimationSequence> getFirstAnimation();
	sp<SpriteAnimationSequence> getAnimationByName(const string& name);
	sp<SpriteAnimationSequence> getAnimationByFrame(int frame);
	sp<SpriteAnimationSequence> getAnimationByIndex(int index);
	int getAnimationNumFramesByIndex(int index);
	int getAnimationNumFramesByName(const string& name);
	int getAnimationNumFramesByFrame(int frame);
	int getAnimationNumFramesByAnimation(sp<SpriteAnimationSequence> a);
	int getAnimationIndexByName(const string& name);
	int getAnimationIndexByAnimation(sp<SpriteAnimationSequence> a);
	int getAnimationIndexByFrame(int frame);
	string getAnimationNameByIndex(int index);
	string getAnimationNameByFrame(int frame);
	void antialiasBufferedImage(sp<BufferedImage> bufferedImage);
	void setHQ2XAlphaFromOriginal(sp<BufferedImage> hq2xBufferedImage, sp<BufferedImage> bufferedImage);


	

	sp<SpriteData> getData();

	int getID();
	string& getName();
	string getTYPEIDString();
	string& getDataMD5();
	string& getPaletteMD5();

	string& getComment();

	int getImageWidth();
	int getImageHeight();	
//	int getScreenWidth();
//	int getScreenHeight();
	int getNumFrames();
	string& getDisplayName();
	bool getIsNPC();
	bool getIsKid();
	bool getIsAdult();
	bool getIsMale();
	bool getIsFemale();
	bool getIsCar();
	bool getIsAnimal();
	bool getHasShadow();
	bool getIsRandom();
	bool getIsDoor();
	bool getIsGame();
	bool getIsItem();
	bool getForceHQ2X();
	bool getForceMD5Export();
	sp<EventData> getEventData();
	string& getItemGameDescription();
	float getGamePrice();
	int getUtilityOffsetXPixelsHQ();
	int getUtilityOffsetYPixelsHQ();
	sp<vector<sp<SpriteAnimationSequence>>> getAnimationList();


	//	public void setName(String s){getData().setName(s);}
	//	public void setComment(String s){getData().setComment(s);}
	//	public void setID(int s){getData().setID(s);}
	//	public void setWidthPixels(int s){getData().setWidthPixels1X(s);}
	//	public void setHeightPixels(int s){getData().setHeightPixels1X(s);}
	//	public void setFrames(int s){getData().setFrames(s);}
	//	public void setDisplayName(String s){getData().setDisplayName(s);}
	//	public void setIsNPC(boolean s){getData().setIsNPC(s);}
	//	public void setIsKid(boolean s){getData().setIsKid(s);}
	//	public void setIsAdult(boolean s){getData().setIsAdult(s);}
	//	public void setIsMale(boolean s){getData().setIsMale(s);}
	//	public void setIsFemale(boolean s){getData().setIsFemale(s);}
	//	public void setIsCar(boolean s){getData().setIsCar(s);}
	//	public void setIsAnimal(boolean s){getData().setIsAnimal(s);}
	//	public void setHasShadow(boolean s){getData().setHasShadow(s);}
	//	public void setIsRandom(boolean s){getData().setIsRandom(s);}
	//	public void setIsDoor(boolean s){getData().setIsDoor(s);}
	//	public void setIsGame(boolean s){getData().setIsGame(s);}
	//	public void setIsItem(boolean s){getData().setIsItem(s);}
	//	public void setForceHQ2X(boolean s){getData().setForceHQ2X(s);}
	//	public void setForceMD5Export(boolean s){getData().setForceMD5Export(s);}
	//	public void setEventID(int s){getData().setEventID(s);}
	//	public void setItemGameDescription(String s){getData().setItemGameDescription(s);}
	//	public void setGamePrice(float s){getData().setGamePrice(s);}
	//	public void setUtilityOffsetXPixels1X(int s){getData().setUtilityOffsetXPixels1X(s);}
	//	public void setUtilityOffsetYPixels1X(int s){getData().setUtilityOffsetYPixels1X(s);}

};

