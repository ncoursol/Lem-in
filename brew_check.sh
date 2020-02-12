#!bin/bash

if [ -d ~/.brew ]
then
	echo "\033[33mbrew already installed.\033[00m\n"
else
	echo "\033[31minstalling brew...\033[00m"
	rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc
	rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && export PATH=$HOME/.brew/bin:$PATH && echo "export PATH=$HOME/.brew/bin:$PATH" >> ~/.zshrc
	echo "\n"
fi
echo "\033[31mbrew update :\033[00m"
brew update
echo "\n"
if [ -d ~/.brew/Cellar/sdl2 ]
then
	echo "\033[33msdl2 already installed.\033[00m"
else
	echo "\033[31minstalling sdl2...\033[00m"
	brew install sdl2
	echo "\n"
fi
if [ -d ~/.brew/Cellar/sdl2_image ]
then
	echo "\033[33msdl2_image already installed.\033[00m"
else
	echo "\033[31minstalling sdl2_image...\033[00m"
	brew install sdl2_image
	echo "\n"
fi
if [ -d ~/.brew/Cellar/sdl2_ttf ]
then
	echo "\033[33msdl2_ttf already installed.\033[00m"
else
	echo "\033[31minstalling sdl2_ttf...\033[00m"
	brew install sdl2_ttf
fi
if [ -d ~/.brew/Cellar/sdl2_mixer ]
then
	echo "\033[33msdl2_mixer already installed.\033[00m"
else
	echo "\033[31minstalling sdl2_mixer...\033[00m"
	brew install sdl2_mixer
fi
if [ -d include/SDL2 ]
then
	rm -Rf include/SDL2/*
else
	mkdir include/SDL2
fi
echo "\n\033[32mcopy all brew .h in include/SDL2\033[00m"
cp ~/.brew/Cellar/sdl2/*/include/SDL2/*.h include/SDL2/
cp ~/.brew/Cellar/sdl2_image/*/include/SDL2/*.h include/SDL2/
cp ~/.brew/Cellar/sdl2_ttf/*/include/SDL2/*.h include/SDL2/
cp ~/.brew/Cellar/sdl2_mixer/*/include/SDL2/*.h include/SDL2/
if [ -d lib/sdl ]
then
	rm -Rf lib/sdl/*
else
	mkdir lib/sdl
fi
echo "\033[32mcopy all brew .a and .dylib in lib/sdl\033[00m"
cp ~/.brew/Cellar/sdl2/*/lib/*.a lib/sdl/
cp ~/.brew/Cellar/sdl2/*/lib/*.dylib lib/sdl/
cp ~/.brew/Cellar/sdl2_image/*/lib/*.dylib lib/sdl/
cp ~/.brew/Cellar/sdl2_image/*/lib/*.a lib/sdl/
cp ~/.brew/Cellar/sdl2_ttf/*/lib/*.a lib/sdl/
cp ~/.brew/Cellar/sdl2_ttf/*/lib/*.dylib lib/sdl/
cp ~/.brew/Cellar/sdl2_mixer/*/lib/*.a lib/sdl/
cp ~/.brew/Cellar/sdl2_mixer/*/lib/*.dylib lib/sdl/

