#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------




Logger FileUtils::log = Logger("FileUtils");

//void FileUtils::fixPath( string &fullname )
//{
//	for ( int i = 0; i < (int)fullname.length(); i++ )
//	{
//		if ( fullname[ i ] == '\\' )
//		{
//			fullname[ i ] = '/';
//		}
//	}
//}








#include <iostream>

#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Delegate.h"
#include "Poco/Zip/Decompress.h"
#include "Poco/Process.h"
#include "Poco/DirectoryIterator.h"
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Process;
using Poco::Path;
using Poco::Delegate;
using Poco::Zip::Decompress;

void test()
{

	//some directory stuff
	Path tmpPath(Path::temp());
	tmpPath.pushDirectory("PocoFileSample");
	File tmpDir(tmpPath);
	tmpDir.createDirectories();
	//bool exists = tmpDir.exists();
	//bool isFile = tmpDir.isFile();
	//bool isDir = tmpDir.isDirectory();
	//bool canRead = tmpDir.canRead();
	bool canWrite = tmpDir.canWrite();

	//some file stuff
	File tmpFile(Path(tmpPath, "PocoFileSample.dat"));
	if (tmpFile.createFile())
	{
		tmpFile.setSize(10000);
		File tmpFile2(Path(tmpPath, "PocoFileSample2.dat"));
		tmpFile.copyTo(tmpFile2.path());
		Poco::Timestamp now;
		tmpFile.setLastModified(now);
		tmpFile.setReadOnly();
		canWrite = tmpFile.canWrite();
		tmpFile.setWriteable();
		canWrite = tmpFile.canWrite();
	}

	//show all files in dir
	{
		vector<string> files;
		tmpDir.list(files);
		vector<string>::iterator it = files.begin();
		for (; it != files.end(); ++it)
		{
			cout << *it << endl;
		}
		tmpDir.remove(true);
	}

	//directory iterator
	{
		string cwd(Path::current());
		DirectoryIterator it(cwd);
		DirectoryIterator end;
		while (it != end)
		{
			cout << it.name();
			if (it->isFile())
				cout << it->getSize();
			cout << endl;
			Path p(it.path());
			++it;
		}
	}
}

//==========================================================================================================================

string FileUtils::removeIllegalFilenameChars(string filename)
{//==========================================================================================================================

	string *s = &filename;
	string illegalChars = "\\/:?\"<>|*";
	for (auto it = s->begin(); it < s->end(); ++it) {
		bool found = illegalChars.find(*it) != string::npos;
		if (found) {
			*it = ' ';
		}
	}
	return filename;
}

//
////==========================================================================================================================
//char* textFileRead(string filename)
//{//==========================================================================================================================
//
//	filename = Main::getPath() + filename;
//
//	FILE* fp;
//	char* content = nullptr;
//
//	long count = 0;
//
//	if (filename != "")
//	{
//		fp = fopen(filename.c_str(), "rt");
//
//		if (fp != nullptr)
//		{
//			fseek(fp, 0, SEEK_END);
//			count = ftell(fp);
//			rewind(fp);
//
//			if (count > 0)
//			{
//				content = (char *)malloc(sizeof(char) * (count + 1));
//				count = fread(content, sizeof(char), count, fp);
//				content[count] = '\0';
//			}
//			fclose(fp);
//		}
//	}
//	return content;
//}

//==========================================================================================================================
void* HARDWARE_load_file(string filename)
{//==========================================================================================================================

	filename = Main::getPath() + filename;

	char* filepointer = NULL;
	FILE* file = nullptr;
	long size;


	//FileUtils::fixPath(filename);

	file = fopen(filename.c_str(), "rb");

	if (file != NULL)
	{
		//get file size using stat
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		rewind(file);

		//fprintf(stdout,"loaded file: %s size: %d\n",fullname,size);

		filepointer = (char*)malloc(size * sizeof(char));

		if (filepointer == NULL)
		{
			ERROR_set_error(filename);
			ERROR_set_error(" malloc failed\n");
		}

		//size_t bytesRead =
        fread(filepointer, 1, size, file);
	}
	if (file == NULL)
	{
		ERROR_set_error(filename);
		ERROR_set_error(" was not found\n");
	}

	fclose(file);
	//HARDWARE_wait_for_vbl();

	return (void*)filepointer;
}

//==========================================================================================================================
void HARDWARE_unload_file(void** data_pointer)
{//==========================================================================================================================

	if (*data_pointer != NULL)
	{
		free(*data_pointer);

		*data_pointer = NULL;
	}
}

//==========================================================================================================================
long HARDWARE_get_file_size(string filename)//HARDWARE_FSFile[HARDWARE_FSGetFile(0,filename,"")].Length;
{//==========================================================================================================================

	filename = Main::getPath() + filename;

	//char* filepointer=NULL;
	FILE* file = nullptr;
	long size = 0;

	file = fopen(filename.c_str(), "rb");
	if (file != NULL)
	{
		// get file size using stat
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		rewind(file);
	}
	if (file == NULL)
	{
		ERROR_set_error(filename);
		ERROR_set_error(" was not found\n");
	}

	fclose(file);

	return size;
}

//FileUtils* FileUtils::fileUtils = nullptr;

string FileUtils::appDataPath = "";
string FileUtils::cacheDir = "";
//string "/" = "";
string FileUtils::bigDataURL = "";
string FileUtils::smallDataURL = "";

FileUtils::FileUtils()
{ //=========================================================================================================================

//	   if (Main::debugMode == true) //DEBUG
//	   {
//	      bigDataURL = BobNet::debugBigDataURL;
//	      smallDataURL = BobNet::debugSmallDataURL;
//	   }
//	   else
//	   {
	      bigDataURL = BobNet::releaseBigDataURL;
	      smallDataURL = BobNet::releaseSmallDataURL;
	  // }
	//
	//   //cacheDir = "C:\\bobsGameCache\\";
	//

	//slash = "/";// prop->getProperty("file.separator"); //also File.separatorChar, File.separator
	//cacheDir = "";// prop->getProperty("user.home") + slash + ".bobsGame" + slash;
	//fileUtils = this;
	appDataPath = string(SDL_GetPrefPath("Bob Corporation", "bob's game"));
	cacheDir = appDataPath+"cache/";
}

BufferedImage* FileUtils::readBufferedImageFromFile(BobFile* file)
{
	return new BufferedImage();
}

//ArrayList<string>* FileUtils::readLines(u8* get_resource_as_stream)
//{
//	return new ArrayList<string>;
//}

#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Delegate.h"
#include "Poco/Zip/Decompress.h"
#include "Poco/Process.h"
#include "Poco/DirectoryIterator.h"
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Process;
using Poco::Path;
using Poco::Delegate;
using Poco::Zip::Decompress;

void FileUtils::makeDir(const string& cs)
{

	File f = File(cs);
	if (f.exists() == false)
	{
		f.createDirectory();
	}

	
}

//
//
//u8* FileUtils::getResourceAsStream(const string& filename)
//{ //=========================================================================================================================
//
//	//
//	//   //don't use absolute paths starting from the folder we are in. /whatever.jpg
//	//   if (String::startsWith(filename, "/") == true && String::startsWith(filename, System::getProperty("user.home")) == false)
//	//   {
//	//      filename = filename.substr(1); //cut off the /
//	//      log.debug("Don't use absolute paths, fix this.");
//	//   }
//	//
//	//
//	//   //if we are using stuff from /res/ we should get them from the ClassLoader which gets them from inside the JAR (but removed from /res/ for some reason)
//	//   if (String::startsWith(filename, "res/") == true)
//	//   {
//	//      filename = filename.substr(4);
//	//      InputStream* is = utils->getClass().getClassLoader().getResourceAsStream(filename);
//	//
//	//      if (is == nullptr)
//	//      {
//	//         log.error("Could not find file in ClassLoader: " + filename);
//	//      }
//	//
//	//      return is;
//	//   }
//	//   else //we are accessing from the hard disk. try the resource loader which will get it as a file.
//	//   {
//	//      FileInputStream* stream = nullptr;
//	//      try
//	//      {
//	//         File* file = new File(filename);
//	//
//	//         if (!file->exists())
//	//         {
//	//            file = new File(new File("."), filename);
//	//         }
//	//
//	//         if (!file->exists())
//	//         {
//	//            log.error("Could not find file: " + filename);
//	//            return nullptr;
//	//         }
//	//         else
//	//         {
//	//            stream = new FileInputStream(file);
//	//         }
//	//      }
//	//      catch (IOException e)
//	//      {
//	//         log.error("Error opening file: " + filename);
//	//         //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
//	//         delete stream;
//	//      }
//	//
//	//      if (stream == nullptr)
//	//      {
//	//      }
//	//
//	//
//	//      return stream;
//	//   }
//	return new u8;
//}

