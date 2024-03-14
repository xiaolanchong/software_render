#ifndef _ARRAY2_D_1120725408559299_
#define _ARRAY2_D_1120725408559299_

template<typename T>
class Array2D
{
	std::vector<T>	m_Data;
	size_t				m_nWidth;
	size_t				m_nHeight;
	size_t				m_nStride;
public:
	Array2D( size_t nWidth, size_t nHeight, size_t nStride ):
		m_Data( nStride * nHeight ),
		m_nWidth(nWidth), m_nHeight(nHeight),  m_nStride(nStride)
		{
		}

	void resize ( size_t nWidth, size_t nHeight, size_t nStride )
	{
		m_Data.resize( nStride * nHeight );
		m_nWidth	= nWidth;
		m_nHeight	= nHeight;
		m_nStride	= nStride;
	}
	
	T&	operator() (size_t i, size_t j)
	{
		ASSERT( i < m_nWidth );
		ASSERT( j < m_nHeight );
		return m_Data[ j * m_nStride + i ];
	}
	const operator() (size_t i, size_t j) const
	{
		ASSERT( i < m_nWidth );
		ASSERT( j < m_nHeight );
		return m_Data[ j * m_nStride + i ];
	}

	typename std::vector<T>::iterator		begin()			{ return m_Data.begin(); }
	typename std::vector<T>::const_iterator	begin() const	{ return m_Data.begin(); }

	typename std::vector<T>::iterator		end()			{ return m_Data.end(); }
	typename std::vector<T>::const_iterator	end() const		{ return m_Data.end(); }

	size_t	GetWidth()	const { return m_nWidth; }
	size_t	GetHeight() const { return m_nHeight; }

	~Array2D(){}
};

#endif // _ARRAY2_D_1120725408559299_