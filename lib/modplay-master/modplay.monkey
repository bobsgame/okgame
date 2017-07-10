Strict

#BINARY_FILES+="*.mod|*.xm" ' probably lots of others are supported too...

Import modfile

#If TARGET="android"
Import "native/android/ModPlugMonkeyGlue.java"
#LIBS+="${CD}/native/android/modplay.jar"
' Can't copy a lib file to the armeabi directory, so it must be done manually
'#LIBS+="${CD}/native/android/armeabi/libmodplug.so"

#Elseif TARGET="ios"

Import "native/ios/ModPlugMonkeyGlue.cpp"
#LIBS+="${CD}/native/ios/libmodplug.a"
#LIBS+="${CD}/native/ios/modplug.h"

'#Elseif TARGET="glfw" ' Not supported yet...

'Import "native/glfw/ModPlugGlue.cpp"

#End

Extern Private
Class ModPlugMonkeyGlue
    Method Init:Void(rate:Int)
    Method Play:Void(file:ModFile)
    Method Stop:Void()
    Method Pause:Void()
    Method Unpause:Void()
    Method SetVolume:Void(volume:Float)
    Method SetLoopCount:Void(loopCount:Int)
    'Method SetCurrentPattern:Void(pattern:Int) ' maybe, someday...
    'Method ChangePattern:Void(pattern:Int)
    Method SetDebug:Void(debug:Bool)
End

Public
Class ModPlayer Extends ModPlugMonkeyGlue
    
    Const READY:= 0
    Const PLAYING:= 1
    Const PAUSED:= 2
    Const SHUTDOWN:= 3

    Method New(rate:Int = 0)
        Init(rate)
    End

    Method GetState:Int()
        Return state
    End

    Method Play:Void(file:ModFile)
        If state <> SHUTDOWN
            state = PLAYING
            If Not file.IsLoaded()
                file.Load()
            EndIf
            Super.Play(file)
        EndIf
    End
    
    Method Pause:Void()
        If state = PLAYING
            state = PAUSED
            Super.Pause()
        EndIf
    End
    
    Method Unpause:Void()
        If state = PAUSED
            state = PLAYING
            Super.Unpause()
        EndIf
    End
    
    Method Shutdown:Void()
        If state <> SHUTDOWN
            state = SHUTDOWN
            Super.Stop()
        EndIf
    End
        
    Private
    Field state:Int = READY
End