## compile the code

```bash
git clone https://github.com/robosina/GCALGO.git
cd GCALGO
mkdir build
cd build 
cmake ..
make
```

You can see that an executable file named `greedy_construction` was created following a successful compilation:
```bash
$ ls
bin  CMakeCache.txt  CMakeFiles  cmake_install.cmake  greedy_construction  lib  Makefile  tests
```

We can run the executable file as follows:
```bash
./greedy_construction /path/2/Sample_Input.json
```

We can find a file named `output.json` near the executable if it was successful.