//
//string FileUtils::getResource(const string& filename)
//{ //=========================================================================================================================
//
//
//	//   //don't use absolute paths starting from the folder we are in. /whatever.jpg
//	//   if (String::startsWith(filename, "/") == true && String::startsWith(filename, System::getProperty("user.home")) == false)
//	//   {
//	//      filename = filename.substr(1); //cut off the /
//	//      log.debug("Don't use absolute paths, fix this.");
//	//   }
//	//
//	//
//	//   //if we are using stuff from /res/ we should get them from the ClassLoader which gets them from inside the JAR (but removed from /res/ for some reason)
//	//   if (String::startsWith(filename, "res/") == true)
//	//   {
//	//      filename = filename.substr(4);
//	//      URL* is = utils->getClass().getClassLoader().getResource(filename);
//	//
//	//      if (is == nullptr)
//	//      {
//	//         log.error("Could not find file in ClassLoader: " + filename);
//	//      }
//	//
//	//      return is;
//	//   }
//	//   else //we are accessing from the hard disk. try the resource loader which will get it as a file.
//	//   {
//	//      try
//	//      {
//	//         File* file = new File(filename);
//	//         if (file->exists() == false)
//	//         {
//	//            file = new File(new File("."), filename);
//	//         }
//	//
//	//
//	//         if (file->exists() == false)
//	//         {
//	//            log.error("Could not find file: " + filename);
//	//
//	//            //if(BobNet.debugMode)new Exception().printStackTrace();
//	//
//	//            return nullptr;
//	//         }
//	//         else
//	//         {
//	//            return file->toURI().toURL();
//	//         }
//	//      }
//	//      catch (IOException e)
//	//      {
//	//         log.error("Error opening file: " + filename);
//	//         return nullptr;
//	//      }
//	//   }
//	return "";
//}

//
//short* FileUtils::oldLoadShortIntFile(const string& filename)
//{ //=========================================================================================================================
//	//   File* file = new File(filename);
//	//
//	//
//	//   int* intArray(((int)(file->length())) / 2);
//	//
//	//   BufferedInputStream* bin = new BufferedInputStream(FileUtils::getResourceAsStream(filename));
//	//
//	//   try
//	//   {
//	//      int sbyte1 = bin->read(); //signed byte 1
//	//      int sbyte2 = bin->read();
//	//      int i = 0;
//	//
//	//      while (sbyte1 != -1 || sbyte2 != -1)
//	//      {
//	//         int ubyte1 = sbyte1 & 0xFF;
//	//         int ubyte2 = sbyte2 & 0xFF;
//	//
//	//         int result = (ubyte2 << 8) + ubyte1;
//	//
//	//         intArray->get(i) = result;
//	//         i++;
//	//         sbyte1 = bin->read();
//	//         sbyte2 = bin->read();
//	//      }
//	//
//	//      bin->close();
//	//   }
//	//   catch (IOException e)
//	//   {
//	//      e->printStackTrace();
//	//   }
//	//
//	//   return intArray;
//	return new short;
//}

////=========================================================================================================================
//vector<uint16_t>* FileUtils::loadShortFile(string filename)
//{//=========================================================================================================================
//
//	ByteArray *byteArray = loadByteFileFromExePath(filename);
//	
//	vector<uint16_t> *shortArray = new vector<uint16_t>(byteArray->size() / 2);
//	
//			for(int x=0;x<shortArray->size();x++)
//			{
//				u8 sbyte1=(*byteArray)[x*2+0];//signed byte 1
//				u8 sbyte2=(*byteArray)[x*2+1];
//	
//	
//				u8 ubyte1 = sbyte1 & 0xFF;
//				u8 ubyte2 = sbyte2 & 0xFF;
//	
//				short result = (ubyte1<<8) + ubyte2;
//	
//				(*shortArray)[x]=result;
//			}
//
//			delete byteArray;//does this leak? delete[] ?
//	//-------------------
//	//alt
//	//-------------------
//
//	//return getIntArrayFromByteArray(loadByteFile(filename));
//
//	return shortArray;
//}

//=========================================================================================================================
IntArray* FileUtils::loadIntFile(string filename)
{//=========================================================================================================================

	ByteArray* byteArray = loadByteFile(filename);

	IntArray* intArray = new IntArray(byteArray->size() / 4);

	for (int x = 0; x<intArray->size(); x++)
	{
		u8 sbyte1 = byteArray->data()[x * 4 + 0];//signed byte 1
		u8 sbyte2 = byteArray->data()[x * 4 + 1];
		u8 sbyte3 = byteArray->data()[x * 4 + 2];
		u8 sbyte4 = byteArray->data()[x * 4 + 3];

		u8 ubyte1 = sbyte1 & 0xFF;
		u8 ubyte2 = sbyte2 & 0xFF;
		u8 ubyte3 = sbyte3 & 0xFF;
		u8 ubyte4 = sbyte4 & 0xFF;

		int result = (ubyte1 << 24) + (ubyte2 << 16) + (ubyte3 << 8) + ubyte4;

		intArray->data()[x] = result;
	}

	delete byteArray;//does this leak? delete[] ?
					 //-------------------
					 //alt
					 //-------------------

					 //return getIntArrayFromByteArray(loadByteFile(filename));

	return intArray;
}

IntArray* FileUtils::loadIntFileFromExePath(string filename)
{//=========================================================================================================================
	filename = Main::getPath() + filename;

	return loadIntFile(filename);
}

// ===============================================================================================
ByteArray* FileUtils::getByteArrayFromIntArray(IntArray*intArray)
{// ===============================================================================================

	ByteArray* byteArray = new ByteArray(intArray->size() * 4);

	for (int i = 0; i < intArray->size(); i++)
	{

		int n = intArray->data()[i];

		byteArray->data()[i*4+0]=((n >> 24) & 0xFF);
		byteArray->data()[i*4+1]=((n >> 16) & 0xFF);
		byteArray->data()[i*4+2]=((n >> 8) & 0xFF);
		byteArray->data()[i*4+3]=(n & 0xFF);
	}

	return byteArray;
}



//save 16 bit to binary
//load 16 bit

//load text file into read buffer?
//load text file into chars?
//load text file into one string
//load text file c way
//save strings to text file
//save string to text file
//save binary to text file

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
//=========================================================================================================================
// trim from start (in place)
void FileUtils::ltrim(std::string s) 
{//=========================================================================================================================
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
}
//=========================================================================================================================
// trim from end (in place)
void FileUtils::rtrim(std::string s) 
{//=========================================================================================================================
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}//=========================================================================================================================

// trim from both ends (in place)
void FileUtils::trim(std::string s) 
{//=========================================================================================================================
	ltrim(s);
	rtrim(s);
}
//=========================================================================================================================
// trim from start (copying)

string FileUtils::ltrimmed(std::string s) 
{//=========================================================================================================================
	ltrim(s);
	return s;
}
//=========================================================================================================================
// trim from end (copying)

string FileUtils::rtrimmed(std::string s) 
{//=========================================================================================================================
	rtrim(s);
	return s;
}
//=========================================================================================================================
// trim from both ends (copying)

string FileUtils::trimmed(std::string s) 
{//=========================================================================================================================
	trim(s);
	return s;
}

//=========================================================================================================================

string FileUtils::loadTextFileAndTrim(string filename)
{//=========================================================================================================================

	ifstream t(filename);
	string str;

	t.seekg(0, ios::end);
	str.reserve((size_t)t.tellg());
	t.seekg(0, ios::beg);

	str.assign((istreambuf_iterator<char>(t)),
		istreambuf_iterator<char>());

	rtrim(str);
	//str.erase(str.find_last_not_of(" \n\r\t") + 1);//right trim space tab return

	//log.debug("Loaded file: " + filename + " Size: " + to_string(str.length()));
	return str;
}

//=========================================================================================================================

string FileUtils::loadTextFileFromExePathAndTrim(string filename)
{//=========================================================================================================================

	filename = Main::getPath() + filename;
	return loadTextFileAndTrim(filename);
}

//=========================================================================================================================
ArrayList<string>* FileUtils::loadTextFileIntoVectorOfStringsAndTrim(string filename)
{//=========================================================================================================================

	ArrayList<string>* lines = new ArrayList<string>();

	string line;
	stringstream dosString;
	ifstream inFile;
	inFile.open(filename);
	while (getline(inFile, line))
	{
		rtrim(line);
		//line.erase(line.find_last_not_of(" \n\r\t") + 1);
		lines->add(line);
	}
	return lines;
}

//=========================================================================================================================
ArrayList<string>* FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim(string filename)
{//=========================================================================================================================

	filename = Main::getPath() + filename;
	return loadTextFileIntoVectorOfStringsAndTrim(filename);
}


