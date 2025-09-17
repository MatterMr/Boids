# THE NAME OF YOUR EXECUTABLE
TARGET = Boids
# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = main.cpp Flock.cpp Boid.cpp

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
	DEL = del
	Q =

	INC_PATH = Z:/CSCI200/include/
	LIB_PATH = Z:/CSCI200/lib/

	ARCH =
	RPATH =
else
	DEL = rm -f
	Q = "

	INC_PATH = /usr/local/include/
	LIB_PATH = /usr/local/lib/

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
		RPATH =
	endif
	ifeq ($(UNAME_S),Darwin)
		TARGET_MAKEFILE = Makefile.osx
		CXXFLAGS += -D OSX
		RPATH = -Wl,-rpath,/Library/Frameworks
	endif

	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARCH =
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		ARCH =
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		ARCH =
	endif
endif

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(ARCH) -o $@ $^ $(RPATH) -L$(LIB_PATH) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(ARCH) $(CXXVERSION) -o $@ -c $< -I$(INC_PATH)

clean:
	$(DEL) $(TARGET) $(OBJECTS)

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

# DEPENDENCIES
main.o: main.cpp /usr/local/include/SFML/Graphics.hpp \
  /usr/local/include/SFML/Window.hpp /usr/local/include/SFML/System.hpp \
  /usr/local/include/SFML/Config.hpp \
  /usr/local/include/SFML/System/Clock.hpp \
  /usr/local/include/SFML/System/Export.hpp \
  /usr/local/include/SFML/System/Time.hpp \
  /usr/local/include/SFML/System/Err.hpp \
  /usr/local/include/SFML/System/FileInputStream.hpp \
  /usr/local/include/SFML/System/InputStream.hpp \
  /usr/local/include/SFML/System/NonCopyable.hpp \
  /usr/local/include/SFML/System/Lock.hpp \
  /usr/local/include/SFML/System/MemoryInputStream.hpp \
  /usr/local/include/SFML/System/Mutex.hpp \
  /usr/local/include/SFML/System/Sleep.hpp \
  /usr/local/include/SFML/System/String.hpp \
  /usr/local/include/SFML/System/Utf.hpp \
  /usr/local/include/SFML/System/Utf.inl \
  /usr/local/include/SFML/System/String.inl \
  /usr/local/include/SFML/System/Thread.hpp \
  /usr/local/include/SFML/System/Thread.inl \
  /usr/local/include/SFML/System/ThreadLocal.hpp \
  /usr/local/include/SFML/System/ThreadLocalPtr.hpp \
  /usr/local/include/SFML/System/ThreadLocalPtr.inl \
  /usr/local/include/SFML/System/Vector2.hpp \
  /usr/local/include/SFML/System/Vector2.inl \
  /usr/local/include/SFML/System/Vector3.hpp \
  /usr/local/include/SFML/System/Vector3.inl \
  /usr/local/include/SFML/Window/Clipboard.hpp \
  /usr/local/include/SFML/Window/Export.hpp \
  /usr/local/include/SFML/Window/Context.hpp \
  /usr/local/include/SFML/Window/GlResource.hpp \
  /usr/local/include/SFML/Window/ContextSettings.hpp \
  /usr/local/include/SFML/Window/Cursor.hpp \
  /usr/local/include/SFML/Window/Event.hpp \
  /usr/local/include/SFML/Window/Joystick.hpp \
  /usr/local/include/SFML/Window/Keyboard.hpp \
  /usr/local/include/SFML/Window/Mouse.hpp \
  /usr/local/include/SFML/Window/Sensor.hpp \
  /usr/local/include/SFML/Window/Touch.hpp \
  /usr/local/include/SFML/Window/VideoMode.hpp \
  /usr/local/include/SFML/Window/Window.hpp \
  /usr/local/include/SFML/Window/WindowBase.hpp \
  /usr/local/include/SFML/Window/Vulkan.hpp \
  /usr/local/include/SFML/Window/WindowHandle.hpp \
  /usr/local/include/SFML/Window/WindowStyle.hpp \
  /usr/local/include/SFML/Graphics/BlendMode.hpp \
  /usr/local/include/SFML/Graphics/Export.hpp \
  /usr/local/include/SFML/Graphics/CircleShape.hpp \
  /usr/local/include/SFML/Graphics/Shape.hpp \
  /usr/local/include/SFML/Graphics/Drawable.hpp \
  /usr/local/include/SFML/Graphics/RenderStates.hpp \
  /usr/local/include/SFML/Graphics/Transform.hpp \
  /usr/local/include/SFML/Graphics/Rect.hpp \
  /usr/local/include/SFML/Graphics/Rect.inl \
  /usr/local/include/SFML/Graphics/Transformable.hpp \
  /usr/local/include/SFML/Graphics/VertexArray.hpp \
  /usr/local/include/SFML/Graphics/Vertex.hpp \
  /usr/local/include/SFML/Graphics/Color.hpp \
  /usr/local/include/SFML/Graphics/PrimitiveType.hpp \
  /usr/local/include/SFML/Graphics/ConvexShape.hpp \
  /usr/local/include/SFML/Graphics/Font.hpp \
  /usr/local/include/SFML/Graphics/Glyph.hpp \
  /usr/local/include/SFML/Graphics/Texture.hpp \
  /usr/local/include/SFML/Graphics/Image.hpp \
  /usr/local/include/SFML/Graphics/RectangleShape.hpp \
  /usr/local/include/SFML/Graphics/RenderTarget.hpp \
  /usr/local/include/SFML/Graphics/View.hpp \
  /usr/local/include/SFML/Graphics/RenderTexture.hpp \
  /usr/local/include/SFML/Graphics/RenderWindow.hpp \
  /usr/local/include/SFML/Graphics/Shader.hpp \
  /usr/local/include/SFML/Graphics/Glsl.hpp \
  /usr/local/include/SFML/Graphics/Glsl.inl \
  /usr/local/include/SFML/Graphics/Sprite.hpp \
  /usr/local/include/SFML/Graphics/Text.hpp \
  /usr/local/include/SFML/Graphics/VertexBuffer.hpp Flock.h Boid.h
