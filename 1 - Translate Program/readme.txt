Simple program that reads from a file with ISO8859-7 format and translates the greek characters into ISO8859-1 English characters.
Done exactly as asked, and the program might swap a few special characters with Null character "\0". Also used an fsm and a functions
array to properly handle 2-letter Greek characters. A normal execution could be:

$ cat test.7 | translate

$ translate < test.7 > test.1