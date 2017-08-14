
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"


//=========================================================================================================================
class GlobalSettings
{//=========================================================================================================================
public:
	int musicVolume = 50;

	float hue = 1.0f;
	float saturation = 1.2f;
	float brightness = 1.0f;
	float contrast = 1.2f;
	float gamma = 1.0f;
	bool useXInput = true;
	

	float bobsGame_screenFlashOnLevelUpAlpha = 0.3f;
	bool bobsGame_showDetailedGameInfoCaptions = true;
	bool bobsGame_showScoreBarsInSinglePlayer = true;

	bool useAnalogSticks = true;
	bool censorBadWords = true;
	bool hideChat = false;
	bool hideNotifications = false;

	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(musicVolume);

		if (version>0)
		{
			ar & BOOST_SERIALIZATION_NVP(hue);
			ar & BOOST_SERIALIZATION_NVP(saturation);
			ar & BOOST_SERIALIZATION_NVP(brightness);
			ar & BOOST_SERIALIZATION_NVP(contrast);
			ar & BOOST_SERIALIZATION_NVP(gamma);
		}
		if(version>1)
		{
			ar & BOOST_SERIALIZATION_NVP(useXInput);
		}
		if(version<3)
		{
			hue = 1.0f;
		}
		if(version>2)
		{
			ar & BOOST_SERIALIZATION_NVP(bobsGame_screenFlashOnLevelUpAlpha);
			ar & BOOST_SERIALIZATION_NVP(bobsGame_showDetailedGameInfoCaptions);
		}

		if(version>4)
		{
			ar & BOOST_SERIALIZATION_NVP(bobsGame_showScoreBarsInSinglePlayer);
		}

		if(version>3)
		{
			ar & BOOST_SERIALIZATION_NVP(useAnalogSticks);
		}
		if(version>5)
		{
			ar & BOOST_SERIALIZATION_NVP(hideChat);
		}
		if(version>6)
		{
			ar & BOOST_SERIALIZATION_NVP(hideNotifications);
		}
	}

};
BOOST_CLASS_VERSION(GlobalSettings, 7)
BOOST_CLASS_TRACKING(GlobalSettings, boost::serialization::track_never)