////=========================================================================================================================
//u8* FileUtils::loadByteFileFromExePath(string filename, int* size_return)
//{//=========================================================================================================================
//
//	filename = Main::getPath() + filename;
//
//
//
//
////	char* cfilepointer = NULL;
////	FILE* cfile;
////	int csize;
////
////	cfile = fopen(fullname, "rb");
////	if (cfile != NULL)
////	{
////		//get file size using stat
////		fseek(cfile, 0, SEEK_END);
////		csize = ftell(cfile);
////		rewind(cfile);
////
////		//fprintf(stdout,"loaded file: %s size: %d\n",fullname,size);
////
////		cfilepointer = (char*)malloc(csize * sizeof(char));
////
////		if (cfilepointer == NULL)
////		{
////			//ERROR_set_error(fullname);
////			//log.error(string(fullname) + " malloc failed");
////		}
////
////		fread(cfilepointer, 1, csize, cfile);
////	}
////	if (cfile == NULL)
////	{
////		//ERROR_set_error(fullname);
////		log.error(string(fullname) + " could not be opened, probably not found");
////	}
////	fclose(cfile);
//////	//HARDWARE_wait_for_vbl();
////
//
//	
//
//	char* cppfilepointer = NULL;
//	streampos cppsize;
//
//	ifstream cppfile(filename, ios::in | ios::binary | ios::ate);
//	if (cppfile.is_open())
//	{
//		cppsize = cppfile.tellg();
//		cppfilepointer = new char[(int)cppsize];
//		cppfile.seekg(0, ios::beg);
//		cppfile.read(cppfilepointer, cppsize);
//		cppfile.close();
//
//		if (size_return != nullptr)*size_return = cppsize;
//		//log.info("Loaded file: " + filename);
//	}
//	else
//	{
//		log.error("Could not open file: "+filename);
//	}
//	
//	return (u8*)cppfilepointer;
//}


//=========================================================================================================================
ByteArray* FileUtils::loadByteFile(string filename)
{//=========================================================================================================================


//	Uint32 start, now;
//	start = SDL_GetPerformanceCounter();



	char* cfilepointer = NULL;
	FILE* cfile;
	int csize;
	
	cfile = fopen(filename.c_str(), "rb");
	if (cfile != NULL)
	{
		//get file size using stat
		fseek(cfile, 0, SEEK_END);
		csize = ftell(cfile);
		rewind(cfile);
	
		//fprintf(stdout,"loaded file: %s size: %d\n",fullname,size);
	
		cfilepointer = (char*)malloc(csize * sizeof(char));
	
		if (cfilepointer == NULL)
		{
			//ERROR_set_error(fullname);
			//log.error(string(fullname) + " malloc failed");
		}
	
		fread(cfilepointer, 1, csize, cfile);
	}
	if (cfile == NULL)
	{
		//ERROR_set_error(fullname);
		log.error(string(filename) + " could not be opened, probably not found");
	}
	fclose(cfile);

	ByteArray* byteArray = new ByteArray((u8*)cfilepointer, csize);

	return byteArray;

//
//	now = SDL_GetPerformanceCounter();
//	log.info("fread took " + to_string((double)((now - start)*1000) / SDL_GetPerformanceFrequency()) + "ms");
//	start = SDL_GetPerformanceCounter();
//
//
//
//		char* cppfilepointer = NULL;
//		streampos cppsize;
//	
//		ifstream cppfile(filename, ios::in | ios::binary | ios::ate);
//		if (cppfile.is_open())
//		{
//			cppsize = cppfile.tellg();
//			cppfilepointer = new char[(int)cppsize];
//			cppfile.seekg(0, ios::beg);
//			cppfile.read(cppfilepointer, cppsize);
//			cppfile.close();
//	
//			//if (size_return != nullptr)*size_return = cppsize;
//			//log.info("Loaded file: " + filename);
//		}
//		else
//		{
//			log.error("Could not open file: "+filename);
//		}
//
//
//
//	now = SDL_GetPerformanceCounter();
//	log.info("ifstream read took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
//	start = SDL_GetPerformanceCounter();


//	// open the file:
//	std::ifstream file(filename, std::ios::binary);
//
//	// Stop eating new lines in binary mode!!!
//	file.unsetf(std::ios::skipws);
//
//	// get its size:
//	std::streampos fileSize;
//
//	file.seekg(0, std::ios::end);
//	fileSize = file.tellg();
//	file.seekg(0, std::ios::beg);
//
//	// reserve capacity
//	std::vector<u8> *vec = new vector<u8>();
//	vec->reserve(fileSize);
//
//	// read the data:
//	vec->insert(vec->begin(),
//		std::istream_iterator<u8>(file),
//		std::istream_iterator<u8>());
//
//	now = SDL_GetPerformanceCounter();
//	log.info("vector iterator took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
//	start = SDL_GetPerformanceCounter();

//	return vec;

}

//=========================================================================================================================
ByteArray* FileUtils::loadByteFileFromExePath(string filename)
{//=========================================================================================================================

	filename = Main::getPath() + filename;
	return loadByteFile(filename);
}

//=========================================================================================================================
std::string FileUtils::byteArrayToHexString(u8 *data, unsigned long len)
{//=========================================================================================================================
	constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7','8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	std::string s(len * 2, ' ');
	for (unsigned long i = 0; i < len; ++i) {
		s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
		s[2 * i + 1] = hexmap[data[i] & 0x0F];
	}
	return s;
}
//=========================================================================================================================
u8* FileUtils::hexStringToByteArray(const string &hex)
{//=========================================================================================================================
	u8* bytes = new u8[hex.length()/2];

	for (unsigned int i = 0; i < hex.length(); i += 2) 
	{
		std::string byteString = hex.substr(i, 2);
		char byte = (char)strtol(byteString.c_str(), NULL, 16);
		bytes[i/2]=byte;
	}

	return bytes;
}

//#include <zip.h>

