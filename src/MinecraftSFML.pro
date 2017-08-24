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
    engine/controller/renderersdl.cpp

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
    opengl.h

#Threading Linux
unix: LIBS += -lpthread

#OpenGL
win32: LIBS += -lopengl32 -lglu32
else:unix: LIBS+= -lGL -lGLU

/#SFML
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/SFML-2.4.2/lib/  -lsfml-graphics -lsfml-window -lsfml-system
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/SFML-2.4.2/lib/ -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
#else:unix: LIBS += -lsfml-graphics -lsfml-window -lsfml-system
#INCLUDEPATH += $$PWD/../lib/SFML-2.4.2/include
#DEPENDPATH += $$PWD/../lib/SFML-2.4.2/include

#SDL
unix: LIBS += -lSDL2 -lSDL2main -lSDL2_image

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
