//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "BufferedImage.h"
class Logger;



char* textFileRead(string filename);
void* HARDWARE_load_file(string filename);
void HARDWARE_unload_file(void** data_pointer);
long HARDWARE_get_file_size(string filename);


class ConsoleText;

class BobFile
{
public:

	string path;

	BobFile();
	BobFile(const string& s);
	bool exists();
	static bool exists(const string& s);
	int length();
	string& getAbsolutePath();
	void createNewFile();
	string getName();
	void deleteFile();
};


class FileUtils
{
public:

	//static FileUtils* fileUtils;

	FileUtils();

	static string removeIllegalFilenameChars(string s);
	//static void fixPath(string &fullname);
	static BufferedImage* readBufferedImageFromFile(BobFile* file);
	//static ArrayList<string>* readLines(u8* get_resource_as_stream);
	static void makeDir(const string& cs);
	//static unsigned char* decodeBase64StringToByteArray(const string& cs);
	//static string& encodeByteArrayToBase64String(unsigned char const* bytes_to_encode, unsigned int in_len);

	//static u8* getResourceAsStream(const string& filename);//was InputStream
	//static string& getResource(const string& filename);//was URL

	static void ltrim(std::string s);
	static void rtrim(std::string s);
	static void trim(std::string s);
	static string ltrimmed(std::string s);
	static string rtrimmed(std::string s);
	static string trimmed(std::string s);
	//static short* oldLoadShortIntFile(const string& filename);
	static vector<int>* loadIntFile(string filename);
	static vector<int>* loadIntFileFromExePath(string filename);
	static vector<uint16_t>* loadShortFile(string filename);
	static string loadTextFileAndTrim(string filename);
	static string loadTextFileFromExePathAndTrim(string filename);
	static ArrayList<string>* loadTextFileIntoVectorOfStringsAndTrim(string filename);
	static ArrayList<string>* loadTextFileFromExePathIntoVectorOfStringsAndTrim(string filename);
	static vector<u8>* loadByteFile(string filename);
	static vector<u8>* loadByteFileFromExePath(string filename);
	//static vector<u8>* loadByteFileFromExePathIntoVector(string filename);

	static string lzoByteArrayToBase64String(const u8* byteArray, unsigned long sourceLength);
	static u8* unlzoBase64StringToByteArray(const string &zippedBytesAsString, unsigned long &returnLength);

	static string lz4ByteArrayToBase64String(const u8* byteArray, unsigned long sourceLength);
	static u8* unlz4Base64StringToByteArray(const string &zippedBytesAsString, unsigned long &returnLength);

	static string zipByteArrayToBase64String(const u8* byteArray, unsigned long sourceLength);
	static u8* unzipBase64StringToByteArray(const string &zippedBytesAsString, unsigned long &returnLength);

	static string lzoStringToBase64String(const string& s);
	static string unlzoBase64StringToString(const string& s);

	static string lz4StringToBase64String(const string& s);
	static string unlz4Base64StringToString(const string& s);

	static string zipStringToBase64String(const string& s);
	static string unzipBase64StringToString(const string& s);

	static string getFileMD5Checksum(const string& filename);
	static vector<u8>* getByteArrayFromIntArray(vector<int>*intArray);
	static string getByteArrayMD5Checksum(vector<u8>* bytes);
	static string getStringMD5(const string& stringToMD5);
	static void saveImage(const string& s, BufferedImage* bufferedImage);

	static std::string byteArrayToHexString(u8 *data, unsigned long len);
	static u8* hexStringToByteArray(const string &hex);
	static std::string encodeByteArrayToBase64String(u8 const* bytes_to_encode, unsigned long in_len);
	static vector<u8>* decodeBase64StringToByteArray(std::string const& encoded_string);//, unsigned long &returnLength);	
	static std::string encodeByteArrayToBase64StringAlt(u8 const* bytes_to_encode, unsigned long in_len);
	static vector<u8>* decodeBase64StringToByteArrayAlt(std::string const& encoded_string);//, unsigned long &returnLength);


	static string appDataPath;
	static string cacheDir;
	//static string slash;

	static string bigDataURL; //for zip files
	static string smallDataURL; //for individual patch files (basically the newest zip file unzipped into dir)

	static Logger log;

	static void writeSessionTokenToCache(long long userID, const string& sessionToken, bool statsAllowed);
	static string readSessionTokenFromCache();
	static void deleteSessionTokenFromCache();
	//void writeCookie(const string& s);
	//ArrayList<string>* readCookies();
	//static void writeBrowserSessionCookieAndRefreshIFrame();
	//static void deleteBrowserSessionCookieAndRefreshIFrame();
	//static void writeBrowserSessionAndRefreshIFrame();

	string downloadingDataNiceName = "";
	ConsoleText* statusConsoleText = nullptr;
	long long downloadingFileSize = 0;

	void setStatusText(const string& text);
	void deleteStatusText();

	void downloadFileToCacheWithProgressListener(const string& fileName, const string& niceName);
	void decompressZipInCache(const string& fileName, const string& niceName);
	void deleteFileFromCache(const string& fileName);
	static bool checkIfFileExistsInCache(const string& fileName);
	long long getFileSizeInCache(const string& fileName);
	long long getFileSizeOnServer(const string& fileName);
	void downloadAndDecompressZIPFileIfDifferentFromServer(const string& fileName, const string& niceName);
	void downloadFileIfDifferentFromServer(const string& fileName, const string& niceName);
	void initCache();
	static void downloadBigFileToCacheIfNotExist(const string& fileName);
	static void downloadSmallFileToCacheIfNotExist(const string& fileName);
	static vector<u8>* loadByteFileFromCacheOrDownloadIfNotExist(const string& fileName);
	static vector<int>* loadIntFileFromCacheOrDownloadIfNotExist(const string& fileName);
	static void saveByteArrayToCache(vector<u8>* byteArray, const string& md5FileName);

	static void writeByteArrayToFile(vector<u8>* byteArray, const string& fileName);
	static bool doesDidIntroFileExist();
	static void writeDidIntroFile();
};