/*
base64.cpp and base64.h

Copyright (C) 2004-2008 René Nyffenegger

This source code is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
claim that you wrote the original source code. If you use this source code
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

René Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static inline bool is_base64(u8 c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}


#include "base64.h"

//=========================================================================================================================
std::string FileUtils::encodeByteArrayToBase64StringAlt(u8 const* bytes_to_encode, unsigned long in_len)
{//=========================================================================================================================

	char* out = new char[in_len];
	Base64::Encode((char*)bytes_to_encode, in_len, out, in_len);

	string outs(out, in_len);

	return outs;
}

#include "Poco/Base64Decoder.h"

//=========================================================================================================================
ByteArray* FileUtils::decodeBase64StringToByteArrayAlt(std::string const& encoded_string)//, unsigned long &returnLength)
{//=========================================================================================================================

	{
		string outs;
		string in(encoded_string);
		Base64::Decode(in, &outs);


		ByteArray* outv = new ByteArray(outs.length());
		for (int i = 0; i < outs.length(); i++)
		{
			outv->data()[i]=(outs[i]);

		}
		return outv;
	}

//	{
//		istringstream istr(encoded_string);
//		ostringstream ostr;
//		Poco::Base64Decoder b64in(istr);
//		copy(std::istreambuf_iterator<char>(b64in),
//			std::istreambuf_iterator<char>(),
//			std::ostreambuf_iterator<char>(ostr));
//		//cout << ostr.str(); // returns full decoded output
//
//		string outs = ostr.str();
//
//	}


}

//=========================================================================================================================
std::string FileUtils::encodeByteArrayToBase64String(u8 const* bytes_to_encode, unsigned long in_len)
{//=========================================================================================================================



	std::string ret;
	int i = 0;
	int j = 0;
	u8 char_array_3[3];
	u8 char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i <4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;

}
//=========================================================================================================================
ByteArray* FileUtils::decodeBase64StringToByteArray(std::string const& encoded_string)//, unsigned long &returnLength)
{//=========================================================================================================================





	long in_len = (long)encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	u8 char_array_4[4], char_array_3[3];
	ByteArray* ret = new ByteArray(in_len);

	int n = 0;
	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) 
	{
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) 
		{
			for (i = 0; i <4; i++)
				char_array_4[i] = (u8)base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
			{
				ret->data()[n++] = (char_array_3[i]);
			}
			i = 0;
		}
	}

	if (i) 
	{
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = (u8)base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret->data()[n++] = (char_array_3[j]);
	}

	return ret;

//	u8* data = new u8[ret.size()];
//	for(int x=0;x<ret.size();x++)
//	{
//		data[x] = ret.at(x);
//	}
//	
//	returnLength = ret.size();
//	return data;
}

//
//#include <minilzo-2.10/minilzo.h>
///* Work-memory needed for compression. Allocate memory in units
//* of 'lzo_align_t' (instead of 'char') to make sure it is properly aligned.
//*/
//
//#define HEAP_ALLOC(var,size) \
//    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]
//
//static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);
//
//
//
////bool zip = false;
////bool lzo = true;
////
//// ===============================================================================================
//
//string FileUtils::lzoByteArrayToBase64String(const u8* byteArray, unsigned long sourceLength)
//{ // ===============================================================================================
//
//
//	string zipDataHexString = "";
//
//	
//	
//	const unsigned long maximumCompressedLength = (sourceLength + sourceLength / 16 + 64 + 3);
//
//	u8 * __LZO_MMODEL compressedBytes = new u8[maximumCompressedLength];
//
//	int r;
//	//lzo_uint in_len;
//	lzo_uint compressedLength;
//	//lzo_uint new_len;
//
//	r = lzo1x_1_compress(byteArray, sourceLength, compressedBytes, &compressedLength, wrkmem);
//	if (r == LZO_E_OK)
//	{
//		//log.debug("Compressed " + to_string(sourceLength) + " bytes into " + to_string(compressedLength) + " bytes");
//	}
//	else
//	{
//		/* this should NEVER happen */
//		log.error("Compression failed:" + to_string(r));
//		return  "";
//	}
//	/* check for an incompressible block */
//	if (compressedLength >= sourceLength)
//	{
//		//log.debug("This block contains incompressible data.");
//		//return "";
//	}
//
//	zipDataHexString = encodeByteArrayToBase64String(compressedBytes, compressedLength);
//	//log.debug("Encoded from " + to_string(compressedLength) + " to " + to_string(zipDataHexString.length()) + " bytes");
//
//	delete[] compressedBytes;
//	
//
//	return zipDataHexString;
//}
//
//// ===============================================================================================
//u8* FileUtils::unlzoBase64StringToByteArray(const string &zippedBytesAsBase64String, unsigned long &returnLength)
//{// ===============================================================================================
//
//	//unsigned long zippedLength;
//	ByteArray* zippedBytes = decodeBase64StringToByteArray(zippedBytesAsBase64String);// , zippedLength);
//	//log.debug("Decoded " + to_string(zippedBytesAsString.length()) + " bytes into " + to_string(zippedLength) + " bytes");
//
//
//	int compressStatus;
//	//lzo_uint in_len;
//	lzo_uint uncompressedLength = zippedBytes->size() * 100;
//	//lzo_uint new_len;
//
//	u8 *uncompressedBytes = new u8[uncompressedLength];
//	//u8 * __LZO_MMODEL uncompressedBytes = new u8[uncompressedLength];
//
//	//new_len = in_len;
//	compressStatus = lzo1x_decompress(zippedBytes->data(), zippedBytes->size(), uncompressedBytes, &uncompressedLength, NULL);
//
//	while (compressStatus == LZO_E_INPUT_OVERRUN)
//	{
//		delete[] uncompressedBytes;
//		log.error("Decompression failed, increasing buffer.");
//		uncompressedLength *= 2;
//		uncompressedBytes = new u8[uncompressedLength];
//		compressStatus = lzo1x_decompress(zippedBytes->data(), zippedBytes->size(), uncompressedBytes, &uncompressedLength, NULL);
//	}
//
//	if (compressStatus == LZO_E_OK)
//	{
//		//log.debug("Decompressed " + to_string(zippedLength) + " bytes into " + to_string(out_len) + " bytes");
//	}
//	else
//	{
//		// this should NEVER happen 
//		log.error("Decompression failed:" + to_string(compressStatus));
//		return nullptr;
//	}
//
//	delete zippedBytes;
//
//	returnLength = uncompressedLength;
//	return uncompressedBytes;
//	
//
//}


#include "lz4-1.7.5/lib/lz4.h"

// ===============================================================================================

string FileUtils::lz4ByteArrayToBase64String(const u8* byteArray, unsigned long sourceLength)
{ // ===============================================================================================





	// LZ4 provides a function that will tell you the maximum size of compressed output based on input data via LZ4_compressBound().
	const size_t max_dst_size = LZ4_compressBound(sourceLength);
	// We will use that size for our destination boundary when allocating space.
	char *compressed_data = (char*)malloc(max_dst_size);


	int return_value = 0;
	return_value = LZ4_compress_default((char*)byteArray, compressed_data, sourceLength, max_dst_size);
	// Check return_value to determine what happened.
	if (return_value < 0)
		log.error("A negative result from LZ4_compress_default indicates a failure trying to compress the data.  See exit code (echo $?) for value returned.");
	if (return_value == 0)
		log.error("Compression worked, but was stopped because the destination buffer couldn't hold all the information.");

//	if (return_value > 0)
//		printf("We successfully compressed some data!\n");

	const size_t compressed_data_size = return_value;


	string zipDataHexString = "";
	zipDataHexString = encodeByteArrayToBase64String((u8*)compressed_data, compressed_data_size);

	free(compressed_data);


	return zipDataHexString;



}

// ===============================================================================================
u8* FileUtils::unlz4Base64StringToByteArray(const string &zippedBytesAsBase64String, unsigned long &returnLength)
{// ===============================================================================================

 //unsigned long zippedLength;
	ByteArray* zippedBytes = decodeBase64StringToByteArray(zippedBytesAsBase64String);// , zippedLength);
	//log.debug("Decoded " + to_string(zippedBytesAsString.length()) + " bytes into " + to_string(zippedLength) + " bytes");



	int maxUncompressedBufferLength = zippedBytes->size() * 100;
	u8 *uncompressedBytesBuffer = new u8[maxUncompressedBufferLength];

	int statusOrUncompressedSize = LZ4_decompress_safe((char*)(zippedBytes->data()), (char*)uncompressedBytesBuffer, zippedBytes->size(), maxUncompressedBufferLength);
	int retries = 0;
	while (statusOrUncompressedSize < 0 && retries < 4)
	{
		//log.error("A negative result from LZ4_decompress_fast indicates a failure trying to decompress the data.");

		retries++;

		delete[] uncompressedBytesBuffer;
		log.error("Decompression failed, increasing buffer.");
		maxUncompressedBufferLength *= 2;
		uncompressedBytesBuffer = new u8[maxUncompressedBufferLength];
		statusOrUncompressedSize = LZ4_decompress_safe((char*)(zippedBytes->data()), (char*)uncompressedBytesBuffer, zippedBytes->size(), maxUncompressedBufferLength);
	}

	if (statusOrUncompressedSize == 0)
		log.error("I'm not sure this function can ever return 0.  Documentation in lz4.h doesn't indicate so.");



//	if (return_value > 0)
//		printf("We successfully decompressed some data!\n");

	delete zippedBytes;

	if(statusOrUncompressedSize < 0)
	{
		delete[] uncompressedBytesBuffer;
		returnLength = 0;
		return nullptr;
	}

	u8* returnByteArray = new u8[statusOrUncompressedSize];

	for(int i=0;i<statusOrUncompressedSize;i++)
	{
		returnByteArray[i] = uncompressedBytesBuffer[i];
	}

	delete[] uncompressedBytesBuffer;


	returnLength = statusOrUncompressedSize;
	return returnByteArray;



}




#include "miniz.c"
typedef u8 uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

