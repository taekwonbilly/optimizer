#ifndef __CAS_H_
#define __CAS_H_

#include "vector.h"

#define assertR(a) assert( !isnan(a) ); return a;

template< size_t L=3, typename V=double >
class Expression { 
public:
  virtual V eval( const Vector<L,V> vals) const = 0;
  virtual Vector<L,V> grad( const Vector<L,V> vals) const = 0;
  inline V operator() (const Vector<L,V> vals) const { assertR( eval(vals) ) }
};

template< size_t L=3, typename V=double >
class ConstExpression : public Expression<L,V> { 
V _val;
public:
  ConstExpression( const V& val ) : _val(val) {}
  ConstExpression( const V&& val ) : _val(val) {}
  V eval( const Vector<L,V> vals) const override final { assertR( _val ) }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return Vector<L,V>::Zero(); }
};

template< size_t L=3, typename V=double >
class VarExpression : public Expression<L,V> { 
size_t _idx;
public:
  VarExpression( const size_t& idx ) : _idx(idx) {}
  VarExpression( const size_t&& idx ) : _idx(idx) {}
  V eval( const Vector<L,V> vals) const override final { assertR( vals[_idx] ) }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return Vector<L,V>(_idx, 1); }
};

template< char op, size_t L=3, typename V=double >
class EBinop : public Expression<L,V> {
  const Expression<L,V> &left;
  const Expression<L,V> &right;
public:
  V eval( const Vector<L,V> vals ) const override final;
  Vector<L,V> grad( const Vector<L,V> vals) const override final;
};


template< size_t L, typename V > 
class EBinop<'+', L, V> : public Expression<L,V> {
  const Expression<L,V> &left;
  const Expression<L,V> &right;
public:
  EBinop( const Expression<L,V>& lhs, const Expression<L,V>& rhs ) : left(lhs), right(rhs) {}
  EBinop( const Expression<L,V>&& lhs, const Expression<L,V>&& rhs ) : left(lhs), right(rhs) {}
  V eval( const Vector<L,V> vals ) const { return left.eval(vals) + right.eval(vals); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return left.grad(vals) + right.grad(vals); }
};

template< size_t L, typename V > 
class EBinop<'-', L, V> : public Expression<L,V> {
  const Expression<L,V> &left;
  const Expression<L,V> &right;
public:
  EBinop( const Expression<L,V>& lhs, const Expression<L,V>& rhs ) : left(lhs), right(rhs) {}
  EBinop( const Expression<L,V>&& lhs, const Expression<L,V>&& rhs ) : left(lhs), right(rhs) {}
  V eval( const Vector<L,V> vals ) const { return left.eval(vals) - right.eval(vals); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return left.grad(vals) - right.grad(vals); }
};

template< size_t L, typename V > 
class EBinop<'*', L, V> : public Expression<L,V> {
  const Expression<L,V> &left;
  const Expression<L,V> &right;
public:
  EBinop( const Expression<L,V>& lhs, const Expression<L,V>& rhs ) : left(lhs), right(rhs) {}
  EBinop( const Expression<L,V>&& lhs, const Expression<L,V>&& rhs ) : left(lhs), right(rhs) {}
  V eval( const Vector<L,V> vals ) const { return left.eval(vals) * right.eval(vals); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return left.grad(vals) * right.eval(vals) + left.eval(vals) * right.grad(vals); }
};

