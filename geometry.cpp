template <typename T>
class point
{
public:
	T x = 0;
	T y = 0;
	T z = 0;
	point(){}
	point(T xx, T yy, T zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}
	
};


template <typename T>
class line//Ax+By+Cz+D=0
{
public:
	T A = 0;
	T B = 0;
	T C = 0;
	T D = 0;
	line(point<T> pos1, point<T> pos2)
	{
		
	}
	T value(point<T> pos){return A * pos.x + B * pos.y + C;}
};
