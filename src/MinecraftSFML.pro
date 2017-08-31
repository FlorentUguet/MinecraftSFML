TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    znoise/FBM.cpp \
    znoise/HybridMultiFractal.cpp \
    znoise/MixerBase.cpp \
    znoise/NoiseBase.cpp \
    znoise/NoiseTools.cpp \
    znoise/Perlin.cpp \
    znoise/Simplex.cpp \
    znoise/Worley.cpp \
    engine/entities/box3d.cpp \
    engine/entities/openglentity.cpp \
    engine/entities/triangle2d.cpp \
    entities/blockentity.cpp \
    entities/blocksideentity.cpp \
    entities/chunkentity.cpp \
    entities/mapentity.cpp \
    engine/controller/renderer.cpp \
    engine/entities/plane2d.cpp \
    tests.cpp \
    engine/glutils.cpp \
    engine/textures/opengltexture.cpp \
    engine/scene.cpp \
    engine/controller/renderersdl.cpp \
    engine/entities/camera.cpp \
    timer.cpp \
    engine/entities/jsonentity.cpp \
    jsoncpp/jsoncpp.cpp \
    jsoncpp/jsonutils.cpp \
    engine/textures/opengltextureatlas.cpp \
    engine/entities/openglattribute.cpp

HEADERS += \
    znoise/Enums.hpp \
    znoise/FBM.hpp \
    znoise/HybridMultiFractal.hpp \
    znoise/MixerBase.hpp \
    znoise/NoiseBase.hpp \
    znoise/NoiseTools.hpp \
    znoise/Perlin.hpp \
    znoise/Simplex.hpp \
    znoise/Worley.hpp \
    engine/entities/box3d.h \
    engine/entities/openglentity.h \
    engine/entities/triangle2d.h \
    entities/blockentity.h \
    entities/blocksideentity.h \
    entities/chunkentity.h \
    entities/mapentity.h \
    engine/controller/renderer.h \
    engine/entities/plane2d.h \
    tests.h \
    engine/glutils.h \
    engine/textures/opengltexture.h \
    engine/scene.h \
    engine/controller/renderersdl.h \
    opengl.h \
    engine/entities/camera.h \
    timer.h \
    engine/entities/jsonentity.h \
    jsoncpp/json/json.h \
    jsoncpp/json/json-forwards.h \
    jsoncpp/jsonutils.h \
    engine/textures/opengltextureatlas.h \
    engine/entities/openglattribute.h

#Threading Linux
unix: LIBS += -lpthread

#OpenGL
win32: LIBS += -lopengl32 -lglu32
else:unix: LIBS+= -lGL -lGLU

#SDL2 + SDL2_image
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/SDL2-2.0.5/lib/ -lmingw32 -lSDL2main -lSDL  -lSDL2_image
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/SDL2-2.0.5/lib/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
else:unix: LIBS += -lSDL2 -lSDL2main -lSDL2_image
INCLUDEPATH += $$PWD/../lib/SDL2-2.0.5/include
DEPENDPATH += $$PWD/../lib/SDL2-2.0.5/include

#GLEW
win32: LIBS += -L$$PWD/../lib/glew-2.1.0/lib/ -lglew32 -lglew32.dll
else:unix: LIBS+= -lGLEW

INCLUDEPATH += $$PWD/../lib/glew-2.1.0/include
DEPENDPATH += $$PWD/../lib/glew-2.1.0/include

#GLM
INCLUDEPATH += $$PWD/../lib/glm-0.9.8/include

DISTFILES += \
    shaders/SimpleFragmentShader.fsh \
    shaders/SimpleVertexShader.vsh \
    shaders/TextureFSH.fsh \
    shaders/MVPVSH.vsh \
    shaders/Light.fsh \
    ../qt-builds/build-MinecraftSFML-Desktop_Qt_5_9_0_MinGW_32bit-Debug/shaders/MvpInstancing.vsh