template< size_t L, typename V > 
class EBinop<'/', L, V> : public Expression<L,V> {
  const Expression<L,V> &left;
  const Expression<L,V> &right;
public:
  EBinop( const Expression<L,V>& lhs, const Expression<L,V>& rhs ) : left(lhs), right(rhs) {}
  EBinop( const Expression<L,V>&& lhs, const Expression<L,V>&& rhs ) : left(lhs), right(rhs) {}
  V eval( const Vector<L,V> vals ) const { return left.eval(vals) / right.eval(vals); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { 
    auto g = right.eval(vals);
return ( left.grad(vals) * g - left.eval(vals) * right.grad(vals) ) / ( g*g ); }
};

/*
template< size_t L, typename V > 
class EBinop<'^', L, V> : public Expression<L,V> {
  const Expression<L,V> &left;
  const Expression<L,V> &right;
public:
  EBinop( const Expression<L,V>& lhs, const Expression<L,V>& rhs ) : left(lhs), right(rhs) {}
  EBinop( const Expression<L,V>&& lhs, const Expression<L,V>&& rhs ) : left(lhs), right(rhs) {}
  V eval( const Vector<L,V> vals ) const { return pow(left.eval(vals), right.eval(vals)); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return left.grad(vals) * right.eval(vals) + left.eval(vals) * right.grad(vals); }
};*/

template< size_t L, typename V=double > 
const Expression<L,V>& operator+( const Expression<L>& lhs, const Expression<L>& rhs ) {
  return *(new EBinop<'+',L,V>(lhs,rhs));
}

template< size_t L, typename V=double > 
const Expression<L,V>& operator-( const Expression<L>& lhs, const Expression<L>& rhs ) {
  return *(new EBinop<'-',L,V>(lhs,rhs));
}

template< size_t L, typename V=double > 
const Expression<L,V>& operator*( const Expression<L>& lhs, const Expression<L>& rhs ) {
  return *(new EBinop<'*',L,V>(lhs,rhs));
}

template< size_t L, typename V=double > 
const Expression<L,V>& operator/( const Expression<L>& lhs, const Expression<L>& rhs ) {
  return *(new EBinop<'/',L,V>(lhs,rhs));
}

template< size_t L, typename V=double > 
const Expression<L,V>& operator^( const Expression<L>& lhs, const Expression<L>& rhs ) {
  return *(new EBinop<'^',L,V>(lhs,rhs));
}

#define V double
template< size_t L > 
const Expression<L,V>& operator+( const V& lhs, const Expression<L>& rhs ) {
  return *(new EBinop<'+',L,V>(*(new ConstExpression<L,V>(lhs)),rhs));
}

template< size_t L > 
const Expression<L,V>& operator-( const V& lhs, const Expression<L>& rhs ) {
  return *(new EBinop<'-',L,V>(*(new ConstExpression<L,V>(lhs)),rhs));
}

template< size_t L > 
const Expression<L,V>& operator*( const V& lhs, const Expression<L>& rhs ) {
  return *(new EBinop<'*',L,V>(*(new ConstExpression<L,V>(lhs)),rhs));
}

template< size_t L > 
const Expression<L,V>& operator/( const V& lhs, const Expression<L>& rhs ) {
  return *(new EBinop<'/',L,V>(*(new ConstExpression<L,V>(lhs)),rhs));
}

template< size_t L > 
const Expression<L,V>& operator^( const V lhs, const Expression<L>& rhs ) {
  return *(new EBinop<'^',L,V>(*(new ConstExpression<L,V>(lhs)),rhs));
}


template< size_t L > 
const Expression<L,V>& operator+( const V& lhs, const Expression<L>&& rhs ) {
  return *(new EBinop<'+',L,V>(*(new ConstExpression<L,V>(lhs)),rhs));
}

template< size_t L > 
const Expression<L,V>& operator-( const V& lhs, const Expression<L>&& rhs ) {
  return *(new EBinop<'-',L,V>(*(new ConstExpression<L,V>(lhs)),rhs));
}

template< size_t L > 
const Expression<L,V>& operator*( const V& lhs, const Expression<L>&& rhs ) {
  return *(new EBinop<'*',L,V>(*(new ConstExpression<L,V>(lhs)),rhs));
}

template< size_t L > 
const Expression<L,V>& operator/( const V& lhs, const Expression<L>&& rhs ) {
  return *(new EBinop<'/',L,V>(*(new ConstExpression<L,V>(lhs)),rhs));
}

template< size_t L > 
const Expression<L,V>& operator^( const V lhs, const Expression<L>&& rhs ) {
  return *(new EBinop<'^',L,V>(*(new ConstExpression<L,V>(lhs)),rhs));
}




template< size_t L > 
const Expression<L,V>& operator+( const Expression<L>& lhs, const V& rhs ) {
  return *(new EBinop<'+',L,V>(lhs,*(new ConstExpression<L>(rhs))));
}

template< size_t L > 
const Expression<L,V>& operator-( const Expression<L>& lhs, const V& rhs ) {
  return *(new EBinop<'-',L,V>(lhs,*(new ConstExpression<L>(rhs))));
}

template< size_t L > 
const Expression<L,V>& operator*( const Expression<L>& lhs, const V& rhs ) {
  return *(new EBinop<'*',L,V>(lhs,*(new ConstExpression<L>(rhs))));
}

template< size_t L > 
const Expression<L,V>& operator/( const Expression<L>& lhs, const V& rhs ) {
  return *(new EBinop<'/',L,V>(lhs,*(new ConstExpression<L>(rhs))));
}

template< size_t L > 
const Expression<L,V>& operator^( const Expression<L>& lhs, const V& rhs ) {
  return *(new EBinop<'^',L,V>(lhs,*(new ConstExpression<L>(rhs))));
}

template< size_t L > 
const Expression<L,V>& operator+( const Expression<L>& lhs, const V&& rhs ) {
  return *(new EBinop<'+',L,V>(lhs,*(new ConstExpression<L>(rhs))));
}

template< size_t L > 
const Expression<L,V>& operator-( const Expression<L>& lhs, const V&& rhs ) {
  return *(new EBinop<'-',L,V>(lhs,*(new ConstExpression<L>(rhs))));
}

template< size_t L > 
const Expression<L,V>& operator*( const Expression<L>& lhs, const V&& rhs ) {
  return *(new EBinop<'*',L,V>(lhs,*(new ConstExpression<L>(rhs))));
}

template< size_t L > 
const Expression<L,V>& operator/( const Expression<L>& lhs, const V&& rhs ) {
  return *(new EBinop<'/',L,V>(lhs,*(new ConstExpression<L>(rhs))));
}

template< size_t L > 
const Expression<L,V>& operator^( const Expression<L>& lhs, const V&& rhs ) {
  return *(new EBinop<'^',L,V>(lhs,*(new ConstExpression<L>(rhs))));
}
#undef V

enum class SymFunction {
  COS, SIN, EXP, LOG, SQRT, NEG
};

template< SymFunction op, size_t L=3, typename V=double >
class EFunc : public Expression<L,V> {
  const Expression<L,V> &inner;
public:
  EFunc( const Expression<L,V>& innerA ) : inner(innerA) {}
  EFunc( const Expression<L,V>&& innerA ) : inner(innerA) {}
  V eval( const Vector<L,V> vals ) const override final;
};

template< size_t L, typename V > 
class EFunc<SymFunction::NEG,L,V> : public Expression<L,V> {
  const Expression<L,V> &inner;
public:
  EFunc( const Expression<L,V>& innerA ) : inner(innerA) {}
  EFunc( const Expression<L,V>&& innerA ) : inner(innerA) {}
  V eval( const Vector<L,V> vals ) const { return -( inner.eval(vals) ); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return - inner.grad(vals); }
};

template< size_t L, typename V > 
class EFunc<SymFunction::COS,L,V> : public Expression<L,V> {
  const Expression<L,V> &inner;
public:
  EFunc( const Expression<L,V>& innerA ) : inner(innerA) {}
  EFunc( const Expression<L,V>&& innerA ) : inner(innerA) {}
  V eval( const Vector<L,V> vals ) const { return cos( inner.eval(vals) ); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return -sin(inner.eval(vals))*inner.grad(vals); }
};

template< size_t L, typename V > 
class EFunc<SymFunction::SIN,L,V> : public Expression<L,V> {
  const Expression<L,V> &inner;
public:
  EFunc( const Expression<L,V>& innerA ) : inner(innerA) {}
  EFunc( const Expression<L,V>&& innerA ) : inner(innerA) {}
  V eval( const Vector<L,V> vals ) const { return sin( inner.eval(vals) ); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return cos(inner.eval(vals))*inner.grad(vals); }
};

template< size_t L, typename V > 
class EFunc<SymFunction::EXP,L,V> : public Expression<L,V> {
  const Expression<L,V> &inner;
public:
  EFunc( const Expression<L,V>& innerA ) : inner(innerA) {}
  EFunc( const Expression<L,V>&& innerA ) : inner(innerA) {}
  V eval( const Vector<L,V> vals ) const { return exp( inner.eval(vals) ); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return exp(inner.eval(vals))*inner.grad(vals); }
};

template< size_t L, typename V > 
class EFunc<SymFunction::LOG,L,V> : public Expression<L,V> {
  const Expression<L,V> &inner;
public:
  EFunc( const Expression<L,V>& innerA ) : inner(innerA) {}
  EFunc( const Expression<L,V>&& innerA ) : inner(innerA) {}
  V eval( const Vector<L,V> vals ) const { return log( inner.eval(vals) ); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return inner.grad(vals)/inner.eval(vals); }
};

template< size_t L, typename V > 
class EFunc<SymFunction::SQRT,L,V> : public Expression<L,V> {
  const Expression<L,V> &inner;
public:
  EFunc( const Expression<L,V>& innerA ) : inner(innerA) {}
  EFunc( const Expression<L,V>&& innerA ) : inner(innerA) {}
  V eval( const Vector<L,V> vals ) const { return sqrt( inner.eval(vals) ); }
  Vector<L,V> grad( const Vector<L,V> vals) const override final { return inner.grad(vals)/(2*sqrt(inner.eval(vals))); }
};

template< size_t L, typename V > 
const Expression<L,V>& operator-( const Expression<L,V>& val ) {
  return *(new EFunc<SymFunction::NEG,L,V>(val));
}

template< size_t L, typename V > 
const Expression<L,V>& cos( const Expression<L,V>& val ) {
  return *(new EFunc<SymFunction::COS,L,V>(val));
}

template< size_t L, typename V > 
const Expression<L,V>& sin( const Expression<L,V>& val ) {
  return *(new EFunc<SymFunction::SIN,L,V>(val));
}

template< size_t L, typename V > 
const Expression<L,V>& exp( const Expression<L,V>& val ) {
  return *(new EFunc<SymFunction::EXP,L,V>(val));
}

template< size_t L, typename V > 
const Expression<L,V>& log( const Expression<L,V>& val ) {
  return *(new EFunc<SymFunction::LOG,L,V>(val));
}

template< size_t L, typename V > 
const Expression<L,V>& sqrt( const Expression<L,V>& val ) {
  return *(new EFunc<SymFunction::SQRT,L,V>(val));
}

#endif
