template <typename T>
class Vectors//(x,y,z)
{
public:
	T x = (T)(0);
	T y = (T)(0);
	T z = (T)(0);
	Vectors(){}
	Vectors(T xx, T yy, T zz){x = xx; y = yy; z = zz;}
	Vectors(const Vectors<T> &vec){x = vec.x; y = vec.y; z = vec.z;}
	column<T> to_column(){return column<T>({x, y, z});}//转化成向量形式 
	bool parallel(Vectors<T> vec){return (x * vec.y == y * vec.x && y * vec.z == z * vec.y && z * vec.x == x * vec.z);}//平行 
	bool vertical(Vectors<T> vec){return (inner_product(*this, vec) == (T)(0));}//垂直
	void operator=(const Vectors<T> &vec){x = vec.x; y = vec.y; z = vec.z;}
	Vectors<T> operator+(const Vectors<T> &vec){return Vectors<T>(x + vec.x, y + vec.y, z + vec.z);}
	Vectors<T> operator-(const Vectors<T> &vec){return Vectors<T>(x - vec.x, y - vec.y, z - vec.z);}
	Vectors<T> operator-(){return Vectors<T>(-x, -y, -z);}
	Vectors<T> operator*(const T &coef){return Vectors<T>(x * coef, y * coef, z * coef);}
	Vectors<T> operator/(const T &coef)
	{
		if(coef == (T)(0))
			exit(1003);
		return Vectors<T>(x / coef, y / coef, z / coef);
	}
	bool operator==(const Vectors<T> &vec){return (x == vec.x && y == vec.y && z == vec.z);}
	bool operator!=(const Vectors<T> &vec){return !(x == vec.x && y == vec.y && z == vec.z);}
	void plumb(Vectors<T> vec)//使本向量与给定向量垂直 
	{
		if(vec != Vectors<T>((T)(0), (T)(0), (T)(0)))
			*this = *this - vec * inner_product<T>(*this, vec) / inner_product<T>(vec, vec);
	}
	
};
template <typename T>
T inner_product(Vectors<T> vec1, Vectors<T> vec2)//内积 
{
	return (T)(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
template <typename T>
Vectors<T> cross_product(Vectors<T> vec1, Vectors<T> vec2)//叉积
{
	return Vectors<T>((T)(vec1.y * vec2.z - vec1.z * vec2.y), (T)(vec1.z * vec2.x - vec1.x * vec2.z), (T)(vec1.x * vec2.y - vec1.y * vec2.x));
}
template <typename T>
matrix<T> outer_product(Vectors<T> vec1, Vectors<T> vec2)//外积 
{
	matrix<T> outmatrix({column<T>({vec1.x * vec2.x, vec1.x * vec2.y, vec1.x * vec2.z}),\
						 column<T>({vec1.y * vec2.x, vec1.y * vec2.y, vec1.y * vec2.z}),\
						 column<T>({vec1.z * vec2.x, vec1.z * vec2.y, vec1.z * vec2.z})});
	return outmatrix;
}
template <typename T>
Vectors<T> projection(Vectors<T> base, Vectors<T> vec)//向量在给定向量上的投影 
{
	Vectors<T> newvec = vec;
	newvec.plumb(base);
	return vec - newvec;
}
template <typename T>
void normalize()//对向量作规整化 
{
	
}


template <typename T>
class Line//(x-x0)/A=(y-y0)/b=(z-z0)/c
{
public:
	Vectors<T> start;//起始点（要求与方向向量正交） 
	Vectors<T> veloc;//方向向量
	Line(){}
	Line(Vectors<T> st, Vectors<T> ve)
	{
		if(ve == Vectors<T>((T)(0), (T)(0), (T)(0)))
			exit(1009);
		start = st;
		veloc = ve;
		start.plumb(veloc);
	}
	void operator=(const Line &aline)
	{
		start = aline.start;
		veloc = aline.veloc;
	}
};


template <typename T>
class Surface//A(x-x0)+B(y-y0)+C(z-z0)=0
{
public:
	Vectors<T> start;//起始点（要求与方向向量正交）
	Vectors<T> veloc_1;
	Vectors<T> veloc_2;
	Surface(){}
	Surface(Vectors<T> st, Vectors<T> ve_1, Vectors<T> ve_2)
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
	Vectors<T>* base1 = NULL;
	Vectors<T>* base2 = NULL;
	Vectors<T>* base3 = NULL;
};

