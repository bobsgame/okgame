import com.sygem.monkey.modplay.ModPlugGlue;

class ModPlugMonkeyGlue extends ActivityDelegate {

    private ModPlugGlue nativeGlue = new ModPlugGlue();
    private boolean debug = false;

    public void Init(int rate) {
        BBAndroidGame.AndroidGame().AddActivityDelegate(this);
        nativeGlue.Init(rate);
    }
    public void Play(NativeModFile file) {
        if (debug) Log.i("ModPlay","Pausing playback");
        nativeGlue.Pause();
        if (debug) Log.i("ModPlay","Loading Mod Data into ModPlug: "+file.GetData().length);
        nativeGlue.LoadMODData(file.GetData());
        if (debug) Log.i("ModPlay","Starting playback");
        nativeGlue.Play();
        nativeGlue.Unpause();
    }
    public void Stop() {
        nativeGlue.Stop();
    }
    public void Pause() {
        nativeGlue.Pause();
    }
    public void Unpause() {
        nativeGlue.Unpause();
    }
    public void SetVolume(float volume) {
        nativeGlue.SetVolume(volume);
    }
    public void SetLoopCount(int loopCount) {
        nativeGlue.SetLoopCount(loopCount);
    }
    public void SetDebug(boolean debug) {
        this.debug = debug;
    }

    //***********************************************************
    // ActivityDelegate Methods
    //***********************************************************
    
    public void onPause() {
        nativeGlue.onPause();
   }
    
    public void onResume() {
        nativeGlue.onResume();
    }
}