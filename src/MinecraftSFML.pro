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
    opengl/box3d.cpp \
    opengl/openglentity.cpp \
    opengl/triangle2d.cpp \
    entities/blockentity.cpp \
    entities/blocksideentity.cpp \
    entities/chunkentity.cpp \
    entities/mapentity.cpp \
    controller/renderer.cpp \
    opengl/plane2d.cpp \
    tests.cpp \
    opengl/glutils.cpp \
    opengl/opengltexture.cpp \
    opengl/scene.cpp

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
    opengl/box3d.h \
    opengl/openglentity.h \
    opengl/triangle2d.h \
    entities/blockentity.h \
    entities/blocksideentity.h \
    entities/chunkentity.h \
    entities/mapentity.h \
    controller/renderer.h \
    opengl/plane2d.h \
    tests.h \
    opengl/glutils.h \
    opengl/opengltexture.h \
    opengl/scene.h

#Threading Linux
unix: LIBS += -lpthread

#OpenGL
win32: LIBS += -lopengl32 -lglu32
else:unix: LIBS+= -lGL -lGLU

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/SFML-2.4.2/lib/  -lsfml-graphics -lsfml-window -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/SFML-2.4.2/lib/ -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
else:unix: LIBS += -lsfml-graphics -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/../lib/SFML-2.4.2/include
DEPENDPATH += $$PWD/../lib/SFML-2.4.2/include

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
