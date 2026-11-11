#include <framework/Stdoutlogger.h>

#include <UIKit/UIKit.h>

int main(int argc, char **argv) //5
{
    framework::StdoutLogger logger; //7
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init]; //8
	int result = UIApplicationMain(argc, argv, nil, @"AppController"); //9
    [pool release]; //10
    
    delete logger;
    
	return result;
}