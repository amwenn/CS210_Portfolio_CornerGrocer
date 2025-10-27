# CS210_Portfolio_CornerGrocer
SNHU CS-210 Project Three – Corner Grocer Program in C++

The Corner Grocer program analyzes a text file of daily produce purchases to show how often each item is bought. It reads CS210_Project_Three_Input_File.txt, counts every unique item, and automatically writes the totals to frequency.dat for backup. The user can search for a single item, print all item frequencies, or view a histogram made of asterisks. The goal is to help the store plan its produce layout based on real sales data.

What I Did Well:
I’m proud of how clearly structured and readable my code is. I used a FrequencyTable class to separate data logic from user interaction, added inline comments, and followed proper naming conventions. Input validation prevents bad menu entries, and case-insensitive searches make the program friendly and reliable.

Where I Could Enhance the Code:
I could improve the program by sorting the histogram by most-sold items or allowing the input filename to be chosen at runtime. I’d also like to add color output and formatting for easier visualization. These changes would make the program more efficient and adaptable for future data.

Most Challenging Part and How I Solved It:
The hardest part was making Visual Studio find the input file correctly. I learned how the working directory works and placed the text file in the x64\Debug folder so it loads at runtime. I also researched how C++ maps work to count items efficiently, which improved performance compared to using multiple loops.

Transferable Skills:
This project strengthened my understanding of file I/O, classes, and data structures such as std::map. I also practiced input validation and exception handling. These skills will transfer directly to future C++, Python, or Java projects and any course requiring data processing or modular design.

Maintainability and Readability:
To make the program maintainable, I separated the class into a header and source file, kept functions short and single-purpose, and used clear comments. Variable names are descriptive, and the menu logic is easy to extend if more features are added. The result is code that another developer could quickly understand and modify.
