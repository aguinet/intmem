intmem
======

This is a small header-only C++11 library that helps loading unaligned
integers from memory, in natural/little/big endian.

It has been tested under the following platforms: 

* GCC 8.2 and Clang 6.0 under Linux/x32, Linux/x64 and Linux/mipsbe (using QEMU).
* Windows x32 and x64 using Visual Studio 2015

Tests
-----

The ``tests.cpp`` file can be compiled to run tests:

.. code:: bash

  $ c++ tests.cpp -std=c++11 -O2 -o tests
  $ ./tests

If everything goes fine, the process returns 0 and print the message ``All
tests are OK.``.

One way to test big-endian support on x86 computers is to cross-compiling for
MIPS under Debian, and run it using QEMU user mode:

.. code:: bash

   $ sudo dpkg --add-architecture mips && sudo apt update
   $ sudo apt install qemu-user qemu-user-binfmt clang-6.0 libstdc++-8-dev:mips binutils-mips-linux-gnu
   $ clang++-6.0 -target mips-linux-gnu -O2 tests.cpp -std=c++11 -o tests
   $ ./tests
