# compile -> .apk
cocos compile -p android;

# install to each connected device
adb devices | tail -n +2 | cut -sf 1 | xargs -I {} adb -s {} install -r bin/debug/android/InteractiveController-debug.apk;

# run on each connected device
adb devices | tail -n +2 | cut -sf 1 | xargs -I {} adb -s {} shell am start -n "foltyma1.interactivecontroller/org.cocos2dx.cpp.AppActivity"