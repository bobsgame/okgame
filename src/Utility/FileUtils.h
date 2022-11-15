//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
#include "BufferedImage.h"
class Logger;



char* textFileRead(string filename);
void* HARDWARE_load_file(string filename);
void HARDWARE_unload_file(void** data_pointer);
long HARDWARE_get_file_size(string filename);


class ConsoleText;

class OKFile
{
public:

	string path;

	OKFile();
	OKFile(const string& s);
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

	//static sp<FileUtils> fileUtils;

	FileUtils();

	static sp<vector<string>> swearWords;
	static string removeSwearWords(string s);
	static string removeIllegalFilenameChars(string s);
	//static void fixPath(string &fullname);
	static sp<BufferedImage> readBufferedImageFromFile(sp<OKFile> file);
	//static sp<vector<string>>* readLines(u8* get_resource_as_stream);
	static void makeDir(const string& cs);
	//static unsigned char* decodeBase64StringToByteArray(const string& cs);
	//static string& encodeByteArrayToBase64String(unsigned char const* bytes_to_encode, unsigned int in_len);

	//static u8* getResourceAsStream(const string& filename);//was InputStream
	//static string& getResource(const string& filename);//was URL

	static void ltrim(std::string &s);
	static void rtrim(std::string &s);
	static void trim(std::string s);
	static string ltrimmed(std::string s);
	static string rtrimmed(std::string s);
	static string trimmed(std::string s);
	//static short* oldLoadShortIntFile(const string& filename);
	static sp<IntArray> loadIntFile(string filename);
	static sp<IntArray> loadIntFileFromExePath(string filename);
	//static sp<vector<uint16_t>>* loadShortFile(string filename);
	static string loadTextFileAndTrim(string filename);
	static string loadTextFileFromExePathAndTrim(string filename);
	static sp<vector<string>> loadTextFileIntoVectorOfStringsAndTrim(string filename);
	static sp<vector<string>> loadTextFileFromExePathIntoVectorOfStringsAndTrim(string filename);
	static sp<ByteArray> loadByteFile(string filename);
	static sp<ByteArray> loadByteFileFromExePath(string filename);
	//static sp<ByteArray> loadByteFileFromExePathIntosp<Vector(string filename);

	//static string lzoByteArrayToBase64String(const u8* byteArray, unsigned long sourceLength);
	//static u8* unlzoBase64StringToByteArray(const string &zippedBytesAsString, unsigned long &returnLength);

	static string lz4ByteArrayToBase64String(const u8* byteArray, unsigned long sourceLength);
	static u8* unlz4Base64StringToByteArray(const string &zippedBytesAsString, unsigned long &returnLength);

	static string zipByteArrayToBase64String(const u8* byteArray, unsigned long sourceLength);
	static u8* unzipBase64StringToByteArray(const string &zippedBytesAsString, unsigned long &returnLength);

	//static string lzoStringToBase64String(const string& s);
	//static string unlzoBase64StringToString(const string& s);

	static string lz4StringToBase64String(const string& s);
	static string unlz4Base64StringToString(const string& s);

	static string zipStringToBase64String(const string& s);
	static string unzipBase64StringToString(const string& s);

	static string getFileMD5Checksum(const string& filename);
	static sp<ByteArray> getByteArrayFromIntArray(sp<IntArray> intArray);
	static string getByteArrayMD5Checksum(sp<ByteArray> bytes);
	static string getStringMD5(const string& stringToMD5);
	static void saveImage(const string& s, sp<BufferedImage> bufferedImage);

	static std::string byteArrayToHexString(u8 *data, unsigned long len);
	static u8* hexStringToByteArray(const string &hex);
	static std::string encodeByteArrayToBase64String(u8 const* bytes_to_encode, unsigned long in_len);
	static sp<ByteArray> decodeBase64StringToByteArray(std::string const& encoded_string);//, unsigned long &returnLength);	
	static std::string encodeByteArrayToBase64StringAlt(u8 const* bytes_to_encode, unsigned long in_len);
	static sp<ByteArray> decodeBase64StringToByteArrayAlt(std::string const& encoded_string);//, unsigned long &returnLength);


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
	//sp<vector<string>>* readCookies();
	//static void writeBrowserSessionCookieAndRefreshIFrame();
	//static void deleteBrowserSessionCookieAndRefreshIFrame();
	//static void writeBrowserSessionAndRefreshIFrame();

	string downloadingDataNiceName = "";
	sp<ConsoleText> statusConsoleText = nullptr;
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
	static sp<ByteArray> loadByteFileFromCacheOrDownloadIfNotExist(const string& fileName);
	static sp<IntArray> loadIntFileFromCacheOrDownloadIfNotExist(const string& fileName);
	static void saveByteArrayToCache(sp<ByteArray> byteArray, const string& md5FileName);
	static void writeByteArrayToFile(sp<ByteArray> byteArray, const string& fileName);
	static bool doesDidIntroFileExist();
	static void writeDidIntroFile();


};

