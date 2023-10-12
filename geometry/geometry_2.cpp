template <typename T>
class point_2//(x,y)
{
public:
	T x = (T)(0);
	T y = (T)(0);
	point_2(){}
	point_2(T xx, T yy){x = xx; y = yy;}
	point_2(const point_2<T> &apoint){x = apoint.x; y = apoint.y;}
	column<T> to_column(){return column<T>({x, y});}
	bool parallel(point_2<T> apoint){return x * apoint.y == y * apoint.x;}
	bool vertical(point_2<T> apoint){return x * apoint.x + y * apoint.y == 0;}
	void operator=(const point_2<T> &apoint){x = apoint.x; y = apoint.y;}
	point_2<T> operator+(const point_2<T> &apoint){return point_2<T>(x + apoint.x, y + apoint.y);}
	point_2<T> operator-(const point_2<T> &apoint){return point_2<T>(x - apoint.x, y - apoint.y);}
	point_2<T> operator-(){return point_2<T>(-x, -y);}
	point_2<T> operator*(const T &coef){return point_2<T>(x * coef, y * coef);}
	point_2<T> operator/(const T &coef)
	{
		if(coef == (T)(0)) exit(1003);
		return point_2<T>(x / coef, y / coef);
	}
	bool operator==(const point_2<T> &apoint){return (x == apoint.x && y == apoint.y);}
	bool operator!=(const point_2<T> &apoint){return !(x == apoint.x && y == apoint.y);}
	void plumb(point_2<T> apoint)//使本向量与给定向量垂直 
	{
		if(apoint != point_2<T>((T)(0), (T)(0)))
			*this = *this - apoint * inner_product<T>(*this, apoint) / inner_product<T>(apoint, apoint);
	}
};
template <typename T>//内积 
T inner_product(point_2<T> point1, point_2<T> point2){return (T)(point1.x * point2.x + point1.y * point2.y);}
template <typename T>//外积 
matrix<T> outer_product(point_2<T> point1, point_2<T> point2){return matrix<T>({column<T>({point1.x * point2.x, point1.x * point2.y}), column<T>({point1.y * point2.x, point1.y * point2.y})});}
template <typename T>
point_2<T> projection(point_2<T> base, point_2<T> apoint)//向量在给定向量上的投影 
{
	point_2<T> newpoint = apoint;
	newpoint.plumb(base);
	return apoint - newpoint;
}
template <typename T>
class Line_2//(x-x0)/A+(y-y0)/B=0
{
public:
	point_2<T> start;//起始点（要求与方向向量正交） 
	point_2<T> veloc;//方向向量
	Line_2(){}
	Line_2(point_2<T> st, point_2<T> ve)
	{
		if(ve == point_2<T>((T)(0), (T)(0))) exit(1009);
		start = st; veloc = ve; start.plumb(veloc);
	}
	void operator=(const Line_2 &aline){start = aline.start; veloc = aline.veloc;}
	bool operator==(const Line_2 &aline)
	{
		Line_2 line = aline;
		if(start != line.start) return 0;
		return line.veloc.parallel(veloc);
	}
	bool operator!=(const Line_2 &aline){return !(*this == aline);}
};
template <typename T>
class Convex_Hull_2//二维凸包（凸多边形） 
{
	point_2<T> center;//中心坐标 
	cyclist<point_2<T>> edgepoints;//凸包点相对于中心的坐标
	Convex_Hull_2(){}
	Convex_Hull_2(cyclist<point_2<T>> points)
	{
		int point_num = points.size();
		if(point_num < 3) exit(1009);
	}
};