string FileUtils::zipByteArrayToBase64String(const u8* byteArray, unsigned long sourceLength)
{ // ===============================================================================================

	//   string outStr = "";
	//   try
	//   {
	//      ByteArrayOutputStream* out = new ByteArrayOutputStream();
	//
	//      GZIPOutputStream* gzip = new GZIPOutputStream(out);
	//      gzip->write(byteArray);
	//      gzip->close();
	//
	//      
	//      outStr = out->toString("ISO-8859-1");
	//   }
	//   catch (exception& e)
	//   {
	//      e.printStackTrace();
	//   }
	//   return outStr;


//
//	
//	zip_source_t *src = nullptr;
//	zip_t *za = nullptr;
//	zip_error_t error;
//	void *data = nullptr;
//	//size_t sourceLength;
//
//	zip_error_init(&error);
//	/* create source from buffer */
//	if ((src = zip_source_buffer_create(byteArray, sourceLength, 1, &error)) == NULL) {
//		fprintf(stderr, "can't create source: %s\n", zip_error_strerror(&error));
//		//free(byteArray);
//		zip_error_fini(&error);
//		return nullptr;
//	}
//
//	/* open zip archive from source */
//	if ((za = zip_open_from_source(src, ZIP_CREATE, &error)) == NULL) {
//		fprintf(stderr, "can't open zip from source: %s\n", zip_error_strerror(&error));
//		zip_source_free(src);
//		zip_error_fini(&error);
//		return nullptr;
//	}
//	zip_error_fini(&error);
//
//	/* we'll want to read the data back after zip_close */
//	zip_source_keep(src);
//
//
//	/* close archive */
//	if (zip_close(za) < 0) {
//		fprintf(stderr, "can't close zip archive: %s\n", zip_strerror(za));
//		return nullptr;
//	}
//
//	int zipsize = 0;
//
//	/* copy new archive to buffer */
//
//	if (zip_source_is_deleted(src)) {
//		/* new archive is empty, thus no data */
//		data = NULL;
//	}
//	else {
//		zip_stat_t zst;
//
//		if (zip_source_stat(src, &zst) < 0) {
//			fprintf(stderr, "can't stat source: %s\n", zip_error_strerror(zip_source_error(src)));
//			return nullptr;
//		}
//
//		zipsize = zst.sourceLength;
//
//		if (zip_source_open(src) < 0) {
//			fprintf(stderr, "can't open source: %s\n", zip_error_strerror(zip_source_error(src)));
//			return nullptr;
//		}
//		if ((data = malloc(zipsize)) == NULL) {
//			fprintf(stderr, "malloc failed: %s\n", strerror(errno));
//			zip_source_close(src);
//			return nullptr;
//		}
//		if ((zip_uint64_t)zip_source_read(src, data, zipsize) < zipsize) {
//			fprintf(stderr, "can't read data from source: %s\n", zip_error_strerror(zip_source_error(src)));
//			zip_source_close(src);
//			free(data);
//			return nullptr;
//		}
//		zip_source_close(src);
//	}
//
//	/* we're done with src */
//	zip_source_free(src);
//	delete[] byteArray;
//
	string zipDataHexString = "";

	//uint step = 0;
	int compressStatus;
	//uLong sourceLength = sourceLength;// (uLong)strlen(s_pStr);
	uLong compressedLength = compressBound(sourceLength);
	//uLong uncomp_len = sourceLength;
	u8 *compressedBytes = nullptr;
	//uint total_succeeded = 0;

	//printf("miniz.c version: %s\n", MZ_VERSION);

	// Allocate buffers to hold compressed and uncompressed data.
	compressedBytes = (mz_uint8 *)malloc((size_t)compressedLength);
	if ((!compressedBytes))
	{
		log.error("Out of memory!");
		return "";
	}

	// Compress the string.
	compressStatus = compress(compressedBytes, &compressedLength, byteArray, sourceLength);
	if (compressStatus != Z_OK)
	{
		log.error("Compress failed");
		free(compressedBytes);
			
		return "";
	}

	//log.debug("Compressed from " + to_string(sourceLength) + " to " + to_string(compressedLength) + " bytes");

	zipDataHexString = encodeByteArrayToBase64String(compressedBytes, compressedLength);
	//log.debug("Encoded from " + to_string(compressedLength) + " to " + to_string(zipDataHexString.length()) + " bytes");

	free(compressedBytes);
	


	return zipDataHexString;
}

// ===============================================================================================
u8* FileUtils::unzipBase64StringToByteArray(const string &zippedBytesAsBase64String, unsigned long &returnLength)
{// ===============================================================================================

	//   GZIPInputStream gis = null;
	//
	//   try
	//   {
	//      ByteArrayInputStream is = new ByteArrayInputStream(zippedBytesAsString.getBytes("ISO-8859-1"));
	//
	//      gis = new GZIPInputStream(is);
	//
	//      return IOUtils.toByteArray(new InputStreamReader(gis, "ISO-8859-1"), "ISO-8859-1");
	//   }
	//   catch (Exception e)
	//   {
	//      e.printStackTrace();
	//   }
	//   return null;


//
//	//unzip the byte array to a new byte array
//	zip_source_t *src = nullptr;
//	zip_t *za = nullptr;
//	zip_error_t error;
//	void *data = nullptr;
//	//size_t size;
//
//	zip_error_init(&error);
//	/* create source from buffer */
//	if ((src = zip_source_buffer_create(byteArray, size, 1, &error)) == NULL) {
//		fprintf(stderr, "can't create source: %s\n", zip_error_strerror(&error));
//		//free(byteArray);
//		zip_error_fini(&error);
//		return nullptr;
//	}
//
//	/* open zip archive from source */
//	if ((za = zip_open_from_source(src, 0, &error)) == NULL) {
//		fprintf(stderr, "can't open zip from source: %s\n", zip_error_strerror(&error));
//		zip_source_free(src);
//		zip_error_fini(&error);
//		return nullptr;
//	}
//	zip_error_fini(&error);
//
//	/* we'll want to read the data back after zip_close */
//	zip_source_keep(src);
//
//
//	/* close archive */
//	if (zip_close(za) < 0) {
//		fprintf(stderr, "can't close zip archive: %s\n", zip_strerror(za));
//		return nullptr;
//	}
//
//	int zipsize = 0;
//
//	/* copy new archive to buffer */
//
//	if (zip_source_is_deleted(src)) {
//		/* new archive is empty, thus no data */
//		data = NULL;
//	}
//	else {
//		zip_stat_t zst;
//
//		if (zip_source_stat(src, &zst) < 0) {
//			fprintf(stderr, "can't stat source: %s\n", zip_error_strerror(zip_source_error(src)));
//			return nullptr;
//		}
//
//		zipsize = zst.size;
//
//		if (zip_source_open(src) < 0) {
//			fprintf(stderr, "can't open source: %s\n", zip_error_strerror(zip_source_error(src)));
//			return nullptr;
//		}
//		if ((data = malloc(zipsize)) == NULL) {
//			fprintf(stderr, "malloc failed: %s\n", strerror(errno));
//			zip_source_close(src);
//			return nullptr;
//		}
//		if ((zip_uint64_t)zip_source_read(src, data, zipsize) < zipsize) {
//			fprintf(stderr, "can't read data from source: %s\n", zip_error_strerror(zip_source_error(src)));
//			zip_source_close(src);
//			free(data);
//			return nullptr;
//		}
//		zip_source_close(src);
//	}
//
//	/* we're done with src */
//	zip_source_free(src);
	

	//unsigned long zippedLength;
	ByteArray* zippedBytes = decodeBase64StringToByteArray(zippedBytesAsBase64String);// , zippedLength);
	//log.debug("Decoded " + to_string(zippedBytesAsString.length()) + " bytes into " + to_string(zippedLength) + " bytes");


	//uint step = 0;
	int compressStatus;
	//uLong src_len = sourceLength;// (uLong)strlen(s_pStr);
	uLong uncompressedLength = zippedBytes->size() * 40;
	//uint total_succeeded = 0;

	u8 *uncompressedBytes = new u8[uncompressedLength];
	//uncompressedBytes = (mz_uint8 *)malloc((size_t)uncompressedLength);
	if ((!uncompressedBytes))
	{
		log.error("Could not allocate memory for decompression");
		return nullptr;
	}

	compressStatus = mz_uncompress(uncompressedBytes, &uncompressedLength, zippedBytes->data(), zippedBytes->size());
	//total_succeeded += (compressStatus == Z_OK);
	int retries = 0;
	while(compressStatus == Z_BUF_ERROR && retries < 4)
	{
		retries++;
		//free(uncompressedBytes);
		delete[] uncompressedBytes;
		uncompressedLength *= 2;
		//uncompressedBytes = (mz_uint8 *)malloc((size_t)uncompressedLength);
		uncompressedBytes = new u8[uncompressedLength];
		compressStatus = mz_uncompress(uncompressedBytes, &uncompressedLength, zippedBytes->data(), zippedBytes->size());
	}

	

	if (compressStatus != Z_OK)
	{
		log.error("Uncompress failed.");
		delete zippedBytes;
		delete[] uncompressedBytes;
		//free(uncompressedBytes);
		returnLength = 0;
		return nullptr;
	}

	delete zippedBytes;

	//log.debug("Decompressed " + to_string(zippedLength) + " bytes into " + to_string(uncompressedLength) + " bytes");
	//printf("Decompressed from %u to %u bytes\n", (mz_uint32)size, (mz_uint32)uncomp_len);

//		// Ensure uncompress() returned the expected data.
//		if (uncomp_len != src_len)
//		{
//			printf("Decompression failed!\n");
//			free(pUncomp);
//			return nullptr;
//		}
	
	returnLength = uncompressedLength;
	return uncompressedBytes;



}

//
//string FileUtils::lzoStringToBase64String(const string& s)
//{ // ===============================================================================================
//
//	if (s == "" || s.length() == 0)
//	{
//	    return s;
//	}
//
//	u8 *val = new u8[s.length() + 1];
//	strcpy((char *)val, s.c_str());
//
//	return lzoByteArrayToBase64String(val, s.length());
//}
//
//string FileUtils::unlzoBase64StringToString(const string& s)
//{ // ===============================================================================================
//
//	if (s == "" || s.length() == 0)
//	{
//	    return s;
//	}
//
//	unsigned long returnLength = 0;
//	u8* bytes = unlzoBase64StringToByteArray(s, returnLength);
//	string out((char*)bytes,returnLength);
//
//	delete[] bytes;
//
//	return out;
//}

string FileUtils::lz4StringToBase64String(const string& s)
{ // ===============================================================================================

	if (s == "" || s.length() == 0)
	{
	    return s;
	}

	u8 *val = new u8[s.length() + 1];
	strcpy((char *)val, s.c_str());

	return lz4ByteArrayToBase64String(val, s.length());
}

