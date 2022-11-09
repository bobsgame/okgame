#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger FriendManager::log = Logger("FriendManager");


FriendManager::FriendManager(sp<BGClientEngine> g)
{ //===============================================================================================
	this->e = g;
}

void FriendManager::init()
{ //===============================================================================================

	//if (OKNet::debugMode)
	{
		//int timesRun = 0;


		//get file with times run

		//get times run

		//write back with timesrun+1
		//
		//      sp<File> sessionFile = ms<File>("C:\\simulator.txt");
		//
		//      if (sessionFile->exists() == false)
		//      {
		//         try
		//         {
		//            sessionFile->createNewFile();
		//         }
		//         catch (IOException e1)
		//         {
		//            e1->printStackTrace();
		//         }
		//      }
		//
		//
		//      string line = "";
		//
		//      try
		//      {
		//         sp<BufferedReader> input = ms<BufferedReader>(ms<FileReader>(sessionFile));
		//         line = input->readLine();
		//         input->close();
		//      }
		//      catch (IOException e)
		//      {
		//         e->printStackTrace();
		//      }
		//
		//      if (line != "")
		//      {
		//         if (line.length() > 0)
		//         {
		//            timesRun = stoi(line);
		//            log->debug("" + to_string(timesRun));
		//         }
		//      }
		//
		//
		//      sp<Writer> output;
		//      try
		//      {
		//         output = ms<BufferedWriter>(ms<FileWriter>(sessionFile));
		//         output->write("" + to_string(timesRun + 1));
		//         output->close();
		//      }
		//      catch (IOException e)
		//      {
		//         e->printStackTrace();
		//      }
		//
		//
		//      int myPort = 1111;
		//      int theirPort = 1112;
		//
		//      if (timesRun % 2 == 0)
		//      {
		//         theirPort = 1111;
		//         myPort = 1112;
		//      }
		//
		//
		//      sp<FriendCharacter> f = ms<FriendCharacter>(getGameEngine(), 1, FriendCharacter::FACEBOOK_TYPE, myPort, theirPort);
		//
		//
		//      friendCharacters.push_back(f);
	}
}

void FriendManager::cleanup()
{ //===============================================================================================

	for (int i = 0; i < friendCharacters.size(); i++)
	{
		friendCharacters.get(i)->cleanup();
	}
}

void FriendManager::update()
{ //===============================================================================================

	for (int i = 0; i < friendCharacters.size(); i++)
	{
		friendCharacters.get(i)->update();
	}

}


////The following method was originally marked 'synchronized':
//void FriendManager::addNewOnlineFriendIfNotExist(int userID, int peerType)
//{ //===============================================================================================
//	for (int i = 0; i < friendCharacters->size(); i++)
//	{
//		if (friendCharacters->get(i)->userID == userID)
//		{
//			return;
//		}
//	}
//
//
//	friendCharacters->add(ms<FriendCharacter>(getClientGameEngine(), userID, peerType));
//}

