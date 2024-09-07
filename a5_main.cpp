// a5_main.cpp

#include "Wordlist.h"

//
// test_read() is a helper function that reads words, one at a time, from cin,
// into a Wordlist and print the stats. You can use it to help test your
// Wordlist class, e.g.:
//
//    > make a5_main
//    g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   a5_main.cpp   -o a5_main
//   
//    > ./a5_main < tiny_shakespeare.txt
//    Number of different words: 25670
//        Total number of words: 202651
//           Most frequent word: the 5437
//         Number of singletons: 14919 (58%)
//
// void test_read()
// {
//     Wordlist lst;
//     string w;
//     while (cin >> w)
//     {
//         lst.add_word(w);
//     }
//
//     lst.print_stats();
// }

 void test_read()
 {
       Wordlist lst;
       string w;
       while (cin >> w)
       {
           lst.add_word(w);
       }

      
    lst.print_words();
    cout << endl;
    lst.print_stats();
 }

 void test_wordlist()
{
    cout << "test_wordlist() called ...\n";
    Wordlist lst("small.txt");
    //Wordlist lst;
    lst.print_words();
    cout << endl;
    lst.print_stats();
    //assert(lst.num_different_words() == 0);
    //assert(lst.total_words() == 0);
     assert(lst.is_sorted());
    // assert(!lst.contains("hello"));
    // assert(lst.num_singletons() == 0);
    // assert(lst.get_count("gello") == 0);
   // assert(lst.most_frequent() == "a 2");
    // ... add more tests: test all methods! ...

    cout << "... test_wordlist() done: all tests passed!\n";
}


int main()
{
    //test_read();
    test_wordlist();
    // Wordlist lst;
    // string w;
    // w = "hello";
    //  lst.print_words();
}
