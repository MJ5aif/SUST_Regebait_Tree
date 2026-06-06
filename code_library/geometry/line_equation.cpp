array<T, 3> line_equation(const Point<T>&b, const Point<T>&c){
 array<T, 3>res;
 res[0] = b.y - c.y, res[1] = -(b.x - c.x), res[2] = b.x*c.y - b.y*c.x;
 if(res[0] < 0)res[0] = -res[0], res[1] = -res[1], res[2] = -res[2];
 else if(res[0] == 0 and res[1] < 0)res[1] = -res[1], res[2] = -res[2]; // for double use feq(res[0], 0)
 return res;
}
