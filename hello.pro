SOURCES += SDLLearningForHenry/solarSimulationWindow.cpp 
QT += widgets
CONFIG += link_pkgconfig
PKGCONFIG += sdl2
LIBS += -lSDL2_image -lSDL2_ttf -ltiff
