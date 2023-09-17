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
	bool parallel(Vectors<T> vec){return (x * vec.y == y * vec.x && y * vec.z == z * vec.y && y * vec.z == z * vec.y);}//平行 
	bool vertical(Vectors<T> vec){return (this->inner_product(vec) == (T)(0));}//垂直
	T inner_product(Vectors<T> vec){return (T)(x * vec.x + y * vec.y + z * vec.z);}//内积 
	Vectors<T> cross_product(Vectors<T> vec){return Vectors<T>((T)(y * vec.z - z - vec.y), (T)(z * vec.x - x - vec.z), (T)(x * vec.y - y - vec.x));}//叉积 
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
};


template <typename T>
class Line
{
public:
	Vectors<T> start;//起始点 
	Vectors<T> veloc;//方向向量
	Line(){}
	Line(Vectors<T> vec1, Vectors<T> vec2){start = vec1; veloc = vec2 - vec1;}
	Tuple<int, Vectors<T>> intersection(Line aline)//求解交点 
	{
		Vectors<T> newstart;
		//λveloc - μaline.veloc = aline.start - start
		matrix<T> coefs({veloc.to_column(), -aline.veloc.to_column(), (aline.start - start).to_column});
	}
};


template <typename T>
class Surface//Ax+By+Cz+D=0
{
public:
	T A = (T)(0);
	T B = (T)(0);
	T C = (T)(0);
	T D = (T)(0);
	line(Vectors<T> vec1, Vectors<T> vec2)
	{
		if(vec1 == vec2)
			exit(1009);
		if(vec1.x == vec2.x)
			exit(1);
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

