#ifndef FTC_ValueUtils_h
#define FTC_ValueUtils_h

#define highLimit(v, h) (v > h ? h : v)
#define lowLimit(v, l) (v < l ? l : v)
#define hlLimit(v, h, l) ( v > h ? h : ( v < l ? l : v ) )
#define limitVar(v, l) ( v > l ? l : ( v < -l ? -l : v ) )

#define dbc(v,l) ( ( abs(v) > l ) ? v : 0 )

#define biggest(a,b) ((a>b)?a:b)
#define smallest(a,b) ((a<b)?a:b)
#define isBetween(v, a, b) (v<biggest(a,b)&&v>smallest(a,b))

#define flipVar(v, max) (-(v-max))

#define signSquare(x) ((x<0)? -1*x*x : x*x)

#endif
