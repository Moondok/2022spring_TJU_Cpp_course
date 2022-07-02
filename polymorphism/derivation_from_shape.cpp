

/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/

class Shape
{
public:
    virtual double area() =0; //纯虚函数
};

class Circle:public Shape
{
private:
    double radius=0;
public:
    Circle(double r):radius(r)
    {};
    virtual double area() 
    {   
        cout<<"圆的面积是: ";
        return 3.1415926*radius*radius;
    }
};

class Square:public Shape
{
private:
    double edge=0;
public:
    Square(double e):edge(e)
    {};
    virtual double area() 
    {   
        cout<<"正方形的面积是: ";
        return edge*edge;
    }
};

class Rectangle:public Shape
{
private:
    double width=0,height=0;
public:
    Rectangle(double w,double h):width(w),height(h)
    {};
    virtual double area() 
    {   
        cout<<"矩形的面积是: ";
        return width*height;
    }
};

class Trapezoid:public Shape
{
private:
    double upper_edge=0,lower_edge=0,height=0;
public:
    Trapezoid(double u,double l,double h):upper_edge(u),lower_edge(l),height(h)
    {};
    virtual double area() 
    {   
        cout<<"梯形的面积是: ";
        return (upper_edge+lower_edge)*height/2.0;
    }
};

class Triangle:public Shape
{
private:
    double e1=0,e2=0,e3=0;
public:
    Triangle(double a1,double a2,double a3):e1(a1),e2(a2),e3(a3)
    {};
    virtual double area() 
    {   
        cout<<"三角形的面积是: ";
        double p=(e1+e2+e3)/2;
        return sqrt(p*(p-e1)*(p-e2)*(p-e3));
    }
};
/**********************************************
*
*    TO-DO END
*
***********************************************/

