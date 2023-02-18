# Extra Credit Lab 1

## Ethan Berkley

Use **make** to compile

> $ make
>
> mkdir bin  
>  cc -c -g src/main.cpp -o bin/main.o  
>  cc -c -g src/Data.cpp -o bin/Data.o  
>  g++ -g bin/main.o bin/Data.o -o out

> $ ./out
>
> Department #1 will get Programmer #1  
>  Department #2 will get Programmer #3  
>  Department #3 will get Programmer #5  
>  Department #4 will get Programmer #2  
>  Department #5 will get Programmer #4

> $ make clean
>
> rm -rf bin out