string FileUtils::unlz4Base64StringToString(const string& s)
{ // ===============================================================================================

	if (s == "" || s.length() == 0)
	{
	    return s;
	}

	unsigned long returnLength = 0;
	u8* bytes = unlz4Base64StringToByteArray(s, returnLength);
	string out((char*)bytes,returnLength);

	delete[] bytes;

	return out;
}

string FileUtils::zipStringToBase64String(const string& s)
{ // ===============================================================================================

	if (s == "" || s.length() == 0)
	{
	    return s;
	}

	u8 *val = new u8[s.length() + 1];
	strcpy((char *)val, s.c_str());

	return zipByteArrayToBase64String(val, s.length());
}

string FileUtils::unzipBase64StringToString(const string& s)
{ // ===============================================================================================

	if (s == "" || s.length() == 0)
	{
	    return s;
	}

	unsigned long returnLength = 0;
	u8* bytes = unzipBase64StringToByteArray(s, returnLength);
	string out((char*)bytes,returnLength);

	delete[] bytes;

	return out;
}

#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
using Poco::MD5Engine;



string FileUtils::getFileMD5Checksum(const string& filename)
{ //===============================================================================================

	ByteArray* bytes = loadByteFileFromExePath(filename);
	string md5 = getByteArrayMD5Checksum(bytes);
	delete bytes;
	return md5;

}

#include "md5.h"

string FileUtils::getByteArrayMD5Checksum(ByteArray* bytes)
{ //===============================================================================================

	return md5(bytes->data(), bytes->size());

	//std::stringstream stringStream((char*)bytes);
	//return getStringMD5(stringStream.str());

}

string FileUtils::getStringMD5(const string& stringToMD5)
{ //===============================================================================================

	return md5(stringToMD5);

//	Poco::MD5Engine md5;
//	Poco::DigestOutputStream outstr(md5);
//	outstr << stringToMD5;
//	outstr.flush(); //to pass everything to the digest engine
//	const Poco::DigestEngine::Digest& digest = md5.digest();
//	std::string md5string = Poco::DigestEngine::digestToHex(digest);
//	return md5string;
}

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <lib/stb_image.h>
#include <lib/stb_image_write.h>
//TODO: 
void FileUtils::saveImage(const string& s, BufferedImage* i)
{ //===============================================================================================

	//		Iterator<ImageWriter> imageWritersIterator = ImageIO.getImageWritersByFormatName("png");
	//		ImageWriter imageWriter = (ImageWriter) imageWritersIterator.next();
	//
	//		FileOutputStream fileOutputStream = null;
	//		File file = null;
	//		MemoryCacheImageOutputStream memoryCacheImageOutputStream = null;
	//
	//		try
	//		{
	//			file = new File(s);
	//			fileOutputStream = new FileOutputStream(file);
	//			memoryCacheImageOutputStream = new MemoryCacheImageOutputStream(fileOutputStream);
	//		}
	//		catch(FileNotFoundException e){log.error("Could not create PNG file. Error: "+e.getMessage());e.printStackTrace();return;}
	//
	//		imageWriter.setOutput(memoryCacheImageOutputStream);
	//		ImageWriteParam iwp = imageWriter.getDefaultWriteParam();
	//		try
	//		{
	//			imageWriter.write(null, new IIOImage(bufferedImage, null, null), iwp);//param);
	//		}
	//		catch(IOException e){log.error("An error occured during writing PNG file. Error: "+e.getMessage());e.printStackTrace();return;}
	//
	//		imageWriter.dispose();
	//
	//		try
	//		{
	//			memoryCacheImageOutputStream.close();
	//			fileOutputStream.close();
	//		}
	//		catch(IOException e){e.printStackTrace();}

	//-------------------
	//alt
	//-------------------

	//   try
	//   {
	//      ImageIO::write(bufferedImage, "PNG", new File(s));
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//   }



	stbi_write_png(s.c_str(), i->getWidth(), i->getHeight(), 4, i->getData(), i->getWidth() *4);







}




void FileUtils::writeSessionTokenToCache(long long userID, const string& sessionToken, bool statsAllowed)
{ //===============================================================================================

//	File* sessionFile = new File(cacheDir + "session.txt");
//	
//	if (sessionFile->exists() == false)
//	{
//	    sessionFile->createFile();
//	}
//	
//	try
//	{
//		sessionFile->write("" + to_string(userID) + ",`" + sessionToken + "`," + StringConverterHelper::toString(statsAllowed));
//		sessionFile->closeFile();
//	}
//	catch (exception)
//	{
//	    
//	}

	ofstream outputFile;
	outputFile.open(appDataPath + "session.txt", ofstream::out);//leave this without runpath, will always be run in windows debug in the proper cwd /bobsgame/
	outputFile << "" + to_string(userID) + ",`" + sessionToken + "`," + StringConverterHelper::toString(statsAllowed);
	outputFile.close();
}

