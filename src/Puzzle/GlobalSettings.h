
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

	bool useAnalogSticks = true;

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

		if(version>3)
		{
			ar & BOOST_SERIALIZATION_NVP(useAnalogSticks);
		}
	}

};
BOOST_CLASS_VERSION(GlobalSettings, 4)
BOOST_CLASS_TRACKING(GlobalSettings, boost::serialization::track_never)