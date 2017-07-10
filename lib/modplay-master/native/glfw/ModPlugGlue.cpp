#include "modplug.h"
#include "sndfile.h"

class ModPlugGlue : public Object {
public:
	
	ModPlugGlue();
	
	~ModPlugGlue();
	
    void Init(int rate);
    
private:

    ModPlugFile *mp_file;
    ModPlug_Settings mp_settings;

}