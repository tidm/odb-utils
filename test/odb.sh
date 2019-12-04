includes=`pkg-config --cflags oi_odb_utils | sed 's/-W[A-Z,a-z,-]*//g'`;
function generate_odb()
{
odb \
    $includes \
    -I/usr/share/include/odb/ -I/usr/include/boost169/ -I/usr/share/include/  \
    --odb-prologue '#include <type_traits/std_chrono_oracle.hpp>' \
    --hxx-prologue '#include <type_traits/std_chrono.hpp>' \
    --odb-prologue '#include <cstddef>' \
    --hxx-prologue '#include <cstddef>' \
    --database oracle \
    --generate-schema \
    --generate-query \
    --std c++11 \
    --sequence-suffix _SEQ \
    --hxx-suffix .hpp \
    --ixx-suffix _inline.hpp \
    --cxx-suffix .cpp \
    --odb-file-suffix _odb \
    $1
}
generate_odb req_agent.hpp
