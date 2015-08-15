// AdjustableArray.h -- class template for an adjustable array
// When debugging, use #define DEBUG_ADJUSTABLE_ARRAY above your #include Array line.
// When done debugging, comment out #define DEBUG_ADJUSTABLE_ARRAY for better performance.
// The constructor and the changeSize function can cause an exception to be thrown if out of heap memory.

#include <string>
using std::string;

template < class DataType >
class AdjustableArray
{
public:
	AdjustableArray( int size );
	AdjustableArray( const AdjustableArray< DataType >& ap );
	~AdjustableArray( );
	AdjustableArray< DataType >& operator =( const AdjustableArray< DataType >& right );
	inline DataType& operator [ ]( int index );
	void changeSize( int newSize );  // Will not alter values unless newSize is smaller than current capacity;
                                         // in this case, the values from 0 to newSize - 1 will not be altered.
	inline int length( ) const;  // Returns the current capacity of the array
	
	string err( ) const;  // Returns error message from errorCode.

private:
	DataType* elements;  // Points to the dynamic array
	int capacity;
	DataType dud;  // Returned from operator [ ] if index error occurs
	int errorCode;  // Contains code for error if array misuse occurs
	inline void deepCopy( const AdjustableArray< DataType >& original );
};

// Implementation of  AdjustableArray 
// Error codes -- use powers of 2
// 0 - No error
// 1 - Nonpositive size passed into constructor
// 2 - Invalid index was used
// 4 - Nonpositive new size passed into changeSize function

template < class DataType >
AdjustableArray< DataType >::AdjustableArray( int size )
{
	if ( size < 1 )
	{
		capacity = 1;
		errorCode = 1;  // Nonpositive size passed into constructor
	}
	else
	{
		capacity = size;
		errorCode = 0;  // No error
	}
	elements = new DataType [capacity];
}

template < class DataType >
AdjustableArray< DataType >::AdjustableArray( const AdjustableArray< DataType >& ap )
{
	deepCopy( ap );
}

template < class DataType >
AdjustableArray< DataType >::~AdjustableArray( )
{
	delete [ ] elements;
}

template < class DataType >
inline DataType& AdjustableArray< DataType >::operator [ ]( int index )
{
#ifdef DEBUG_ADJUSTABLE_ARRAY
	if ( index < 0 || index >= capacity )
	{
		errorCode |= 2;  // Invalid index was used
		return dud;
	}
#endif
	return elements[index];
}

template < class DataType >
void AdjustableArray< DataType >::changeSize( int newSize )
{
	if ( newSize < 1 )
	{
		errorCode |= 4;  // Nonpositive new size
		return;
	}
	DataType* newArray = new DataType [newSize];

	int limit = ( newSize > capacity ) ? capacity : newSize;

	for ( int i = 0; i < limit; i++ )
	{
		newArray[ i ] = elements[ i ];
	}

	delete [ ] elements;

	elements = newArray;

	capacity = newSize;
}

template < class DataType >
inline int AdjustableArray< DataType >::length( ) const
{
	return capacity;
}

template < class DataType >
string AdjustableArray< DataType >::err( ) const
{
	if ( errorCode == 0 )
		return "No error.\n";

	string errMsg = "";
	
	if ( errorCode & 1 )  // Nonpositive size passed into constructor
	{
		errMsg += "Nonpositive size passed into constructor, so\n";
		errMsg += "the capacity was set to 1 by default.\n";
	}

	if ( errorCode & 2 )  // Invalid index was used
	{
		errMsg += "Invalid index was used\n";
	}

	if ( errorCode & 4 )  // Nonpositive new size passed into changeSize
	{
		errMsg += "Invalid index was used, so\n";
		errMsg += "the size of the array was not changed.\n";
	}

	return errMsg;
}

template < class DataType >
inline void AdjustableArray< DataType >::deepCopy( const AdjustableArray< DataType >& original )
{
	// Note: private members of input object original are accessible.
	capacity = original.capacity;
	errorCode = original.errorCode;
	elements = new DataType [ capacity ];

	for ( int i = 0; i < capacity; i++ )
	{
		elements[ i ] = original.elements[ i ];
	}
}

template < class DataType >
AdjustableArray< DataType >&  AdjustableArray< DataType >::operator =( const AdjustableArray< DataType >& right )
{
	if ( this == &right )
		return *this;
	delete [ ] elements;
	deepCopy( right );

	return  *this;
}
