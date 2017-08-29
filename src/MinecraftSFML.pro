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
    engine/opengl/box3d.cpp \
    engine/opengl/openglentity.cpp \
    engine/opengl/triangle2d.cpp \
    entities/blockentity.cpp \
    entities/blocksideentity.cpp \
    entities/chunkentity.cpp \
    entities/mapentity.cpp \
    engine/controller/renderer.cpp \
    engine/opengl/plane2d.cpp \
    tests.cpp \
    engine/opengl/glutils.cpp \
    engine/opengl/opengltexture.cpp \
    engine/opengl/scene.cpp \
    engine/controller/renderersdl.cpp \
    engine/opengl/camera.cpp \
    timer.cpp

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
    engine/opengl/box3d.h \
    engine/opengl/openglentity.h \
    engine/opengl/triangle2d.h \
    entities/blockentity.h \
    entities/blocksideentity.h \
    entities/chunkentity.h \
    entities/mapentity.h \
    engine/controller/renderer.h \
    engine/opengl/plane2d.h \
    tests.h \
    engine/opengl/glutils.h \
    engine/opengl/opengltexture.h \
    engine/opengl/scene.h \
    engine/controller/renderersdl.h \
    opengl.h \
    engine/opengl/camera.h \
    timer.h

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
    shaders/Light.fsh
