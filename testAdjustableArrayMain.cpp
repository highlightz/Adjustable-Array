#define DEBUG_ADJUSTABLE_ARRAY 
#include "AdjustableArray.h"

#include <iostream>
using std::cout;
using std::endl;

namespace miscellaneous
{
	void getElements( AdjustableArray< int >& numbers )
	{

	}
	float calcAverage( AdjustableArray< int > numbers )
	{
		return 0.0;
	}
}

void miscellaneous::getElements( AdjustableArray< int >& numbers );
float miscellaneous::calcAverage( AdjustableArray< int > numbers );

int main( )
{
	AdjustableArray< int > nums( 2 );
	miscellaneous::getElements( nums );
	float average = miscellaneous::calcAverage( nums );
	cout << "The average is: " << average << endl;
	return 0;
}
