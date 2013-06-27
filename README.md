m
==

Generical macro madness!

<!--


Conventions:

Library Prefix: 'm'

Scope: 
    A letter and name used to identify a specific aspect of the library.
    E.g. Containers have the scope 'c (cdt)', Exceptions have the scope 'x (xc)'

Scope Prefix:
    Simply Library Prefix + Scope Letter.

Class Name:
    A letter and name used to identify a class pertaining to a specific scope.
    E.g.: Lists in the Container scope have the classname 'l (list)'.
    
Method Names:
    Method names have at least 2 characters, and starts with a lowercase letter.
    Underlines are not valid.
    Camel case is valid, but avoided. Instead, reduce the names of the methods.
    E.g.: 'add', 'push', etc

Macro Method Names:
    Follows the same conventions of method names, with the exception that
    the name is all uppercase.
    Macro functions usually doesn't map to their equivalent concrete ones.
    E.g.: 'ADD', 'PUSH', etc

User Typename:
    Typenames are provided by the user, and are exclusive to the scope they
    were declared into.
    Typenames must resolve into a single token.
    More specifically, they must be a valid identifier.
    E.g.: int, 32, lo32_ys

Realized User typenames:
    A typename prefixed with a class, method or namespace name.
    The typename will always be prefixed with '__'.
    E.g.: mc__int__i (Scope: mt (cdt), Typename: int, Type/Method: i (Iterator))

Type Suffixes:
    All suffixes starts with '_'.
    For realized names, they must start with '__'.
    - (No suffix): Generally, the same as 't'.
    - 't': The type. Must be properly typedef'd.
    - 'p': Pointer for the type. Must be properly typedef'd.
    - 'i': Iterator type to the type. Must be properly typedef'd.
    - 'ip': Pointer to the iterator. Must be properly typedef'd.
    - 'k<i>': Key type, for containers. In case there's more than one type,
        they'll be numbered as 'i' (e.g. k1, k2, k3, etc), with k1 == k.
        Must be properly typedef'd.
    - 'v<i>': Same as 'k<i>', but for values.

Special Suffixes:
    Suffixes with special usages.
    They always come last in the name.
    All suffixes starts with '_'.
    - 'USERSTRUCT': Markers for structs and unions.
    - 'USERAPI': Markers for public user functions.
    - 'USERDATA': Marker for public user data and variables.
    - 'USERIAPI': Markers for internal user functions.
    - 'USERIDATA': Marker for internal user data and variables.
    - 'DECT': Emits typedefs and function/variable declarations.
    - 'DECS': Emits structures, unions and enums definitions.
    - 'DECL': Same as DECT followed by DECS.
    - 'DEFN': Defines functions and initialize variables.
        Implies that DECL was previously done.
    - 'DINIT': All at once (DECL and DEFN).


*/

/*

m  - [macro]  macro type
mx - [xc]     exception handling
    mxc  - [mx_exc] Exception
mt - [type]   generic type library
    mt   - []
    mtsz - [mt_sz]
mm - [mem]    memory management
mc - [adc]    abstract data container
ms - [stream] stream type

mp - [thread] Threading and 

mc    - type to be used on functions (generally a value)
mc_t  - object's type
mc_p  - pointer type
mc_pd - pointer diff
mc_sz - object size

mc_i  - iterator
mc_k  - key type
mc_v  - value type

#include "m/adc/vector.h"

mc(l_i) c = mc_new(l_i)();


mx_ON(i)(v)
    printf("Not caught, %d", v);

mx_TRY(i)
    mx_THROW(10);
mx_CATCH(i)(v)
	printf("%d", v);
mx_FINALLY
	printf("finished");


LIBRARY TYPES

# Base
c  - ctnr
e  - elem (type)
i  - iter

# Nodes
an - array (node)
pn - pair (node)
ln - listnode
fn - flistnode
gn - graphnode
tn - treenode

# Abstract
a  - array
v  - vector
bv - bitvector
d  - deque
l  - list
fl - flist
s  - treeset
hs - hashset
m  - treemap
hm - hashmap

# Adaptors
b  - buffer
q  - queue
pq - pqueue
k  - stack
t  - tree
g  - graph

# Types
c   - char
w   - wchar_t
sz  - size_t
o   - offset_t
pd  - ptrdiff_t
s   - short
i   - int
l   - long
ll  - long long
uc  - unsigned char
us  - unsigned short
ui  - unsigned int
ul  - unsigned long
ull - unsigned long long
8   - int8
16  - int16
32  - int32
64  - int64
u8  - uint8
u16 - uint16
u32 - uint32
u64 - uint64
f   - float
d   - double
ld  - long double
f32 - float32
f64 - float64
p   - void*
b   - char* (buffer)
cs  - char*
ws  - wchar_t*
mbs - char* (multi-byte)

-->