# Interactive Game
PC game interactively controlled via smartphone

Bachelor final thesis (FIT CVUT)

# Installation prerequisites

For proper installation the following packages must be installed:
- Android SDK, Android NDK
- Android Debug Bridge
- Cocos2d-x engine

# Controller Android installation (linux, OS X)


Debug:

Run source/controller/InteractiveController/install_and_run_everywhere.sh in terminal. The Controller application
will be installed on each device connected to ADB.

Release

Run the following command in the source/controller/InteractiveController/:

cocos compile -p android -m release

The release .apk file will be in bin/ folder.

# Controller iOS installation (linux, OS X)

Debug:

Open project InteractiveController in Xcode and run the target "InteractiveController-mobile"

Release:

Run the following command in the source/controller/InteractiveController/:

cocos compile -p ios -m release

The release application file will be in bin/ folder.

# Game installation (OS X)

Debug:

Open project InteractiveGame in Xcode and run the target "InteractiveGame-desktop"

Release:

Run the following command in the source/controller/InteractiveGame/:

cocos compile -p mac -m release

The release application file will be in bin/ folder.
