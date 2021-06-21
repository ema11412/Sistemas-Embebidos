#ifndef HELLO_H
#define HELLO_H

/* in case we use a C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

void
hello( char const* name );

float
floater( void );

float
fadd( float x, float y );

void
test_padding_array(int* data, int len);

#ifdef __cplusplus
}
#endif

#endif /* HELLO_H */
