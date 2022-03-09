# Top-Down-Parser


### Input format

The input format has to keep the followind rules:

- It has to have a starting symbol which is marked with ```S```
- The rules follow the the following format: D>DkLsdk where D is a non-terminal (all capitals are considered non-terminals)
- Every rule must be given separately which means you cannot give for EG. S>sd,Lksd -> this has to be given in the following format: S>sd S>Lksd
- The input must be only one line as well as the input word


### Compile & Link

```g++ -c src/*.cpp && g++ *.o -o main```


### Run

In the base directory run: ```./main```


*written and tested for linux*