string FileUtils::readSessionTokenFromCache()
{ //===============================================================================================

//	File* sessionFile = new File(cacheDir + "session.txt");
//	
//	if (sessionFile->exists() == false)
//	{
//	    return "";
//	}
//	
//	string line = "";
//	
//	try
//	{
//	    BufferedReader* input = new BufferedReader(new FileReader(sessionFile));
//	    line = input->readLine();
//	    input->close();
//	}
//	catch (IOException e)
//	{
//	    e->printStackTrace();
//	}
//	
//	if (line != "")
//	{
//	    //log.debug(line);
//	
//	    if (line.length() > 0)
//	    {
//	        return line;
//	    }
//	}

	File f(appDataPath + "session.txt");
	if (f.exists())
	{
		ifstream t(appDataPath + "session.txt");
		string str;

		t.seekg(0, ios::end);
		str.reserve((size_t)t.tellg());
		t.seekg(0, ios::beg);

		str.assign((istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>());

		rtrim(str);

		return str;
	}
	return "";
}

void FileUtils::deleteSessionTokenFromCache()
{ //===============================================================================================

	File* sessionFile = new File(appDataPath + "session.txt");
	if(sessionFile->exists())sessionFile->remove();

}

void FileUtils::setStatusText(const string& text)
{ //===============================================================================================

	   if (statusConsoleText == nullptr)
	   {
	      statusConsoleText = Console::add("", -1, GLUtils::getViewportWidth() / 2 - 50, GLUtils::getViewportHeight() / 2 - 10);
	   }
	
	   statusConsoleText->x = (int)(GLUtils::getViewportWidth() / 2 - ((statusConsoleText->getWidth() + 3) / 2));
	   statusConsoleText->y = (int)(GLUtils::getViewportHeight() / 2 - 10);
	
	   statusConsoleText->text = text;
	
	   glClear(GL_COLOR_BUFFER_BIT);
	
	   Main::mainObject->console->render();
	   Main::mainObject->whilefix();
}

void FileUtils::deleteStatusText()
{ //===============================================================================================

	   if (statusConsoleText != nullptr)
	   {
	      statusConsoleText->text = "";
	      statusConsoleText->x = GLUtils::getViewportWidth();
	      statusConsoleText->y = GLUtils::getViewportHeight();
	
	      statusConsoleText->ticks = 1; //will be deleted from the console after 1 tick
	
	      //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	      delete statusConsoleText;
	
	      glClear(GL_COLOR_BUFFER_BIT);
		  Main::mainObject->console->render();
		  Main::mainObject->whilefix();
	   }
}


//private:
//   class ProgressListener : public ActionListener
//   {
//   private:
//      FileUtils* outerInstance;
//
//   public:
//      ProgressListener(FileUtils* outerInstance);
//
//      void actionPerformed(ActionEvent* e) override;
//   };
//
//
//public:
//   class DownloadCountingOutputStream : public CountingOutputStream
//   {
//   private:
//      FileUtils* outerInstance;
//
//      ActionListener* listener = nullptr;
//   public:
//      DownloadCountingOutputStream(FileUtils* outerInstance, OutputStream* out);
//      void setListener(ActionListener* listener);
//
//   protected:
//      void afterWrite(int n) throw(IOException) override;
//   };

//
//FileUtils::ProgressListener::ProgressListener(FileUtils* outerInstance) : outerInstance(outerInstance)
//{
//}
//
//void FileUtils::ProgressListener::actionPerformed(ActionEvent* e)
//{
//   // e.getSource() gives you the object of DownloadCountingOutputStream because you set it in the overriden method, afterWrite().
//   outerInstance->setStatusText("Downloading " + outerInstance->downloadingDataNiceName + ": " + (static_cast<DownloadCountingOutputStream*>(e->getSource()))->getByteCount() / 1024 + " kB / " + outerInstance->downloadingFileSize / 1024 + " kB");
//}
//
//FileUtils::DownloadCountingOutputStream::DownloadCountingOutputStream(FileUtils* outerInstance, OutputStream* out) : org::apache::commons::io::output::CountingOutputStream(out), outerInstance(outerInstance)
//{
//}
//
//void FileUtils::DownloadCountingOutputStream::setListener(ActionListener* listener)
//{
//   this->listener = listener;
//}
//
//void FileUtils::DownloadCountingOutputStream::afterWrite(int n) throw(IOException)
//{
////   CountingOutputStream::afterWrite(n);
////   if (listener != nullptr)
////   {
////      listener->actionPerformed(new ActionEvent(this, 0, nullptr));
////   }
//}

void FileUtils::downloadFileToCacheWithProgressListener(const string& fileName, const string& niceName)
{ //===============================================================================================
	//
	//   downloadingDataNiceName = niceName;
	//
	//   File* outputFile = new File(cacheDir + getFileName);
	//   //download sprites.zip and maps.zip from http://localhost/z/ and save to directory
	//
	//   URL* fileURL = nullptr;
	//
	//   try
	//   {
	//      fileURL = new URL(bigDataURL + getFileName);
	//   }
	//   catch (MalformedURLException e1)
	//   {
	//      e1->printStackTrace();
	//   }
	//
	//   //		try
	//   //		{
	//   //			org.apache.commons.io.FileUtils::copyURLToFile(fileURL, file, 60000, 60000);
	//   //		}
	//   //		catch (IOException e1)
	//   //		{
	//   //			e1.printStackTrace();
	//   //		}
	//
	//
	//   OutputStream* os = nullptr;
	//   InputStream* is = nullptr;
	//   ProgressListener* progressListener = new ProgressListener(this);
	//
	//
	//   try
	//   {
	//      os = new FileOutputStream(outputFile);
	//      is = fileURL->openStream();
	//
	//      DownloadCountingOutputStream* dcount = new DownloadCountingOutputStream(this, os);
	//
	//      dcount->setListener(progressListener);
	//
	//      // this line give you the total length of source stream as a String.
	//      // you may want to convert to integer and store this value to
	//      // calculate percentage of the progression.
	//
	//      //setStatusText("Connecting to asset server...");
	//
	//
	//      string fileSizeString = fileURL->openConnection().getHeaderField("Content-Length");
	//
	//      if (fileSizeString != "")
	//      {
	//         downloadingFileSize = -1;
	//         try
	//         {
	//            downloadingFileSize = StringConverterHelper::fromString<long long>(fileSizeString);
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//            return;
	//         }
	//      }
	//
	//      // begin transfer by writing to dcount, not os.
	//      IOUtils::copy(is, dcount);
	//   }
	//   catch (exception& e)
	//   {
	//      log.error("Error downloading file to cache! File: " + getFileName + " Error: " + e.what());
	//      e.printStackTrace();
	//   }
	//   
	//   finally
	//      {
	//
	//         try
	//         {
	//            if (os != nullptr)
	//            {
	//               os->close();
	//            }
	//            if (is != nullptr)
	//            {
	//               is->close();
	//            }
	//         }
	//         catch (IOException e)
	//         {
	//            e->printStackTrace();
	//         }
	//
	//      }
	//
	//   //deleteStatusText();
}

void FileUtils::decompressZipInCache(const string& fileName, const string& niceName)
{ //===============================================================================================
	//
	//   setStatusText("Decompressing " + niceName + "...");
	//
	//   try
	//   {
	//      File* inputFile = new File(cacheDir + getFileName);
	//
	//      ZipInputStream* zipInputStream = new ZipInputStream(new FileInputStream(inputFile));
	//      BufferedInputStream* bufferedInputStream = new BufferedInputStream(zipInputStream);
	//
	//      ZipEntry* zipEntry = zipInputStream->getNextEntry();
	//
	//      while (zipEntry != nullptr)
	//      {
	//         BufferedOutputStream* bufferedOutputStream = new BufferedOutputStream(new FileOutputStream(new File(cacheDir + zipEntry->getName())));
	//
	//         //int zipSize = (int)zipEntry.getCompressedSize();
	//
	//         int bytesRead = 0;
	//
	//         u8* b(1024);
	//
	//         while ((bytesRead = bufferedInputStream->read(b)) != -1)
	//         {
	//            bufferedOutputStream->write(b, 0, bytesRead);
	//         }
	//         bufferedOutputStream->close();
	//
	//
	//         zipEntry = zipInputStream->getNextEntry();
	//      }
	//
	//      bufferedInputStream->close();
	//      zipInputStream->close();
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//      return;
	//   }
	//
	//   deleteStatusText();
}

void FileUtils::deleteFileFromCache(const string& fileName)
{ //===============================================================================================

	//   File* file = new File(cacheDir + getFileName);
	//
	//   if (file->exists() == true)
	//   {
	//      file->
	//      delete(
	//      )
	//      ;
	//   }
}

bool FileUtils::checkIfFileExistsInCache(const string& fileName)
{ //===============================================================================================

	//   File* file = new File(cacheDir + getFileName);
	//
	//   return file->exists();

	return true;
}

long long FileUtils::getFileSizeInCache(const string& fileName)
{ //===============================================================================================

	//   if (checkIfFileExistsInCache(getFileName) == true)
	//   {
	//      return FileUtils::sizeOf(new File(cacheDir + getFileName));
	//   }
	//   else
	//   {
	return -1;
	//   }
}

long long FileUtils::getFileSizeOnServer(const string& fileName)
{ //===============================================================================================

	//   URL* fileURL = nullptr;
	//
	//   try
	//   {
	//      fileURL = new URL(bigDataURL + getFileName);
	//   }
	//   catch (MalformedURLException e1)
	//   {
	//      e1->printStackTrace();
	//   }
	//
	//
	//   string fileSizeString = "";
	//
	//
	//   //setStatusText("Connecting to asset server...");
	//
	//
	//   try
	//   {
	//      fileSizeString = fileURL->openConnection().getHeaderField("Content-Length");
	//   }
	//   catch (exception& ex)
	//   {
	//      //setStatusText("Timed out, retrying...");
	//   }
	//
	//
	//   if (fileSizeString != "")
	//   {
	//      long long size = -1;
	//      try
	//      {
	//         size = StringConverterHelper::fromString<long long>(fileSizeString);
	//      }
	//      catch (NumberFormatException ex)
	//      {
	//         ex->printStackTrace();
	//         return -1;
	//      }
	//      return size;
	//   }
	//
	//   //deleteStatusText();

	return -1;
}

void FileUtils::downloadAndDecompressZIPFileIfDifferentFromServer(const string& fileName, const string& niceName)
{ //===============================================================================================

	//   long long serverSize = getFileSizeOnServer(getFileName);
	//   long long localSize = getFileSizeInCache(getFileName);
	//
	//   log.debug("" + getFileName + " size on server: " + to_string(serverSize));
	//   log.debug("" + getFileName + " size in cache: " + to_string(localSize));
	//
	//   if (localSize != serverSize && serverSize > 16)
	//   {
	//      deleteFileFromCache(getFileName);
	//      downloadFileToCacheWithProgressListener(getFileName, niceName);
	//      decompressZipInCache(getFileName, niceName);
	//      deleteStatusText();
	//   }
}

void FileUtils::downloadFileIfDifferentFromServer(const string& fileName, const string& niceName)
{ //===============================================================================================

	//   long long serverSize = getFileSizeOnServer(getFileName);
	//   long long localSize = getFileSizeInCache(getFileName);
	//
	//   log.debug("" + getFileName + " size on server: " + to_string(serverSize));
	//   log.debug("" + getFileName + " size in cache: " + to_string(localSize));
	//
	//   if (localSize != serverSize && serverSize > 16)
	//   {
	//      deleteFileFromCache(getFileName);
	//      downloadFileToCacheWithProgressListener(getFileName, niceName);
	//      //decompressZipInCache(getFileName,niceName);
	//      deleteStatusText();
	//   }
}

void FileUtils::initCache()
{ //===============================================================================================

	   //log.info("Init FileUtils...");
	
	   FileUtils::makeDir(cacheDir);

	   FileUtils::makeDir(cacheDir + "l/");
	
	   //File initFile = new File(cacheDir+"init");
	   //if(initFile.exists()==false)
	   //{
			// check filesize of sprites.zip locally
			// check filesize of sprites.zip on server
			//if different, delete sprites.zip locally, download sprites.zip, decompress.
	
	   //log.info("Initializing cache data...");
	   downloadAndDecompressZIPFileIfDifferentFromServer("sprites.zip", "Sprite Graphics");
	   downloadAndDecompressZIPFileIfDifferentFromServer("maps.zip", "Background Graphics");
	   downloadAndDecompressZIPFileIfDifferentFromServer("sounds.zip", "Sound Effects");
	   downloadAndDecompressZIPFileIfDifferentFromServer("music.zip", "Initial Music Data");
	   //downloadFileIfDifferentFromServer("gameData", "Initial Game Data"); //old bobs game puzzle assets
	
	   deleteStatusText();

	   //FileUtils::listFiles(new File(cacheDir),null,true);
	
	
	   //delete("sprites.zip");
	   //delete("maps.zip");
	
	   //			try
	   //			{
	   //				initFile.createNewFile();
	   //			}
	   //			catch (IOException e1)
	   //			{
	   //				e1.printStackTrace();
	   //			}
	   //}
	
	   // log.info("FileUtils Complete.");
}

void FileUtils::downloadBigFileToCacheIfNotExist(const string& fileName)
{ //===============================================================================================

	//
	//   if (FileUtils::getResource("" + FileUtils::cacheDir + getFileName) == nullptr)
	//   {
	//      File* outputFile = new File(cacheDir + getFileName);
	//
	//      URL* fileURL = nullptr;
	//
	//      try
	//      {
	//         fileURL = new URL(bigDataURL + getFileName);
	//      }
	//      catch (MalformedURLException e1)
	//      {
	//         e1->printStackTrace();
	//      }
	//
	//
	//      OutputStream* os = nullptr;
	//      InputStream* is = nullptr;
	//
	//      try
	//      {
	//         os = new FileOutputStream(outputFile);
	//         is = fileURL->openStream();
	//
	//         // this line give you the total length of source stream as a String.
	//         // you may want to convert to integer and store this value to
	//         // calculate percentage of the progression.
	//         string fileSizeString = fileURL->openConnection().getHeaderField("Content-Length");
	//
	//
	//         // begin transfer by writing to dcount, not os.
	//         IOUtils::copy(is, os);
	//      }
	//      catch (exception& e)
	//      {
	//         log.error("Error downloading file to cache! File: " + getFileName + " Error: " + e.what());
	//         e.printStackTrace();
	//      }
	//      
	//      finally
	//         {
	//
	//            try
	//            {
	//               if (os != nullptr)
	//               {
	//                  os->close();
	//               }
	//               if (is != nullptr)
	//               {
	//                  is->close();
	//               }
	//            }
	//            catch (IOException e)
	//            {
	//               e->printStackTrace();
	//            }
	//
	//         }
	//   }
}

#undef INADDR_ANY       
#undef INADDR_LOOPBACK  
#undef INADDR_BROADCAST 
#undef INADDR_NONE      
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPCredentials.h"
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;

#include "Poco/FileStream.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/FTPStreamFactory.h"
#include <memory>
#include <iostream>
using Poco::FileStream;
using Poco::URIStreamOpener;
using Poco::Net::HTTPStreamFactory;
using Poco::Net::FTPStreamFactory;

void FileUtils::downloadSmallFileToCacheIfNotExist(const string& fileName)
{ //===============================================================================================

	//   if (FileUtils::getResource("" + FileUtils::cacheDir + getFileName) == nullptr)
	//   {
	//      URL* fileURL = nullptr;
	//
	//      try
	//      {
	//         fileURL = new URL(smallDataURL + getFileName);
	//      }
	//      catch (MalformedURLException e1)
	//      {
	//         e1->printStackTrace();
	//      }
	//
	//      try
	//      {
	//         FileUtils::copyURLToFile(fileURL, new File("" + FileUtils::cacheDir + getFileName), 60000, 60000);
	//      }
	//      catch (IOException e1)
	//      {
	//         e1->printStackTrace();
	//      }
	//   }

	File f = File(cacheDir + fileName);
	if (f.exists() == false)
	{

		try
		{

			HTTPStreamFactory::registerFactory();

			URI zipuri(smallDataURL+fileName);

			HTTPClientSession session(zipuri.getHost(), zipuri.getPort());
			string path(zipuri.getPathAndQuery());
			HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
			HTTPResponse response;
			session.setTimeout(Poco::Timespan(20, 0));
			session.sendRequest(request);
			//std::istream& rs =
			session.receiveResponse(response);
			//int contentlen = (int)response.getContentLength();

			FileStream fs(cacheDir + fileName, ios::out | ios::trunc | ios::binary);
			std::auto_ptr<std::istream> pStr(URIStreamOpener::defaultOpener().open(zipuri));
			StreamCopier::copyStream(*pStr.get(), fs);
			fs.close();
		}
		catch (Exception)
		{
			//std::cerr << exc.displayText() << std::endl;
			log.error("Could not download " + fileName);

			return;
		}
	}

}

ByteArray* FileUtils::loadByteFileFromCacheOrDownloadIfNotExist(const string& fileName)
{ //===============================================================================================

	downloadSmallFileToCacheIfNotExist(fileName);
	return loadByteFile(cacheDir + fileName);
}

IntArray* FileUtils::loadIntFileFromCacheOrDownloadIfNotExist(const string& fileName)
{ //===============================================================================================

	downloadSmallFileToCacheIfNotExist(fileName);
	return loadIntFile(cacheDir + fileName);
}

void FileUtils::saveByteArrayToCache(ByteArray* byteArray, const string& md5FileName)
{ //===============================================================================================
	
	
	writeByteArrayToFile(byteArray, cacheDir + md5FileName);

}

void FileUtils::writeByteArrayToFile(ByteArray* byteArray, const string& fileName)
{ //===============================================================================================

	std::ofstream file(fileName, std::ios::binary);
	if (file)
	{
		file.write((char*)byteArray->data(), byteArray->size());
	}


//	r - open for reading
//		w - open for writing(file need not exist)
//		a - open for appending(file need not exist)
//		r + -open for reading and writing, start at beginning
//		w + -open for reading and writing(overwrite file)
//		a + -open for reading and writing(append if file exists)
//	FILE *f = fopen("out.txt", "w");
//	if (f == NULL)
//	{
//		fprintf(stderr, "Error opening file!\n");
//		exit(EXIT_FAILURE);
//	}

//	for (int i = 0; i < len; i++)
//	{
//		fprintf(f, "%u", buffer[i]);
//	}
	//OR
//  fwrite(x, sizeof(x[0]), sizeof(x) / sizeof(x[0]), fp);
	//size_t fwrite(const void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);
	//int fputc( int c, FILE *fp );
//	fclose(f);


//	Poco::FileOutputStream fos(file, std::ios::binary);
//	fos << "sometestdata";
//	fos.close();

}

bool FileUtils::doesDidIntroFileExist()
{ //===============================================================================================
	//   File* introCheckFile = new File(FileUtils::cacheDir + ".didIntro");
	//   if (introCheckFile->exists())
	//   {
	//      return true;
	//   }
	return false;
}

void FileUtils::writeDidIntroFile()
{ //===============================================================================================
	//   File* introCheckFile = new File(FileUtils::cacheDir + ".didIntro");
	//   try
	//   {
	//      introCheckFile->createNewFile();
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//   }
}



BobFile::BobFile()
{
}

BobFile::BobFile(const string& s)
{
	path = s;
}

bool BobFile::exists()
{
	File f(path);
	return f.exists();

}

bool BobFile::exists(const string& s)
{
	File f(s);
	return f.exists();

}

int BobFile::length()
{
	File f(path);
	if (f.exists())
	{
		return f.getSize();
	}
	return 0;
}

//includes filename, so just path???

string& BobFile::getAbsolutePath()
{
//	string fullPath = string(path);
//	string absPath;
//	int found = (int)fullPath.find('/');
//	while (found != string::npos)
//	{
//		absPath += fullPath.substr(0,found + 1);
//		fullPath = fullPath.substr(found + 1, fullPath.length());
//		found = (int)fullPath.find('/');
//	}
//	return absPath;

	return path;
}

void BobFile::createNewFile()
{
	File f(path);
	if (f.exists()==false)
	{
		f.createFile();
	}
}

string BobFile::getName()
{
	string name = string(path);
	int found = (int)name.find('/');
	while (found != string::npos)
	{
		name = name.substr(found + 1, name.length());
		found = (int)name.find('/');
	}
	return name;

}

void BobFile::deleteFile()
{
	File f(path);
	if (f.exists())
	{
		f.remove();
	}

}




/*

Constructor

std::vector<MyType> myVec(numberOfElementsToStart);
int size = myVec.size();
int capacity = myVec.capacity();

In this first case, using the constructor, size and numberOfElementsToStart will be equal and capacity will be greater than or equal to them.

Think of myVec as a vector containing a number of items of MyType which can be accessed and modified, push_back(anotherInstanceOfMyType) will append it the the end of the vector.



Reserve

std::vector<MyType> myVec;
myVec.reserve(numberOfElementsToStart);
int size = myVec.size();
int capacity = myVec.capacity();

When using the reserve function, size will be 0 until you add an element to the array and capacity and numberOfElementsToStart will be equal.

Think of myVec as an empty vector which can have new items appended to it using push_back with no overhead for the first numberOfElementsToStart elements.

*/







