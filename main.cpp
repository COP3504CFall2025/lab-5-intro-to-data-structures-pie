#ifdef MAIN_H
#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    LLS<int> s;
    s.push(15);
    s.push(20);
    s.push(30);

    LLS<int> d = std::move(s);
    std::cout << d.peek() << std::endl;
    std::cout << d.pop() << " " << d.pop() << " " << d.pop() << std::endl;
    d.push(20);
    std::cout << d.peek() << std::endl;
    return 0;
}
#endif