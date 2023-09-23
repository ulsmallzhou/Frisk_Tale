template <typename T>
class point_3//(x,y,z)
{
public:
	T x = (T)(0);
	T y = (T)(0);
	T z = (T)(0);
	point_3(){}
	point_3(T xx, T yy, T zz){x = xx; y = yy; z = zz;}
	point_3(const point_3<T> &vec){x = vec.x; y = vec.y; z = vec.z;}
	column<T> to_column(){return column<T>({x, y, z});}//转化成向量形式 
	bool parallel(point_3<T> vec){return (x * vec.y == y * vec.x && y * vec.z == z * vec.y && z * vec.x == x * vec.z);}//平行 
	bool vertical(point_3<T> vec){return (x * vec.x + y * vec.y + z * vec.z == (T)(0));}//垂直
	void operator=(const point_3<T> &vec){x = vec.x; y = vec.y; z = vec.z;}
	point_3<T> operator+(const point_3<T> &vec){return point_3<T>(x + vec.x, y + vec.y, z + vec.z);}
	point_3<T> operator-(const point_3<T> &vec){return point_3<T>(x - vec.x, y - vec.y, z - vec.z);}
	point_3<T> operator-(){return point_3<T>(-x, -y, -z);}
	point_3<T> operator*(const T &coef){return point_3<T>(x * coef, y * coef, z * coef);}
	point_3<T> operator/(const T &coef)
	{
		if(coef == (T)(0))
			exit(1003);
		return point_3<T>(x / coef, y / coef, z / coef);
	}
	bool operator==(const point_3<T> &vec){return (x == vec.x && y == vec.y && z == vec.z);}
	bool operator!=(const point_3<T> &vec){return !(x == vec.x && y == vec.y && z == vec.z);}
	void plumb(point_3<T> vec)//使本向量与给定向量垂直 
	{
		if(vec != point_3<T>((T)(0), (T)(0), (T)(0)))
			*this = *this - vec * inner_product<T>(*this, vec) / inner_product<T>(vec, vec);
	}
};
template <typename T>
T inner_product(point_3<T> vec1, point_3<T> vec2)//内积 
{
	return (T)(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
template <typename T>
point_3<T> cross_product(point_3<T> vec1, point_3<T> vec2)//叉积
{
	return point_3<T>((T)(vec1.y * vec2.z - vec1.z * vec2.y), (T)(vec1.z * vec2.x - vec1.x * vec2.z), (T)(vec1.x * vec2.y - vec1.y * vec2.x));
}
template <typename T>
matrix<T> outer_product(point_3<T> vec1, point_3<T> vec2)//外积 
{
	matrix<T> outmatrix({column<T>({vec1.x * vec2.x, vec1.x * vec2.y, vec1.x * vec2.z}),\
						 column<T>({vec1.y * vec2.x, vec1.y * vec2.y, vec1.y * vec2.z}),\
						 column<T>({vec1.z * vec2.x, vec1.z * vec2.y, vec1.z * vec2.z})});
	return outmatrix;
}
template <typename T>
point_3<T> projection(point_3<T> base, point_3<T> vec)//向量在给定向量上的投影 
{
	point_3<T> newvec = vec;
	newvec.plumb(base);
	return vec - newvec;
}
template <typename T>
point_3<T> gravity(cyclist<point_3<T>> vectors)
{
	point_3<T> sum((T)(0), (T)(0), (T)(0));
	int length = vectors.size();
	if(length == 0)
		exit(1009);
	for(int id = 0; id < length; id += 1)
		sum = sum + vectors[id];
	return sum / length;
}


template <typename T>
class Line_3//(x-x0)/A=(y-y0)/b=(z-z0)/c
{
public:
	point_3<T> start;//起始点（要求与方向向量正交） 
	point_3<T> veloc;//方向向量
	Line_3(){}
	Line_3(point_3<T> st, point_3<T> ve)
	{
		if(ve == point_3<T>((T)(0), (T)(0), (T)(0)))
			exit(1009);
		start = st;
		veloc = ve;
		start.plumb(veloc);
	}
	void operator=(const Line_3 &aline)
	{
		start = aline.start;
		veloc = aline.veloc;
	}
	bool operator==(const Line_3 &aline)
	{
		Line_3 line = aline;
		if(start != line.start) return 0;
		return line.veloc.parallel(veloc);
	}
	bool operator!=(const Line_3 &aline)
	{
		return !(*this == aline);
	}
};


template <typename T>
class Surface//A(x-x0)+B(y-y0)+C(z-z0)=0
{
public:
	point_3<T> start;//起始点（要求与方向向量正交）
	point_3<T> veloc_1;
	point_3<T> veloc_2;
	Surface(){}
	Surface(point_3<T> st, point_3<T> ve_1, point_3<T> ve_2)
	{
		if(ve_1.parallel(ve_2))
			exit(1009);
		start = st;
		veloc_1 = ve_1;
		veloc_2 = ve_2;
		veloc_2.plumb(veloc_1);
		start.plumb(veloc_1);
		start.plumb(veloc_2);
	}
	void operator=(const Surface &asur)
	{
		start = asur.start;
		veloc_1 = asur.veloc_1;
		veloc_2 = asur.veloc_2;
	}
};


template <typename T>
class Basement
{
public:
	point_3<T>* base1 = NULL;
	point_3<T>* base2 = NULL;
	point_3<T>* base3 = NULL;
};