Flock.o: Flock.cpp Flock.h /usr/local/include/SFML/Graphics.hpp \
  /usr/local/include/SFML/Window.hpp /usr/local/include/SFML/System.hpp \
  /usr/local/include/SFML/Config.hpp \
  /usr/local/include/SFML/System/Clock.hpp \
  /usr/local/include/SFML/System/Export.hpp \
  /usr/local/include/SFML/System/Time.hpp \
  /usr/local/include/SFML/System/Err.hpp \
  /usr/local/include/SFML/System/FileInputStream.hpp \
  /usr/local/include/SFML/System/InputStream.hpp \
  /usr/local/include/SFML/System/NonCopyable.hpp \
  /usr/local/include/SFML/System/Lock.hpp \
  /usr/local/include/SFML/System/MemoryInputStream.hpp \
  /usr/local/include/SFML/System/Mutex.hpp \
  /usr/local/include/SFML/System/Sleep.hpp \
  /usr/local/include/SFML/System/String.hpp \
  /usr/local/include/SFML/System/Utf.hpp \
  /usr/local/include/SFML/System/Utf.inl \
  /usr/local/include/SFML/System/String.inl \
  /usr/local/include/SFML/System/Thread.hpp \
  /usr/local/include/SFML/System/Thread.inl \
  /usr/local/include/SFML/System/ThreadLocal.hpp \
  /usr/local/include/SFML/System/ThreadLocalPtr.hpp \
  /usr/local/include/SFML/System/ThreadLocalPtr.inl \
  /usr/local/include/SFML/System/Vector2.hpp \
  /usr/local/include/SFML/System/Vector2.inl \
  /usr/local/include/SFML/System/Vector3.hpp \
  /usr/local/include/SFML/System/Vector3.inl \
  /usr/local/include/SFML/Window/Clipboard.hpp \
  /usr/local/include/SFML/Window/Export.hpp \
  /usr/local/include/SFML/Window/Context.hpp \
  /usr/local/include/SFML/Window/GlResource.hpp \
  /usr/local/include/SFML/Window/ContextSettings.hpp \
  /usr/local/include/SFML/Window/Cursor.hpp \
  /usr/local/include/SFML/Window/Event.hpp \
  /usr/local/include/SFML/Window/Joystick.hpp \
  /usr/local/include/SFML/Window/Keyboard.hpp \
  /usr/local/include/SFML/Window/Mouse.hpp \
  /usr/local/include/SFML/Window/Sensor.hpp \
  /usr/local/include/SFML/Window/Touch.hpp \
  /usr/local/include/SFML/Window/VideoMode.hpp \
  /usr/local/include/SFML/Window/Window.hpp \
  /usr/local/include/SFML/Window/WindowBase.hpp \
  /usr/local/include/SFML/Window/Vulkan.hpp \
  /usr/local/include/SFML/Window/WindowHandle.hpp \
  /usr/local/include/SFML/Window/WindowStyle.hpp \
  /usr/local/include/SFML/Graphics/BlendMode.hpp \
  /usr/local/include/SFML/Graphics/Export.hpp \
  /usr/local/include/SFML/Graphics/CircleShape.hpp \
  /usr/local/include/SFML/Graphics/Shape.hpp \
  /usr/local/include/SFML/Graphics/Drawable.hpp \
  /usr/local/include/SFML/Graphics/RenderStates.hpp \
  /usr/local/include/SFML/Graphics/Transform.hpp \
  /usr/local/include/SFML/Graphics/Rect.hpp \
  /usr/local/include/SFML/Graphics/Rect.inl \
  /usr/local/include/SFML/Graphics/Transformable.hpp \
  /usr/local/include/SFML/Graphics/VertexArray.hpp \
  /usr/local/include/SFML/Graphics/Vertex.hpp \
  /usr/local/include/SFML/Graphics/Color.hpp \
  /usr/local/include/SFML/Graphics/PrimitiveType.hpp \
  /usr/local/include/SFML/Graphics/ConvexShape.hpp \
  /usr/local/include/SFML/Graphics/Font.hpp \
  /usr/local/include/SFML/Graphics/Glyph.hpp \
  /usr/local/include/SFML/Graphics/Texture.hpp \
  /usr/local/include/SFML/Graphics/Image.hpp \
  /usr/local/include/SFML/Graphics/RectangleShape.hpp \
  /usr/local/include/SFML/Graphics/RenderTarget.hpp \
  /usr/local/include/SFML/Graphics/View.hpp \
  /usr/local/include/SFML/Graphics/RenderTexture.hpp \
  /usr/local/include/SFML/Graphics/RenderWindow.hpp \
  /usr/local/include/SFML/Graphics/Shader.hpp \
  /usr/local/include/SFML/Graphics/Glsl.hpp \
  /usr/local/include/SFML/Graphics/Glsl.inl \
  /usr/local/include/SFML/Graphics/Sprite.hpp \
  /usr/local/include/SFML/Graphics/Text.hpp \
  /usr/local/include/SFML/Graphics/VertexBuffer.hpp Boid.h
