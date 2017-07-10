modplay
=======

MOD music player for [MonkeyX]

Supported Targets
-----------------
- Android
- iOS

Installation Instructions
-------------------------

###Android
- If you are using *modplay* on Android, you will need to copy the **native\android\armeabi\libmodplug.so** file into your compiled project's **libs\armeabi** folder.

###iOS
- Nothing to do ;-)

Usage Example
-------------
```
Local player:= New ModPlayer()
player.SetLoopCount(-1) ' looping is supported, hurrah!

Local file:= New ModFile("mymodfile.mod")
player.Play(file)

Local anotherFile:= New ModFile("another.mod")
player.Play(anotherFile)
```
Version
-------
0.1a

[MonkeyX]:http://http://www.monkey-x.com/
