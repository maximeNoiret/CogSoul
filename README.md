# CogSoul
Simple terminal game I'm making to practice my C++

Features a procedurally generated map, menus, customization/configuration, a little bit of lore, and a bit more to come (once I'm not too lazy to code lmao).
Will not get ported to Windows.

## How to install
### Binaries
You can download the latest pre-compiled binaries from the [release section](https://github.com/maxnrt/CogSoul/releases/latest) of this repo, tho it might not be up to date with the source so I recommend building it yourself. (you use linux, you should be used to compiling stuff)
1. Download the executable from the releases page
2. Download the 'rooms' folders from the repo and place it next to the executable
3. ``# chmod +x CogSoul`` to make it executable
4. ``$ ./CogSoul`` to start the game. It should generate a default config file next to itself.

### Building
I mean, you can just do like ``$ g++ -o CogSoul path/to/repo/*.cpp`` and it'll create an executable called CogSoul.
Or you could load the .pro file into QTCreator and build it with that.
I dunno how all this Makefile stuff works tbh and cba to figure it out lmao just use g++

---

## Contributing
If you don't mind needing to bleach your eyes after reading my code and, somehow, actually want to contribute, you can generate a documentation of the code using doxygen.
There is a Doxyfile already present at the root of the repo, so just use ``doxygen`` to generate the doc. It'll generate it in the 'doc' folder by default.
(Though you probably know all that if you wanna contribute lmao)

PS: if someone could make a pull request to implement A* for the enemies, I'd greatly appreciate it cuz I'm way too bad at math to figure it out.
