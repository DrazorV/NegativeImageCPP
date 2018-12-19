//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2017 - 2018
//
//

#ifndef _Array
#define _Array

#include "Vec3.h"
#include <string>
#include <vector>
#include <ppm/ppm.h>

/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation. 
 */ 
using namespace imaging;
using namespace std;
namespace math
{

//------------------------------------ class Array ------------------------------------------------

	/*! It is the class that represents a generic data container for an Array.
	 * 
	 * It holds the actual buffer of the pixel values and provides methods for accessing them, 
	 * either as individual pixels or as a memory block. The Array class alone does not provide
	 * any functionality for loading and storing an array, as it is the result or input to such a procedure.
	 *
	 * The internal buffer of an array object stores the actual bytes (data) of the color image as
	 * a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is 
	 * width X height X sizeof(Color) bytes.
	 *
	 * All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
	 * intensity ranges, each color component is within the range [0.0, 1.0].
	 */
    template<typename T>
	class Array{

	public:
		                                             
	protected:
		vector<T> buffer;                              //! Holds the Array data.

		unsigned int width, 						 //! The width of the array (in pixels)
					 height;		                 //! The height of the array (in pixels)

	public:
		// metric accessors

		/*! Returns the width of the array
		 */
		const unsigned int getWidth() const {return width;}      
		
		/*! Returns the height of the array
		 */
		const unsigned int getHeight() const {return height;}   

		// data accessors
		
		/*! Obtains a pointer to the internal data.
		 *
		 *  This is NOT a copy of the internal array data, but rather a pointer
		 *  to the internally allocated space, so DO NOT attempt to delete the pointer. 
		 */
		vector<T> * getRawDataPtr();

		/*! Obtains the color of the array at location (x,y).
		 *
		 *  The method should do any necessary bounds checking.
		 *
		 *  \param x is the (zero-based) horizontal index of the pixel to get.
		 *  \param y is the (zero-based) vertical index of the pixel to get.
		 *
		 *  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		 */
		T getValue(unsigned int x, unsigned int y) const;

		// data mutators
		
		/*! Sets the RGB values for an (x,y) pixel.
		 * 
		 *  The method should perform any necessary bounds checking.
		 *  
		 *  \param x is the (zero-based) horizontal index of the pixel to set. 
		 *  \param y is the (zero-based) vertical index of the pixel to set. 
		 *  \param value is the new color for the (x,y) pixel.
		 */
		void setValue(unsigned int x, unsigned int y, T & value);

		/*! Copies the array data from an external raw buffer to the internal array buffer.
		 *
		 *  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
		 *  Array object and that the data buffer has been already allocated. If the array buffer is not allocated or the
		 *  width or height of the array are 0, the method should exit immediately.
		 *
		 *  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Array object.
		 */
		void setData(const vector<T> * & data_ptr);

		// constructors and destructor

		/*! Default constructor.
		 * 
		 * By default, the dimensions of the array should be zero and the buffer must be set to nullptr.
		 */
		Array();

		/*! Constructor with width and height specification.
		 *
		 * \param width is the desired width of the new array.
		 * \param height is the desired height of the new array.
		 */
        Array(unsigned int width, unsigned int height);

		/*! Constructor with data initialization.
		 *
		 * \param width is the desired width of the new array.
		 * \param height is the desired height of the new array.
		 * \param data_ptr is the source of the data to copy to the internal array buffer.
		 *
		 * \see setData
		 */
        Array(unsigned int width, unsigned int height, const vector<T> * data_ptr);

		/*! Copy constructor.
		 *
		 * \param src is the source array to replicate in this object.
		 */
		Array(const Array &src);

		/*! The array destructor.
		 */
		~Array();

		/*! Copy assignment operator.
		 *
		 * \param right is the source array.
		 */
        Array & operator = (const Array & right);

        /*! New operator.
		 *
		 * \param Returns reference to element of type T in raw j and column i.
		 */
        T & operator () (unsigned int i , unsigned int j);

	};
} //namespace math

#endif