Boid.o: Boid.cpp Boid.h /usr/local/include/SFML/Graphics.hpp \
  /usr/local/include/SFML/Window.hpp /usr/local/include/SFML/System.hpp \
  /usr/local/include/SFML/Config.hpp \
  /usr/local/include/SFML/System/Clock.hpp \
  /usr/local/include/SFML/System/Export.hpp \
  /usr/local/include/SFML/System/Time.hpp \
  /usr/local/include/SFML/System/Err.hpp \
  /usr/local/include/SFML/System/FileInputStream.hpp \
  /usr/local/include/SFML/System/InputStream.hpp \
  /usr/local/include/SFML/System/NonCopyable.hpp \
  /usr/local/include/SFML/System/Lock.hpp \
  /usr/local/include/SFML/System/MemoryInputStream.hpp \
  /usr/local/include/SFML/System/Mutex.hpp \
  /usr/local/include/SFML/System/Sleep.hpp \
  /usr/local/include/SFML/System/String.hpp \
  /usr/local/include/SFML/System/Utf.hpp \
  /usr/local/include/SFML/System/Utf.inl \
  /usr/local/include/SFML/System/String.inl \
  /usr/local/include/SFML/System/Thread.hpp \
  /usr/local/include/SFML/System/Thread.inl \
  /usr/local/include/SFML/System/ThreadLocal.hpp \
  /usr/local/include/SFML/System/ThreadLocalPtr.hpp \
  /usr/local/include/SFML/System/ThreadLocalPtr.inl \
  /usr/local/include/SFML/System/Vector2.hpp \
  /usr/local/include/SFML/System/Vector2.inl \
  /usr/local/include/SFML/System/Vector3.hpp \
  /usr/local/include/SFML/System/Vector3.inl \
  /usr/local/include/SFML/Window/Clipboard.hpp \
  /usr/local/include/SFML/Window/Export.hpp \
  /usr/local/include/SFML/Window/Context.hpp \
  /usr/local/include/SFML/Window/GlResource.hpp \
  /usr/local/include/SFML/Window/ContextSettings.hpp \
  /usr/local/include/SFML/Window/Cursor.hpp \
  /usr/local/include/SFML/Window/Event.hpp \
  /usr/local/include/SFML/Window/Joystick.hpp \
  /usr/local/include/SFML/Window/Keyboard.hpp \
  /usr/local/include/SFML/Window/Mouse.hpp \
  /usr/local/include/SFML/Window/Sensor.hpp \
  /usr/local/include/SFML/Window/Touch.hpp \
  /usr/local/include/SFML/Window/VideoMode.hpp \
  /usr/local/include/SFML/Window/Window.hpp \
  /usr/local/include/SFML/Window/WindowBase.hpp \
  /usr/local/include/SFML/Window/Vulkan.hpp \
  /usr/local/include/SFML/Window/WindowHandle.hpp \
  /usr/local/include/SFML/Window/WindowStyle.hpp \
  /usr/local/include/SFML/Graphics/BlendMode.hpp \
  /usr/local/include/SFML/Graphics/Export.hpp \
  /usr/local/include/SFML/Graphics/CircleShape.hpp \
  /usr/local/include/SFML/Graphics/Shape.hpp \
  /usr/local/include/SFML/Graphics/Drawable.hpp \
  /usr/local/include/SFML/Graphics/RenderStates.hpp \
  /usr/local/include/SFML/Graphics/Transform.hpp \
  /usr/local/include/SFML/Graphics/Rect.hpp \
  /usr/local/include/SFML/Graphics/Rect.inl \
  /usr/local/include/SFML/Graphics/Transformable.hpp \
  /usr/local/include/SFML/Graphics/VertexArray.hpp \
  /usr/local/include/SFML/Graphics/Vertex.hpp \
  /usr/local/include/SFML/Graphics/Color.hpp \
  /usr/local/include/SFML/Graphics/PrimitiveType.hpp \
  /usr/local/include/SFML/Graphics/ConvexShape.hpp \
  /usr/local/include/SFML/Graphics/Font.hpp \
  /usr/local/include/SFML/Graphics/Glyph.hpp \
  /usr/local/include/SFML/Graphics/Texture.hpp \
  /usr/local/include/SFML/Graphics/Image.hpp \
  /usr/local/include/SFML/Graphics/RectangleShape.hpp \
  /usr/local/include/SFML/Graphics/RenderTarget.hpp \
  /usr/local/include/SFML/Graphics/View.hpp \
  /usr/local/include/SFML/Graphics/RenderTexture.hpp \
  /usr/local/include/SFML/Graphics/RenderWindow.hpp \
  /usr/local/include/SFML/Graphics/Shader.hpp \
  /usr/local/include/SFML/Graphics/Glsl.hpp \
  /usr/local/include/SFML/Graphics/Glsl.inl \
  /usr/local/include/SFML/Graphics/Sprite.hpp \
  /usr/local/include/SFML/Graphics/Text.hpp \
  /usr/local/include/SFML/Graphics/VertexBuffer.hpp
