#include <iostream>

class complex {
  public:
   complex() {
     re = im = 0;
  }

   complex(float re, float im) {
       setRe(re);
       setIm(im);
   }

   ~complex() {
       std::cout << "Die" << std::endl;
   }

   float getRe() const  {
       return re;
   }

   void setRe(float re) {
       this->re = re;
   }

   float getIm() const {
       return im;
   }

   void setIm(float im) {
       this->im = im;
   }

  private:
   float re;
   float im;
};

complex operator+(const complex& l, const complex& r) {
   complex result(l.getRe() + r.getRe(), l.getIm() + r.getIm());
   return result;
}

std::ostream& operator<<(std::ostream&o, const complex& c) {
    return o << "{ re = " << c.getRe() << ", im = " << c.getIm() << " }";
}

namespace sss {
    complex global;
}

void f(double x, double const y, double&  z) {
    std::cout << sizeof(x) << " " << sizeof(y) << " " << sizeof(z);
}

int main() {
    {
      const complex c(10, 20) , b(-3,12);
      complex a = b + c;
      std::cout << a << std::endl;
    }
    return 0;
}
