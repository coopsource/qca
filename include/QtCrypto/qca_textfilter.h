/*
 * qca_textfilter.h - Qt Cryptographic Architecture
 * Copyright (C) 2003-2005  Justin Karneges <justin@affinix.com>
 * Copyright (C) 2004,2005  Brad Hards <bradh@frogmouth.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef QCA_TEXTFILTER_H
#define QCA_TEXTFILTER_H

#include "qca_core.h"

namespace QCA
{
	/**
	   \class TextFilter qca_textfilter.h QtCrypto

	   Superclass for text based filtering algorithms

	   This differs from Filter in that it has the concept
	   of an algorithm that works in two directions, and 
	   supports operations on QString arguments.
	*/
	class QCA_EXPORT TextFilter : public Filter
	{
	public:
		/**
		   Standard constructor

		   \param dir the Direction that this TextFilter
		   should use.
		*/
		TextFilter(Direction dir);

		/**
		   Reset the TextFilter

		   \param dir the Direction that this TextFilter
		   should use.
		*/
		void setup(Direction dir);

		/**
		 Process an array in the "forward" direction,
		 returning an array

		 This method runs in the forward direction, so
		 for something like a Base64 encoding, it takes
		 the "native" array, and returns that array 
		 encoded in base64.

		 \param a the array to encode
		*/
		QSecureArray encode(const QSecureArray &a);

		/**
		 Process an array in the "reverse" direction,
		 returning an array

		 This method runs in the reverse direction, so
		 for something like a Base64 encoding, it takes
		 a Base64 encoded array, and returns the "native"
		 representation..

		 \param a the array to decode
		*/
		QSecureArray decode(const QSecureArray &a);

		/**
		 Process an array in the "forward" direction,
		 returning a QString

		 This is equivalent to encode(), except
		 that it returns a QString, rather than a
		 byte array.

		 \param a the array to encode
		*/
		QString arrayToString(const QSecureArray &a);

		/**
		 Process an string in the "reverse" direction,
		 returning a byte array

		 This is equivalent to decode(), except
		 that it takes a QString, rather than a
		 byte array.

		 \param s the array to decode
		*/
		QSecureArray stringToArray(const QString &s);

		/**
		 Process a string in the "forward" direction,
		 returning a string

		 This is equivalent to encode(), except
		 that it takes and returns a QString, rather than
		 byte arrays.

		 \param s the string to encode
		*/
		QString encodeString(const QString &s);

		/**
		 Process a string in the "reverse" direction,
		 returning a string

		 This is equivalent to decode(), except
		 that it takes and returns a QString, rather than
		 byte arrays.

		 \param s the string to decode
		*/
		QString decodeString(const QString &s);

	protected:
		/**
		   Internal state variable for the Direction
		   that the filter operates in
		*/
		Direction _dir;
	};

	/**
	   \class Hex qca_textfilter.h QtCrypto

	   Hexadecimal encoding / decoding
	*/
	class QCA_EXPORT Hex : public TextFilter
	{
	public:
		/**
		   Standard constructor

		   \param dir the Direction that should be used.

		   \note The direction can be changed using
		   the setup() call.
		*/
		Hex(Direction dir = Encode);

		/**
		 Reset the internal state.

		 This is useful to reuse an existing Hex object
		*/
		virtual void clear();

		/**
		   Process more data, returning the corresponding
		   encoded or decoded (depending on the Direction
		   set in the constructor or setup() call) representation.

		   If you find yourself with code that only calls
		   this method once, you might be better off using
		   encode() or decode(). Similarly, if the data is
		   really a string, you might be better off using
		   arrayToString(), encodeString(), stringToArray()
		   or decodeString().

		   \param a the array containing data to process
		*/
		virtual QSecureArray update(const QSecureArray &a);

		/**
		   Complete the algorithm

		   \return any remaining output. Because of the way
		   hexadecimal encoding works, this will return a 
		   zero length array - any output will have been returned
		   from the update() call.
		*/
		virtual QSecureArray final();

		/**
		 Test if an update() or final() call succeeded.
		 
		 \return true if the previous call succeeded
		*/
		virtual bool ok() const;

	private:
		uchar val;
		bool partial;
		bool _ok;
	};

	/**
	   \class Base64 qca_textfilter.h QtCrypto

	   Base64 encoding / decoding
	*/
	class QCA_EXPORT Base64 : public TextFilter
	{
	public:
		/**
		   Standard constructor

		   \param dir the Direction that should be used.

		   \note The direction can be changed using
		   the setup() call.
		*/
		Base64(Direction dir = Encode);

		/**
		 Reset the internal state. This is useful to 
		 reuse an existing Base64 object
		*/
		virtual void clear();

		/**
		   Process more data, returning the corresponding
		   encoded or decoded (depending on the Direction
		   set in the constructor or setup() call) representation.

		   If you find yourself with code that only calls
		   this method once, you might be better off using
		   encode() or decode(). Similarly, if the data is
		   really a string, you might be better off using
		   arrayToString(), encodeString(), stringToArray()
		   or decodeString().

		   \param a the array containing data to process
		*/
		virtual QSecureArray update(const QSecureArray &a);

		/**
		   Complete the algorithm

		   \return any remaining output. Because of the way
		   Base64 encoding works, you will get either an 
		   empty array, or an array containing one or two
		   "=" (equals, 0x3D) characters.
		*/
		virtual QSecureArray final();

		/**
		 Test if an update() or final() call succeeded.
		 
		 \return true if the previous call succeeded
		*/
		virtual bool ok() const;

	private:
		QSecureArray partial;
		bool _ok;
	};
}

#endif