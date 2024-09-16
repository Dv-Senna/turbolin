#include "test.hpp"

#include <iostream>


namespace test {
	void sayHello() {
		#ifdef TL_WINDOWS
			std::cout << "Hello from Windows turbolin !" << std::endl;
		#elifdef TL_LINUX
			std::cout << "Hello from Linux turbolin !" << std::endl;
		#elifdef TL_APPLE
			std::cout << "Hello from Apple turbolin !" << std::endl;
		#else
			#error Unable to know on which OS you try to compile this code
		#endif
	}
}
