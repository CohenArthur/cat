# cat
A simple cat implementation with a GNU Fast® aligned buffer

The source code should be relatively self-explanatory.

## Memory footprint
### GNU cat
```
yuuko@navi ~/git/cat $ valgrind cat cat.c nonexistent_file cat.c >/dev/null
==2558== Memcheck, a memory error detector
==2558== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==2558== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==2558== Command: cat cat.c nonexistent_file cat.c
==2558== 
cat: nonexistent_file: No such file or directory
==2558== 
==2558== HEAP SUMMARY:
==2558==     in use at exit: 0 bytes in 0 blocks
==2558==   total heap usage: 63 allocs, 63 frees, 149,881 bytes allocated
==2558== 
==2558== All heap blocks were freed -- no leaks are possible
==2558== 
==2558== For counts of detected and suppressed errors, rerun with: -v
==2558== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
### My cat
```
yuuko@navi ~/git/cat $ valgrind ./cat cat.c nonexistent_file cat.c >/dev/null
==2546== Memcheck, a memory error detector
==2546== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==2546== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==2546== Command: ./cat cat.c nonexistent_file cat.c
==2546== 
./cat: nonexistent_file: No such file or directory
==2546== 
==2546== HEAP SUMMARY:
==2546==     in use at exit: 0 bytes in 0 blocks
==2546==   total heap usage: 5 allocs, 5 frees, 9,896 bytes allocated
==2546== 
==2546== All heap blocks were freed -- no leaks are possible
==2546== 
==2546== For counts of detected and suppressed errors, rerun with: -v
==2546== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
As you can see, mine blows GNU's out of the water.
## speed
```
yuuko@navi ~/git/cat $ du -sh ~/Downloads/`ls -S ~/Downloads | sed q`
537M	/home/yuuko/Downloads/9front-4308.4e3f4e43246e.iso

```
GNU cat
```
yuuko@navi ~/git/cat $ time cat ~/Downloads/9front-4308.4e3f4e43246e.iso >/dev/null

real	0m0.483s
user	0m0.009s
sys	0m0.472s
```
My cat
```
yuuko@navi ~/git/cat $ time ./cat ~/Downloads/9front-4308.4e3f4e43246e.iso >/dev/null

real	0m0.482s
user	0m0.015s
sys	0m0.46s
```
Speeds are consistently neck-and-neck.
